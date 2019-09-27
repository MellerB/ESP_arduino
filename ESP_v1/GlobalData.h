#pragma once

#include <OneWire.h>
#include <DallasTemperature.h>


namespace globalData
{
// CONFIG
	// ip address
	// port
	struct
	{
		typedef uint8_t Pin;

		// !!!!   SET UP ALL PINS   !!!!

		const Pin TemperatureSensorWireBus = 0;
		const Pin Relay = 0;
	}pin;
	const uint8_t InsideTempIndex = 0; // CHANGE ONLY THIS INDEX! outside is auto set to the opposite
	const uint8_t OutsideTempIndex = InsideTempIndex == 0 ? 1 : 0; // different than insideIndex

	const uint8_t TempBitResolution = 12;

// END OF CONFIG


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
	}Address;
}

