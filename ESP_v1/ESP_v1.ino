/*
    Name:       ESP_v1.ino
    Created:	27.09.2019 13:13:37
    Author:     Jan Wielgus
*/

#include <FC_TaskPlanner.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "GlobalData.h"
#include "TemperatureSensor.h"


void setup()
{
	if (!initializeTemperatureSensors())
	{
		// ERROR
	}
}

void loop()
{


}
