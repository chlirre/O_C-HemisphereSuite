## Developing

### Background
[The original software for the Ornament and Crime](https://github.com/mxmxmx/O_C) was written for the Arduino IDE 1.8.1 with the teensyduino add-on.

Since Arduino IDE 1.8.1 is not exactly a best in class IDE and the fact that it will not even install on recent version of OS X, another development environment was needed.

### PlatformIO
[PlatformIO](https://platformio.org/) is a _collaborative platform for embedded development_. 

#### Getting started
1. Download PlatformIO from [https://platformio.org/](https://platformio.org/)
2. Open the project's `/software` folder in PlatformIO
3. Build / upload


## Tests
### Desktop
Tests are located in `/test`.

#### Running
In the PlatformIO terminal, run:
`pio test -e native`