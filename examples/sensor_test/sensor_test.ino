//-----------------------------------------------------------------
//
// Feb-2018
//
// Condition Monitoring Box v1 - sensor test
//
// DPS310:   I2C 0x77 (dec 119) (works on socket 2 only)
// TLV493D:  I2C 0x5E (dec 94)
//
//-----------------------------------------------------------------

#include <Wire.h>
#include <Dps310.h>
#include <Tlv493d.h>

//-----------------------------------------------------------------

// WeMos D1 mini pinout
// https://escapequotes.net/wp-content/uploads/2016/02/esp8266-wemos-d1-mini-pinout.png

// I2C pins
const int sdaPin = D2; // PIN_WIRE_SDA
const int sclPin = D1; // PIN_WIRE_SDL

Dps310  Dps310PressureSensor    = Dps310();
Tlv493d Tlv493dMagnetic3DSensor = Tlv493d();

//-----------------------------------------------------------------


void setup() {

  int32_t temperature;
  int32_t pressure;
  int16_t oversampling = 7;
  int16_t ret;

  //-----------------------------------------------------------------
  Serial.begin(9600);
  Serial.println();

  //-----------------------------------------------------------------
  // scan I2C bus
  Wire.begin(sdaPin, sclPin);
      
  byte error, address;
  int nDevices;

  Serial.println("Scanning I2C bus ...");

  nDevices = 0;
  for (address = 1; address < 127; address++) {
    // The i2c scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address: 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println(" !");
      nDevices++;

      // DPS310 found?
      if( address == 119 ) {
        Serial.println("-----------------------------------");
        Serial.println("DPS310 barometric pressure sensor");
        Dps310PressureSensor.begin(Wire, address);
        Dps310PressureSensor.correctTemp();
        ret = Dps310PressureSensor.measureTempOnce(temperature, oversampling);
        ret = Dps310PressureSensor.measurePressureOnce(pressure, oversampling);
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println("C");

        int p = (int) pressure/100;
        Serial.print("Pressure: ");
        Serial.print(p);
        Serial.println("hPa");  
        Serial.println("-----------------------------------");
      }

      // TLV493D found?
      if( address == 94 ) {
        Serial.println("-----------------------------------");
        Serial.println("TLV493D 3D magnetic sensor ");

        Tlv493dMagnetic3DSensor.begin();
        Tlv493dMagnetic3DSensor.updateData();
        delay(100);

        Serial.print("X = ");
        Serial.print(Tlv493dMagnetic3DSensor.getX());
        Serial.print(" mT; Y = ");
        Serial.print(Tlv493dMagnetic3DSensor.getY());
        Serial.print(" mT; Z = ");
        Serial.print(Tlv493dMagnetic3DSensor.getZ());
        Serial.println(" mT");
        Tlv493dMagnetic3DSensor.end();
        Serial.println("-----------------------------------");
      }

    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  } else {
    Serial.println("Done.");
  }

  //-----------------------------------------------------------------

  Serial.println("Done.");

}

//-----------------------------------------------------------------

void loop() {

}
