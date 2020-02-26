# Marlin 2.0.x for Anycubic 4Max Pro

[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg?style=flat&color=blue)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=HYDQNE7EAQH3G&source=url)
[![Forum](https://img.shields.io/badge/Social-Forum-blue.svg)](https://drucktipps3d.de/forum/topic/anycubic-4max-pro)
[![Gitter](https://img.shields.io/gitter/room/marlin-a4maxpro/development?color=blue)](https://gitter.im/marlin-a4maxpro/development?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)
[![Latest Release](https://img.shields.io/github/release/Poket-Jony/Marlin-A4MaxPro-2.0.x.svg?style=flat&color=blue)](https://github.com/Poket-Jony/Marlin-A4MaxPro-2.0.x/releases/latest/)
[![GitHub stars](https://img.shields.io/github/stars/Poket-Jony/Marlin-A4MaxPro-2.0.x?style=flat&color=brightgreen)](https://github.com/Poket-Jony/Marlin-A4MaxPro-2.0.x/stargazers)
[![Downloads](https://img.shields.io/github/downloads/Poket-Jony/Marlin-A4MaxPro-2.0.x/total.svg?style=flat&color=brightgreen)](https://github.com/Poket-Jony/Marlin-A4MaxPro-2.0.x/releases)
[![Open Issues](https://img.shields.io/github/issues-raw/Poket-Jony/Marlin-A4MaxPro-2.0.x.svg?style=flat&color=yellowgreen)](https://github.com/Poket-Jony/Marlin-A4MaxPro-2.0.x/issues?q=is%3Aopen+is%3Aissue)
[![Closed Issues](https://img.shields.io/github/issues-closed-raw/Poket-Jony/Marlin-A4MaxPro-2.0.x.svg?style=flat&color=brightgreen)](https://github.com/Poket-Jony/Marlin-A4MaxPro-2.0.x/issues?q=is%3Aissue+is%3Aclosed)
[![Travis CI](https://api.travis-ci.org/Poket-Jony/Marlin-A4MaxPro-2.0.x.svg?branch=master)](https://travis-ci.org/Poket-Jony/Marlin-A4MaxPro-2.0.x)


This is the newest version of the [Marlin Firmware](https://github.com/MarlinFirmware/Marlin), customized and optimized for the 4Max Pro based on [davidramiro](https://github.com/davidramiro/Marlin-Ai3M-2.0.x), [derhopp](https://github.com/derhopp/Marlin-with-Anycubic-i3-Mega-TFT) and [alfrank](https://drucktipps3d.de/forum/topic/anycubic-4max-pro-marlin-1-1-9-firmware-ai3m-basierend/) changes.

## Why should use this firmware?
Anycubic's touchscreen implementation is very hacked together and is based on the old Marlin beta version 1.1.0-RC8.
In addition, the wrong thermistor for the hotend is entered in the stock firmware, which has been fixed in this version.
Also if your hotbed is concave or not straight you can use the [mesh bed leveling](https://github.com/davidramiro/Marlin-Ai3M-2.0.x#manual-mesh-bed-leveling).

## How to use?
**Warning: If your 4Max Pro works satisfactorily for you there is no reason to do a firmware update.**
**Remember: There is always a way back to the original firmware [Anycubic 1.1.7 (Marlin 1.1.0-RC8)](https://drive.google.com/file/d/1FwKHQcOxPabLgirkihu3LnBMuHuZLqZR/view).**

### Use precompiled hex:
If you don't want to change the firmware yourself, download the latest `.hex` file from the [releases](https://github.com/Poket-Jony/Marlin-A4MaxPro/releases).

### Or compile it yourself:
- Download and install [Arduino IDE](https://www.arduino.cc/en/main/software)
- Clone or download this repo with `git clone https://github.com/Poket-Jony/Marlin-A4MaxPro-2.0.x.git`
- Browse into the Marlin folder and open `Marlin.ino` with Arduino IDE
- [Customize if needed](http://marlinfw.org/docs/configuration/configuration.html#configuring-marlin)
(`Configuration.h` and `Configuration_adv.h` files are located in Marlin folder)
- In the Arduino IDE, under `Tools -> Board` menu select `Genuino Mega 2560` and `ATmega2560`
- Under `Sketch` menu, select `Export compiled binary`
- Look for the `.hex` files in the Marlin directory (only use the `Marlin.ino.hex`, not the `Marlin.ino.with_bootloader.hex`!)

#### BLTouch v3.1
- copy the config files from `/config/examples/Anycubic4MaxPro/A4MaxProBLTouch/` to `/Marlin/`
- replace `NOZZLE_TO_PROBE_OFFSET` values with your current BLTouch mount position

### After obtaining the `.hex` file
Flash your printer with obtained hex file. After flashing the firmware, no matter which way, you have to reset all configurable settings to their factory defaults using a terminal program (OctoPrint, [Pronterface](https://www.pronterface.com/), Repetier Host, ...):

- connect the printer via USB cable
- open the terminal program, select the appropriate USB serial interface (on Mac: `SLAB_USBtoUART`)
- change `baud rate` or `Baudrate` to `250000 bps` _(the original Anycubic firmware is set to a baud rate of `115200 bps`)_
- connect and wait for the EEPROM values to be output
- send the following commands: `M502` (Factory Reset) and `M500` (Save Settings)
- now you can disconnect the printer, for safety's turn the printer off and on again.
- the new firmware version is shown in the printer display


**The latest CP210x USB drivers for your printer can be downloaded [here](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers).**

## Calibration
***Do NOT skip this section! Your 3D printer is exceptionally accurate piece of equipment BUT ONLY if it is calibrated!***

- **Optional:** (To avoid warping) Stock fan duct replacement (Ex: [Vortex Fan Duct](https://www.thingiverse.com/thing:3772311) or [Dowble side fan duct](https://www.thingiverse.com/thing:3763851)).
- **Mandatory:** Check hotend termistor - it can be loose! Try to slightly pool or push termistor's wires. If termistor moves freely - slide it all the way in the heater block. Clamp the brass tube around termistor's wires a little to secure it.
- **Mandatory:** [Extruder PIDs auto tuning](https://github.com/davidramiro/Marlin-Ai3M/wiki/Calibration#pid-tuning)
- **Mandatory:** [Extruder steps calibration](https://github.com/davidramiro/Marlin-Ai3M/wiki/Calibration#extruder-steps)
- **Recommended:** [Manual Mesh Bed Leveling](https://github.com/davidramiro/Marlin-Ai3M#manual-mesh-bed-leveling)
- **Recommended:** [Check FAQ in davidramiro's repo](https://github.com/davidramiro/Marlin-AI3M/wiki/Frequently-Asked-Questions)

### Linear Advance
[Marlin Documentation](https://marlinfw.org/docs/features/lin_advance.html)

- To calibrate your linear advance K-factor you can use [this form](https://marlinfw.org/tools/lin_advance/k-factor.html).
- Linear advance K-factor should be calibrated for every material which you use. To set new K-factor use `M900` command **OR**
- Use Linear Advance Settings plugin for Cura to use specific K-factor value in your profiles (or leave it `0` to disable Linear Advance). Can be found in Material tab.

## Features
### Filament Runout
As soon as the filament is empty when printing, a message appears on the display and the printer removes the remaining filament. Please insert a new one and press "Continue". (Sometimes the command is not transmitted correctly, then first press "Pause" and then "Continue") Now the new filament is drawn in and printing continues.

### Advanced Pause
If you press "Pause" while printing, it stops and your print head moves to the waiting position. If you want to continue printing, press "Continue". Now the printhead is heated up and then moves back into position.

### Mesh Leveling
Due to the concave print bed on the Anycubic, you can use the mesh leveling to fix the unevenness. Insert an SD card first and then go to the "Extra Menu" in the print menu. Select "start mesh leveling" there. The print head now moves to the first position. Place a sheet of paper under the nozzle and select "z up" or "z down" on the next page until you notice a slight rubbing on the paper. Now press "next mesh point" and repeat the process. As soon as you have reached the last point, the print head returns to the home position and you can save the new values by clicking on "save eeprom". Don't forget to integrate the mesh leveling into your gcode start script.

## Credits
Marlin-A4MaxPro:
- Jonas Plamann [[@Poket-Jony](https://github.com/Poket-Jony)]
- Ruslan Kolosovskyi [[@rkolosovskyi](https://github.com/rkolosovskyi)]
- Bernhard Berger [[@bernhardberger](https://github.com/bernhardberger)]
- [[@mpk](https://drucktipps3d.de/forum/profile/mpk)]
- [[@m-kozlowski](https://github.com/m-kozlowski)]
- [[@whitecube](https://drucktipps3d.de/forum/profile/whitecube)]

Marlin-Ai3M:
- David Ramiro [[@davidramiro](https://github.com/davidramiro)]

Marlin:
 - Scott Lahteine [[@thinkyhead](https://github.com/thinkyhead)]
 - Roxanne Neufeld [[@Roxy-3D](https://github.com/Roxy-3D)]
 - Chris Pepper [[@p3p](https://github.com/p3p)]
 - Bob Kuhn [[@Bob-the-Kuhn](https://github.com/Bob-the-Kuhn)]
 - João Brazio [[@jbrazio](https://github.com/jbrazio)]
 - Erik van der Zalm [[@ErikZalm](https://github.com/ErikZalm)]
 - Alexey Shvetsov [[@alexxy](https://github.com/alexxy)]
 - Andreas Hardtung [[@AnHardt](https://github.com/AnHardt)]
 - Ben Lye [[@benlye](https://github.com/benlye)]
 - Bernhard Kubicek [[@bkubicek](https://github.com/bkubicek)]
 - Bob Cousins [[@bobc](https://github.com/bobc)]
 - Petr Zahradnik [[@clexpert](https://github.com/clexpert)]
 - Jochen Groppe [[@CONSULitAS](https://github.com/CONSULitAS)]
 - David Braam [[@daid](https://github.com/daid)]
 - Eduardo José Tagle [[@ejtagle](https://github.com/ejtagle)]
 - Ernesto Martinez [[@emartinez167](https://github.com/emartinez167)]
 - Edward Patel [[@epatel](https://github.com/epatel)]
 - F. Malpartida [[@fmalpartida](https://github.com/fmalpartida)]
 - Kai [[@Kaibob2](https://github.com/Kaibob2)]
 - Luc Van Daele [[@LVD-AC](https://github.com/LVD-AC)]
 - Alberto Cotronei [[@MagoKimbra](https://github.com/MagoKimbra)]
 - Marcio Teixeira [[@marcio-ao](https://github.com/marcio-ao)]
 - Chris Palmer [[@nophead](https://github.com/nophead)]
 - Steeve Spaggi [[@studiodyne](https://github.com/studiodyne)]
 - Thomas Moore [[@tcm0116](https://github.com/tcm0116)]
 - Teemu Mäntykallio [[@teemuatlut](https://github.com/teemuatlut)]
 - Nico Tonnhofer [[@Wurstnase](https://github.com/Wurstnase)]
 - [[@android444](https://github.com/android444)]
 - [[@bgort](https://github.com/bgort)]
 - [[@GMagician](https://github.com/GMagician)]
 - [[@Grogyan](https://github.com/Grogyan)]
 - [[@maverikou](https://github.com/maverikou)]
 - [[@oysteinkrog](https://github.com/oysteinkrog)]
 - [[@paclema](https://github.com/paclema)]
 - [[@paulusjacobus](https://github.com/paulusjacobus)]
 - [[@psavva](https://github.com/psavva)]
 - [[@Tannoo](https://github.com/Tannoo)]
 - [[@teemuatlut](https://github.com/teemuatlut)]
 - ...and many others

## License
Marlin is published under the [GPLv3 license](https://github.com/MarlinFirmware/Marlin/blob/1.0.x/COPYING.md) because we believe in open development. The GPL comes with both rights and obligations. Whether you use Marlin firmware as the driver for your open or closed-source product, you must keep Marlin open, and you must provide your compatible Marlin source code to end users upon request. The most straightforward way to comply with the Marlin license is to make a fork of Marlin on Github, perform your modifications, and direct users to your modified fork.

## Disclaimer
```
/*
* Flashing a custom firmware happens at your own risk.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS
* AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
* THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
* IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
```
