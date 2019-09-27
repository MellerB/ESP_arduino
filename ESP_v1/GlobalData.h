#pragma once

#include <OneWire.h>
#include <DallasTemperature.h>


namespace globalData
{
// constants
	// ip address
	// port
	struct
	{
		typedef uint8_t Pin;

		// !!!!   SET UP ALL PINS   !!!!

		const Pin TemperatureSensorWireBus = 0;
		const Pin Relay = 0;
	}pin;
	const uint8_t insideTempIndex = 0;
	const uint8_t outsideTempIndex = insideTempIndex == 0 ? 1 : 0; // different than insideIndex



// variables
	struct
	{
		float inside;
		float outside;
	}temperature;



// objects and custom data types
	// temperature sensors
	OneWire oneWire(pin.TemperatureSensorWireBus);
	DallasTemperature sensors(&oneWire);
	struct
	{
		DeviceAddress insideThermometer;
		DeviceAddress outsideThermometer;
	}address;
}

