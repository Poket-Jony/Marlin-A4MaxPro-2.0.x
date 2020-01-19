# Marlin 2.0.x (Ai3M-2.0.x based) for Anycubic 4Max Pro

[![Downloads](https://img.shields.io/github/downloads/rkolosovskyi/Marlin-A4MaxPro-2.0.x/total.svg?style=flat)](https://github.com/rkolosovskyi/Marlin-A4MaxPro-2.0.x/releases) [![Open Issues](https://img.shields.io/github/issues-raw/rkolosovskyi/Marlin-A4MaxPro-2.0.x.svg?style=flat)](https://github.com/rkolosovskyi/Marlin-A4MaxPro-2.0.x/issues?q=is%3Aopen+is%3Aissue) [![License](https://img.shields.io/github/license/rkolosovskyi/Marlin-A4MaxPro-2.0.x.svg?style=flat)](https://github.com/rkolosovskyi/Marlin-A4MaxPro-2.0.x/blob/master/LICENSE) [![Latest Release](https://img.shields.io/github/release/rkolosovskyi/Marlin-A4MaxPro-2.0.x.svg?style=flat)](https://github.com/rkolosovskyi/Marlin-A4MaxPro-2.0.x/releases/latest/) [![Last commit](https://img.shields.io/github/last-commit/rkolosovskyi/Marlin-A4MaxPro-2.0.x.svg?style=flat)](https://github.com/rkolosovskyi/Marlin-A4MaxPro-2.0.x/commits/)  [![Travis CI](https://api.travis-ci.org/rkolosovskyi/Marlin-A4MaxPro-2.0.x.svg?branch=master)](https://travis-ci.org/rkolosovskyi/Marlin-A4MaxPro-2.0.x)  

## Beta build - use with caution!

This is the newest version of the [Marlin Firmware](https://github.com/MarlinFirmware/Marlin), customized and optimized for the 4Max Pro 3D printer, based on:
- [davidramiro's Ai3M-2.0.x repo](https://github.com/davidramiro/Marlin-Ai3M-2.0.x)
- [Poket-Jony's Marlin-A4MaxPro-2.0.x](https://github.com/Poket-Jony/Marlin-A4MaxPro-2.0.x)
- [alfrank's changes](https://drucktipps3d.de/forum/topic/anycubic-4max-pro-marlin-1-1-9-firmware-ai3m-basierend/)

The DWIN TFT screen is based on [derhopp's repo](https://github.com/derhopp/Marlin-with-Anycubic-i3-Mega-TFT) with his remarkable efforts to get this working with the latest versions of Marlin.

**!!!Warning!!! It's highly recommended to use Octoprint, Repetier, Printrun or any other software to manage you printer, instead of using factory display. If you want to use the factory display only to manage your printer - it's better for you to use stock firmware.

## How to flash this?

**There is always a way back to the original firmware!**

If you want to go back to the Original Anycubic 1.1.7 (Marlin 1.1.0-RC8) firmware download it from [here](https://drive.google.com/file/d/1FwKHQcOxPabLgirkihu3LnBMuHuZLqZR/view).

After flashing the firmware, no matter which way, you have to reset (load default) EEPROM values using a terminal program: (e.g. [Pronterface](https://www.pronterface.com/)):
- connect the printer to the computer via USB cable
- open the terminal program, select the appropriate USB serial interface (on Mac: `SLAB_USBtoUART`)
- change `baud rate` or `Baudrate` to `250000 bps`
- connect and wait for the EEPROM values to be output
- then send the following commands: `M502` and `M500`

### Use precompiled hex:
If you don't want to change the firmware yourself, download the latest `.hex` file from the [releases](https://github.com/rkolosovskyi/Marlin-A4MaxPro-2.0.x/releases).

### Or compile it yourself:

- Download and install [Arduino IDE](https://www.arduino.cc/en/main/software)
- Clone or download this repo
- Browse into the Marlin folder and run `Marlin.ino`
- In the IDE, under `Tools -> Board` select `Genuino Mega 2560` and `ATmega2560`
- Open Marlin.ino in the Marlin directory of this repo
- [Customize if needed](http://marlinfw.org/docs/configuration/configuration.html#configuring-marlin)
(**Configuration.h and Configuration_adv.h files are located in Marlin folder**)
- Under `Sketch`, select `Export compiled binary`
- Look for the .hex file in the Marlin directory (only use the `Marlin.ino.hex`, not the `Marlin.ino.with_bootloader.hex`!)

### After obtaining the hex file:

- Flash the hex with Cura, OctoPrint or similar
- Use a tool with a terminal (OctoPrint, Pronterface, Repetier Host, ...) to send commands to your printer.
- **Important** Connect to the printer and send the following commands:
- `M502` - load hard coded default values
- `M500` - save them to EEPROM

## Next steps

- **Optional:** Stock fan duct replacement (Ex: [Vortex Fan Duct](https://www.thingiverse.com/thing:3772311) or [Dowble side fan duct](https://www.thingiverse.com/thing:3763851)).
- **Mandatory:** [Extruder PID auto tuning](https://github.com/davidramiro/Marlin-Ai3M/wiki/Calibration#pid-tuning)
- **Mandatory:** [Extruder calibration](https://github.com/davidramiro/Marlin-Ai3M/wiki/Calibration#extruder-steps)
- **Recommended:** [Manual Mesh Bed Leveling](https://github.com/davidramiro/Marlin-Ai3M#manual-mesh-bed-leveling)
- **Recommended:** [Check FAQ in davidramiro's repo](https://github.com/davidramiro/Marlin-AI3M/wiki/Frequently-Asked-Questions)

## Credits
Marlin-Ai3M-2.0.x administrator:
- David Ramiro [[@davidramiro](https://github.com/davidramiro)]

Marlin-A4MaxPro-2.0.x contributors:
- [[@mpk](https://drucktipps3d.de/forum/profile/mpk/)]
- Jonas Plamann [[@Poket-Jony](https://github.com/Poket-Jony)]

Marlin-2.0.x dev team:
 - Scott Lahteine [[@thinkyhead](https://github.com/thinkyhead)]
 - Roxanne Neufeld [[@Roxy-3D](https://github.com/Roxy-3D)]
 - Chris Pepper [[@p3p](https://github.com/p3p)]
 - Bob Kuhn [[@Bob-the-Kuhn](https://github.com/Bob-the-Kuhn)]
 - João Brazio [[@jbrazio](https://github.com/jbrazio)]
 - Erik van der Zalm [[@ErikZalm](https://github.com/ErikZalm)]

Notable contributors include:
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
