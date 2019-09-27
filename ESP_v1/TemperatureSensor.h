#pragma once

#include "GlobalData.h"
#include <DallasTemperature.h>

using namespace globalData;


bool initializeTemperatureSensors()
{
	sensors.begin();

	if (!sensors.getAddress(address.insideThermometer, insideTempIndex))
	{
		// Unable to find address for the inside thermometer
		return false;
	}

	if (!sensors.getAddress(address.outsideThermometer, outsideTempIndex))
	{
		// Unable to find address for the outside thermometer
		return false;
	}


	// Everything went OK
	return true;
}


void readTemperatures()
{
	// ...
}

