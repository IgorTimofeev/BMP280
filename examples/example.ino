#include <Arduino.h>
#include "BMP280.h"

BMP280 bmp(27);

float pressureToAltitude(float pressureInPa, float seaLevelInPa) {
	return 44330.0f * (1.0f - powf(pressureInPa / seaLevelInPa, 1.0f / 5.255f));
}

void setup() {
	Serial.begin(115200);

	if (!_bmp.begin()) {
		Serial.println("BMP280 initialization failed, check wiring");

		while (1)
			delay(100);
	}

	_bmp.configure(
		BMP280Mode::Normal,
		BMP280Oversampling::X2,
		BMP280Oversampling::X16,
		BMP280Filter::X16,
		BMP280StandbyDuration::Ms125
	);
}

void loop() {
	auto temperature = bmp.readTemperature();
	auto pressure = bmp.readPressure();
	auto altitude = pressureToAltitude(pressure, 102200);

	Serial.print("Temperature: ");
	Serial.print(temperature);
	Serial.println(" *C");

	Serial.print("Pressure: ");
	Serial.print(pressure);
	Serial.println(" Pa");

	Serial.print("Altitude: ");
	Serial.print(altitude);
	Serial.println(" m");

	delay(1000);
}