#include "Si7021.h"

Si7021 si7021;


void setup() {
  
  uint64_t serialNumber = 0ULL;

  Serial.begin(115200);
  si7021.begin();

  serialNumber = si7021.getSerialNumber();

  //arduino lib doesn't natively support printing 64bit numbers on the serial port
  //so it's done in 2 times
  Serial.print("Si7021 serial number: ");
  Serial.print((uint32_t)(serialNumber >> 32), HEX);
  Serial.println((uint32_t)(serialNumber), HEX);

  //Firware version
  Serial.print("Si7021 firmware version: ");
  Serial.println(si7021.getFirmwareVersion(), HEX);

}

void loop() {

  Serial.print("Humidity: ");
  Serial.print(si7021.measureHumidity());
  Serial.print("% \tTemperature: ");
  Serial.print(si7021.getTemperatureFromPreviousHumidityMeasurementF());
  Serial.println("F");
  delay(1000);


}
