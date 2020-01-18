# Marlin 2.0.x (Ai3M-2.0.x based) for Anycubic 4Max Pro

[![Downloads](https://img.shields.io/github/downloads/rkolosovskyi/Marlin-A4MaxPro-2.0.x/total.svg?style=flat)](https://github.com/rkolosovskyi/Marlin-A4MaxPro-2.0.x/releases) [![Open Issues](https://img.shields.io/github/issues-raw/rkolosovskyi/Marlin-A4MaxPro-2.0.x.svg?style=flat)](https://github.com/rkolosovskyi/Marlin-A4MaxPro-2.0.x/issues?q=is%3Aopen+is%3Aissue) [![License](https://img.shields.io/github/license/rkolosovskyi/Marlin-A4MaxPro-2.0.x.svg?style=flat)](https://github.com/rkolosovskyi/Marlin-A4MaxPro-2.0.x/blob/master/LICENSE) [![Latest Release](https://img.shields.io/github/release/rkolosovskyi/Marlin-A4MaxPro-2.0.x.svg?style=flat)](https://github.com/rkolosovskyi/Marlin-A4MaxPro-2.0.x/releases/latest/) [![Last commit](https://img.shields.io/github/last-commit/rkolosovskyi/Marlin-A4MaxPro-2.0.x.svg?style=flat)](https://github.com/rkolosovskyi/Marlin-A4MaxPro-2.0.x/commits/)  [![Travis CI](https://api.travis-ci.org/rkolosovskyi/Marlin-A4MaxPro-2.0.x.svg?branch=master)](https://travis-ci.org/rkolosovskyi/Marlin-A4MaxPro-2.0.x)  

**Beta build - use with caution!**

This is the newest version of the [Marlin Firmware](https://github.com/MarlinFirmware/Marlin), customized and optimized for the 4Max Pro based on [davidramiro's Ai3M-2.0.x repo](https://github.com/davidramiro/Marlin-Ai3M-2.0.x) and [alfrank's changes](https://drucktipps3d.de/forum/topic/anycubic-4max-pro-marlin-1-1-9-firmware-ai3m-basierend/) for the Anycubic 4Max Pro. The DWIN TFT screen is based on [derhopp's repo](https://github.com/derhopp/Marlin-with-Anycubic-i3-Mega-TFT) with his remarkable efforts to get this working with the latest versions of Marlin.

**Make sure to take a look at the [Wiki](https://github.com/davidramiro/Marlin-Ai3M-2.0.x/wiki/) in [davidramiro's Ai3M-2.0.x repo](https://github.com/davidramiro/Marlin-Ai3M-2.0.x) and also the [FAQ](https://github.com/davidramiro/Marlin-Ai3M-2.0.x/wiki/Frequently-Asked-Questions).**

## Why should use this firmware?
Anycubic's touchscreen implementation is very hacked together and is based on the old Marlin beta version 1.1.0-RC8.
In addition, the wrong thermistor for the hotend is entered in the stock firmware, which has been fixed in this version.
Also if your hotbed is concave or not straight you can use the [mesh bed leveling](https://github.com/davidramiro/Marlin-Ai3M-2.0.x#manual-mesh-bed-leveling).

## How to use?
**Warning: If your 4Max Pro works satisfactorily for you there is no reason to do a firmware update.**

- There is always a way back to the original firmware. Before the update, please note the currently installed version: Menu Tools / About / Firmware Version on the display of the printer.
- If you don't want to change the firmware yourself, you can simply use Cura to load the latest `.hex` file from the [release](https://github.com/Poket-Jony/Marlin-A4MaxPro/releases).
- If you want to go back to the Original Anycubic 1.1.7 (Marlin 1.1.0-RC8) firmware download it from [here](https://drive.google.com/file/d/1FwKHQcOxPabLgirkihu3LnBMuHuZLqZR/view)
- After flashing the firmware, no matter which way, you have to reset and save the EEPROM values using a terminal program (e.g. [Pronterface](https://www.pronterface.com/)).
    - connect the printer to the computer via USB cable
    - open the terminal program, select the appropriate USB serial interface (on Mac: `SLAB_USBtoUART`)
    - change `baud rate` or `Baudrate` to `250000 bps`
    - connect and wait for the EEPROM values to be output
    - then enter the following: `M502` and `M500`
- Now you can disconnect again, for safety's turn the printer off and on again.
- The new firmware is shown in the printer display (see above) as `v2.0.0`.

#### Info: The original Anycubic firmware is set to a baud rate of `115200 bps`.

## Known Issues
#### [Marlin-A4MaxPro-2.0.x/v1.4.5](https://github.com/Poket-Jony/Marlin-A4MaxPro-2.0.x/releases/tag/v1.4.5)
- LED control: It would be better to enable `case lights` menu option with PWM control
- Light flickers when printing
- PID from the hotend no longer fits => Can be fixed by [PID tuning](https://github.com/davidramiro/Marlin-Ai3M-2.0.x/wiki/Calibration#pid-tuning)

#### [Marlin-Ai3M-2.0.x/v1.4.5](https://github.com/davidramiro/Marlin-Ai3M-2.0.x/releases/tag/v1.4.5)

#### [Marlin/2.0.0](https://github.com/MarlinFirmware/Marlin/releases/tag/2.0.0)
- Mixing Extruder with G10/G11 may have quirks
- Sensor-less probing is still pretty experimental

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
