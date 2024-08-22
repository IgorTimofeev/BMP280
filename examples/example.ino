#include <Arduino.h>
#include "BMP280.h"

BMP280 bmp(27);

float pressureToAltitude(float pressureInPa, float seaLevelInPa) {
	return 44330.0f * (1.0f - powf(pressureInPa / seaLevelInPa, 1.0f / 5.255f));
}

void setup() {
	Serial.begin(115200);

	bmp.begin();
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