# Arduino Code for DCS KA-50 and A10-C radio

This code allows me to export the radio frequencies from DCS (Flight Simulator PC game) to 7-segment LED displays and change them using physical rotary encoders, all connected to an Arduino Nano.

## Libraries used
| Library | GitHub link|
| ------ | ------ |
| DCS-BIOS | https://github.com/dcs-bios |
| LedControl | https://github.com/wayoda/LedControl |

## Why?
I play DCS in multiplayer servers that usually have two distinct teams (Blue and Red) which have preset objectives like capturing bases, airfields etc. Since players fly different airframes with different roles and capabilities like Air Patrol, Ground Strike, Close Air Support, setting up SAM Sites and so on, communications become vital especially when there are over 30 players in the same team.

Therefore, most players have to listen and/or speak on multiple radio frequencies at the same time and switch between radios and frequencies as needed. For example, a helicopter pilot deploying air defences must listen to human GCI and friendlies doing Air Patrol but also listen and communicate with other helicopter pilots in order to coordinate with them.

Having physical switches allows for faster setup time and a better game experience overall.

Also, the slightest excuse to tinker with electronics and software is more than enough for me.

## How?
The best way I know is to use DCS-BIOS to export data from the game in real time and to change it using external switches and rotary encoders. I decided I will use an Arduino Nano since it is compact and has a good amount of I/O pins.

The LedControl library allows for easy control of the MAX7219 IC based 7-segment displays. They only require 3 pins plus power and can be daisy-chained in series to up to 8.
However, when having them in series, the input voltage will drop slightly for each consecutive display but I'm only using 2 so it's not an issue.
I also placed a 1k ohm resistor in series with the 'Data In' connector to prevent the displays from showing a false reading when changing frequencies fast.

The 7-segment displays and the rotary encoders sit on a custom board that I designed and 3D printed and which it is fastened to the throttle body of my HOTAS.
