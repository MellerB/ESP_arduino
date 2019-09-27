#pragma once

#include "GlobalData.h"
#include <DallasTemperature.h>
#include <FC_TaskPlanner.h>

using namespace globalData;

FC_TaskPlanner temperatureTaskPlanner(3); // max 3 scheduled tasks

// function headers
bool initializeTemperatureSensors();
uint32_t getMinTemperatureReadingTaskMicrosInterval();
void readTemperatures();
void getTemperatures();


uint16_t conversionWaitTime;



bool initializeTemperatureSensors()
{
	sensors.begin();

	if (!sensors.getAddress(Address.insideThermometer, InsideTempIndex))
	{
		// Unable to find address for the inside thermometer
		return false;
	}


	if (!sensors.getAddress(Address.outsideThermometer, OutsideTempIndex))
	{
		// Unable to find address for the outside thermometer
		return false;
	}

	
	// set up both thermometers
	sensors.setResolution(TempBitResolution);
	sensors.setWaitForConversion(false); // disable delay inside the request method

	conversionWaitTime = sensors.millisToWaitForConversion(TempBitResolution);


	// Everything went OK
	return true;
}


// Calculate the min temperature reading task interval
// Which is the maximum reading frequency
uint32_t getMinTemperatureReadingTaskMicrosInterval()
{
	float maxAmtOfReadingsPerSecond = 1000.0 / (float)sensors.millisToWaitForConversion(TempBitResolution);
	return (uint32_t)((1000000.0f / maxAmtOfReadingsPerSecond) + 0.5f);
}


void readTemperatures()
{
	// Request temperatures from all devices
	sensors.requestTemperatures();

	// Schedule getting the temperatures task
	temperatureTaskPlanner.scheduleTask(getTemperatures, conversionWaitTime);
}


void getTemperatures()
{
	temperature.inside = sensors.getTempC(Address.insideThermometer);
	temperature.outside = sensors.getTempC(Address.outsideThermometer);
}

