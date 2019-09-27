/*
    Name:       ESP_v1.ino
    Created:	27.09.2019 13:13:37
    Author:     Jan Wielgus
*/

#include <FC_Tasker.h>
#include <FC_TaskPlanner.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "GlobalData.h"
#include "TemperatureSensor.h"


FC_SimpleTasker tasker;


void setup()
{
	if (!initializeTemperatureSensors())
	{
		// ERROR
		// Inner, outer or both thermometers failed
	}


	// This functions will be executed in the constant period
	tasker.addFunction(readTemperatures, getMinTemperatureReadingTaskMicrosInterval(), 10);
}

void loop()
{
	tasker.runTasker();
	temperatureTaskPlanner.runPlanner(); // call planned tasks if time has come
}
