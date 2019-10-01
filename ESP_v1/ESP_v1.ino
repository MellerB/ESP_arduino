/*
    Name:       ESP_v1.ino
    Created:	27.09.2019 13:13:37
    Author:     Jan Wielgus
*/

#include <FC_AverageFilter.h>
#include <FC_Tasker.h>
#include <FC_TaskPlanner.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "GlobalData.h"
#include "TemperatureSensor.h"


// objects
FC_SimpleTasker tasker;
FC_AverageFilter<float, float, float> insideTempFilter(globalData::AveragedSecondsInsideTemp * 2); // *2 because average function runs at is 2Hz
FC_AverageFilter<float, float, float> outsideTempFilter(globalData::AveragedSecondsOutsideTemp * 2); // *2 because average function runs at is 2Hz

// tasker functions
void showDebugTemperature();
void controlBlink();
void updateRealyAction();
void averageTemperatures();

// other functions
void setRelay(bool state);


void setup()
{
	Serial.begin(115200);

	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(globalData::pin.Relay, OUTPUT);


	while (!initializeTemperatureSensors())
	{
		// ERROR
		// Inner, outer or both thermometers failed
		Serial.println("Init failed");

		delay(1000);
	}


	// This functions will be executed in the constant period
	tasker.addFunction(readTemperatures, getMinTemperatureReadingTaskMicrosInterval(), 0); // 1.3Hz when 12 bit resolution
	tasker.addFunction(showDebugTemperature, getMinTemperatureReadingTaskMicrosInterval(), 0); // 1.3Hz when 12 bit resolution
	tasker.addFunction(controlBlink, 1000000L, 0); // 1Hz
	tasker.addFunction(updateRealyAction, 1000000L, 0); // 1Hz
	tasker.addFunction(averageTemperatures, 500000L, 0); // 2Hz
}


void loop()
{
	tasker.runTasker();
	temperatureTaskPlanner.runPlanner(); // call planned tasks if time has come
}





void showDebugTemperature()
{
	Serial.print("Ti: ");
	Serial.print(temperature.inside);
	Serial.print("\tTo: ");
	Serial.print(temperature.outside);
	Serial.println();
}


// decide to change the relay state
void updateRealyAction()
{
	using namespace globalData;

	// choose if need to change relay state
	float twoTempAverage = (temperature.inside + temperature.outside) / 2.0f; // average of inside and outside thermometer
	if (twoTempAverage > SetTemperature + TemperatureDeadZone)
		setRelay(true);
	else if (twoTempAverage < SetTemperature - TemperatureDeadZone)
		setRelay(false);
}


void averageTemperatures()
{
	// average temperature data
	insideTempFilter.addNewSample(temperature.inside);
	averagedTemp.inside = insideTempFilter.getAverage();

	outsideTempFilter.addNewSample(temperature.outside);
	averagedTemp.outside = outsideTempFilter.getAverage();
}


void controlBlink()
{
	static bool ledState = LOW;
	digitalWrite(LED_BUILTIN, ledState);
	ledState = !ledState;
}


void setRelay(bool state)
{
	if (state)
		digitalWrite(globalData::pin.Relay, LOW);
	else
		digitalWrite(globalData::pin.Relay, HIGH);
}
