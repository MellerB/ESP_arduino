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

		const Pin TemperatureSensorWireBus = D6;
		const Pin Relay = D0;
	}pin;
	const uint8_t InsideTempIndex = 0; // CHANGE ONLY THIS INDEX! outside is auto set to the opposite
	const uint8_t OutsideTempIndex = InsideTempIndex == 0 ? 1 : 0; // different than insideIndex

	const uint8_t TemperatureBitResolution = 12;

	const uint16_t AveragedSecondsOutsideTemp = 30; // amt of seconds to average past samples
	const uint16_t AveragedSecondsInsideTemp = 30; // amt of seconds to average past samples
	const float SetTemperature = 22.0f;
	const float TemperatureDeadZone = 0.4f;

// END OF CONFIG


// variables
	struct tempType
	{
		float inside;
		float outside;
	};

	tempType temperature; // current reading from the sensors
	tempType averagedTemp; // averaged temperature reading



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

