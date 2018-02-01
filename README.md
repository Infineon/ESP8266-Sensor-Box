# ESP8266-Sensor-Box
This repository contains all components of the ESP8266 sensor box

## Condition Monitoring Box v1
The initial version of this sensor box consists of the following components:

### Hardware
* WeMos D1 mini (v2.1.0) ([pinout](https://escapequotes.net/wp-content/uploads/2016/02/esp8266-wemos-d1-mini-pinout.png))
* Infineon Adapter Socket
* DPS310 barometric pressure sensor ([datasheet](https://www.infineon.com/dgdl/Infineon-DPS310-DS-v01_00-EN.pdf?fileId=5546d462576f34750157750826c42242))
* TLV493D 3D magnetic sensor ([datasheet](https://www.infineon.com/dgdl/Infineon-TLV493D-A1B6-DS-v01_00-EN.pdf?fileId=5546d462525dbac40152a6b85c760e80))

### Software
* Install the Arduino IDE (get the latest version from [here](https://www.arduino.cc/))
* Add the WeMos D1 mini board in the Arduino IDE (read [this](http://www.instructables.com/id/Programming-the-WeMos-Using-Arduino-SoftwareIDE/))
* Add Arduino libraries for the sensors (libraries and instructions can be found [here](https://github.com/Infineon))

An example sketch can be found [here](https://github.com/Infineon/ESP8266-Sensor-Box/tree/master/examples).


### Important Notes
* The DPS310 barometric pressure sensor __only__ works on socket 2. This is due to a limitation of the WeMos board.

Files for a 3D printable enclosure will follow.
