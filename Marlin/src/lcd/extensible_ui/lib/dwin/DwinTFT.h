/**
 * DWIN TFT Support for Anycubic i3 Mega and 4Max Pro
 * Based on the work of Christian Hopp and David Ramiro.
 * Copyright (c) 2020 by Jonas Plamann <https://github.com/Poket-Jony>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "../../../../inc/MarlinConfigPre.h"

#include <stdio.h>

#include "../../ui_api.h"

#define DWIN_TFT_UPDATE_INTERVAL_MS 250

char *itostr2(const uint8_t &x);

#ifndef ULTRA_LCD
char *itostr3(const int);
char *ftostr32(const float &);
#endif

const char DWIN_TFT_GCODE_G90[] PROGMEM = "G90";
const char DWIN_TFT_GCODE_G91[] PROGMEM = "G91";
const char DWIN_TFT_GCODE_M25[] PROGMEM = "M25";
const char DWIN_TFT_GCODE_M27[] PROGMEM = "M27";
const char DWIN_TFT_GCODE_M81[] PROGMEM = "M81";
const char DWIN_TFT_GCODE_M84[] PROGMEM = "M84";
const char DWIN_TFT_GCODE_M108[] PROGMEM = "M108";
const char DWIN_TFT_GCODE_M500[] PROGMEM = "M500";
const char DWIN_TFT_GCODE_M502[] PROGMEM = "M502";
const char DWIN_TFT_GCODE_M600[] PROGMEM = "M600";
const char DWIN_TFT_GCODE_MESH_START[] PROGMEM = "G29 S1";
const char DWIN_TFT_GCODE_MESH_NEXT[] PROGMEM = "G29 S2";
const char DWIN_TFT_GCODE_RETR_1[] PROGMEM = "G91\nG1 E-1 F1800\nG90";
const char DWIN_TFT_GCODE_RETR_3[] PROGMEM = "G1 E-3 F1800";
const char DWIN_TFT_GCODE_HOTEND_PID[] PROGMEM = "M106 S204\nM303 E0 S210 C15 U1";
const char DWIN_TFT_GCODE_HOTBED_PID[] PROGMEM = "M303 E-1 S60 C6 U1";
const char DWIN_TFT_GCODE_PREHEAT[] PROGMEM = "M140 S60";
const char DWIN_TFT_GCODE_UP_COARSE[] PROGMEM = "G91\nG1 Z+0.1\nG90";
const char DWIN_TFT_GCODE_DOWN_COARSE[] PROGMEM = "G91\nG1 Z-0.1\nG90";
const char DWIN_TFT_GCODE_UP_FINE[] PROGMEM = "G91\nG1 Z+0.02\nG90";
const char DWIN_TFT_GCODE_DOWN_FINE[] PROGMEM = "G91\nG1 Z-0.02\nG90";
const char DWIN_TFT_GCODE_PARK_RETR[] PROGMEM = "M125 L2";
const char DWIN_TFT_GCODE_RAIZE_Z_10[] PROGMEM = "G1 Z10";
const char DWIN_TFT_GCODE_HOME_ALL[] PROGMEM = "G28";
const char DWIN_TFT_GCODE_HOME_X[] PROGMEM = "G28 X";
const char DWIN_TFT_GCODE_HOME_Y[] PROGMEM = "G28 Y";
const char DWIN_TFT_GCODE_HOME_Z[] PROGMEM = "G28 Z";
const char DWIN_TFT_GCODE_INACTIVITY_ON[] PROGMEM = "M85 S600"; // 10 min
const char DWIN_TFT_GCODE_INACTIVITY_OFF[] PROGMEM = "M85 S0";

class DwinTFTClass {
public:
  bool autoPowerOff = true;
  DwinTFTClass();
  void init();
  void kill();
  void tick();
  void filamentRunout(const ExtUI::extruder_t extruder);
  void gcodeNow_P(PGM_P const gcode);
  void gcodeQueue_P(PGM_P const gcode);
  void gcodeQueue(const char* gcode);
  void onMediaInserted();
  void onMediaError();
  void onMediaRemoved();
  void onStatusChanged(const char * const msg);
  void onUserConfirmRequired(const char * const msg);
  bool isWaitingForUserConfirm();
  void waitForUserConfirm();
  void PowerDown();

private:
  bool caseLight = false;
  void receiveCommands();
  void loop();
  void checkPowerOff();
};

extern DwinTFTClass DwinTFT;
