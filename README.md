# Smart Espresso Scale

A Smart Espresso Scale, powered by the [Raspberry Pi Pico W board](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html).

## componetns used

1. [Raspberry Pi Pico W board](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html)
   1. [pinout](https://datasheets.raspberrypi.com/picow/PicoW-A4-Pinout.pdf)
   1. [I2C Wire doc - pico](https://arduino-pico.readthedocs.io/en/latest/wire.html)
   1. [I2C Wire doc - arduino](https://www.arduino.cc/reference/en/language/functions/communication/wire/)
1. [I2C 1602 LCD Display Module 16X2](https://www.amazon.com/dp/B07S7PJYM6)
   1. [documentation](https://wiki.52pi.com/index.php?title=Z-0234)
   1. [arduino lib](https://github.com/johnrickman/LiquidCrystal_I2C)
   1. [arduino example](https://projecthub.arduino.cc/arduino_uno_guy/i2c-liquid-crystal-displays-5eb615)
1. [SparkFun Qwiic Scale - NAU7802](https://www.sparkfun.com/products/15242)
   1. [arduino lib](https://github.com/sparkfun/SparkFun_Qwiic_Scale_NAU7802_Arduino_Library)

## VS Code

1. install VS Code
1. make sure the _Arduino_ and _z-uno_ extensions are not installed or at least, _disabled_ if installed
1. [install the PlatformIO extension](https://platformio.org/platformio-ide)
   1. on Chromebook
      1. `sudo apt-get install python3-venv`
      1. restart VSCode
      1. warning: it may take up to 10 minutes to finish the installation and all the pio commands to become available
1. install [99-platformio-udev.rules](https://docs.platformio.org/en/latest/core/installation/udev-rules.html)
   1. `curl -fsSL https://raw.githubusercontent.com/platformio/platformio-core/develop/platformio/assets/system/99-platformio-udev.rules | sudo tee /etc/udev/rules.d/99-platformio-udev.rules`
   1. on Fedora
      1. `sudo udevadm control --reload-rules && sudo udevadm trigger`
   1. on Chromebook
      1. `sudo service udev restart`
   1. on Fedora/Chromebook
      1. `sudo usermod -a -G dialout $USER`
      1. `sudo usermod -a -G plugdev $USER`
   1. logout / login to O/S
   1. physically unplug and reconnect your board
      1. on Chromebook
         1. select connect to Linux on chromebook
         1. it should appear as PicoArduino in the Manage USB devices
         1. then, serial monitor can connect
1. to initialize the project
   1. `pio project init`
   1. should give `Project has been successfully updated!`
1. select the active project environment
    1. `>PlatformIO: Switch Project Environment` or from the bottom left corner of the IDE
    1. select USB (for first upload) or OTA (for subsequent ones but change the `auth` inside `platformio.ini` file)
1. to build
   1. `>PlatformIO: Build` or `pio run` or from the bottom left corner of the IDE
   1. should result in `[SUCCESS]`
1. to monitor the serial port for debugging
   1. `>PlatformIO: Serial Monitor` or from the bottom left corner of the IDE
   1. should open up a new Terminal with the serial monitor
1. to upload
   1. `>PlatformIO: Upload` or from the bottom left corner of the IDE
   1. should show progress `Loading into Flash: [====] 100%` and `[SUCCESS]`
   1. if not, make sure you have installed the udev rules properly...
   1. warning: Upload over USB is [not possible currently on Chromebooks](https://issuetracker.google.com/issues/260278133). Therefore, the first upload MUST take place from another O/S (ie. Fedora) and subsequent uploads can happen OTA from Chromebook

### hostname

the device should get `smart-espresso-scale.local` as a hostname on the local network

### secrets

copy `secrets.h.template` to `secrets.h` and insert values

## troubleshooting

### debugging

- in `main.cpp` uncomment the `#define SERIAL_DEBUG` and build/upload, to enable serial.print debug messages

### clear arduino compile cache

`rm /tmp/arduino* -rf`

### upload through OTA fails

It is not always known why but uploading over WiFi directly to the device, can fail at random % and at random times.
The same code and environment settings can fail or succeed just be retrying multiple times.

Restarting the device does not really help.

The most important thing to succeed with OTA updates, is the WiFi signal to be great.
Otherwise, it may take up to 10 times/retries to succeed.

## references

1. [Arduino-Pico documentation](https://arduino-pico.readthedocs.io/en/latest/)
1. [Arduino-Pico repo](https://github.com/earlephilhower/arduino-pico)
