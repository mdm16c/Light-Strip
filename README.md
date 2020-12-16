# Light-Strip
Neopixel light strip running on an Arduino Uno using the FastLED library for quick and efficient animations. The desired animation can be controlled with input read from an infrared remote.

## Motivation
This project is my first major attempt to create something useful for myself using an Arduino. I had been thinking about purchasing a light strip for myself, but I was always curious as to what the functionality of each different one was, and I never found the perfect one. I ended up deciding to just create my own as then I could decide what animations I used instead.

## Code Style
[![js-standard-style](https://img.shields.io/badge/code%20style-standard-brightgreen.svg?style=flat)](https://github.com/feross/standard)
 
## Effects Video
This will hopefully be uploaded soon. I am not able to get to the light strip currently due to Covid complications.

## Framework Used
[Arduino](https://www.arduino.cc/)

## Features
My project stands out in that it combines the IRremote and FastLED libraries which typically do not work together due to specific internal timer issues. I wrote the code in an abstract way that works around the idea of needing specific timers by utilizing the internal clock of the Arduino instead. Because of this, it allows these two libraries to work happily together.

## Credits
-[IRremote](https://github.com/Arduino-IRremote/Arduino-IRremote) </br>
-[FastLED](https://github.com/FastLED/FastLED)

MIT © [Matthew McCracken](https://github.com/mdm16c)
