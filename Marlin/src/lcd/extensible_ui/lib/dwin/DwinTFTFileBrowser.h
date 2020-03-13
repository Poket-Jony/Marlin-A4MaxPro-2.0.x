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
#include "../../../../sd/SdFatConfig.h"

#define DIR_UP "../"
#define EXTRA_MENU_DIR_UP "<../>"
#define EXTRA_MENU_SPACER "<--->"

#define EXTRA_MENU "<Extra Menu>"
#define EXTRA_MENU_AUTO_TUNE_HOTEND_PID "<auto tune hotend pid>"
#define EXTRA_MENU_AUTO_TUNE_HOTBED_PID "<auto tune hotbed pid>"
#define EXTRA_MENU_SAVE_EEPROM "<save eeprom>"
#define EXTRA_MENU_LOAD_FW_DEFAULTS "<load fw defaults>"
#define EXTRA_MENU_PREHEAT_BED "<preheat bed>"
#define EXTRA_MENU_START_BLTOUCH_LEVELING "<start bltouch leveling>"
#define EXTRA_MENU_START_MESH_LEVELING "<start mesh leveling>"
#define EXTRA_MENU_NEXT_MESH_POINT "<next mesh point>"
#define EXTRA_MENU_Z_UP_01 "<z up 0.1>"
#define EXTRA_MENU_Z_UP_002 "<z up 0.02>"
#define EXTRA_MENU_Z_DOWN_01 "<z down 0.1>"
#define EXTRA_MENU_Z_DOWN_002 "<z down 0.02>"

#define DEBUG_MENU "<Debug Menu>"
#define DEBUG_MENU_TEST_DISPLAY_TX_COMMANDS "<test display tx commands>"
#define DEBUG_MENU_TEST_DISPLAY_INTERACTION "<test display interaction>"

class DwinTFTFileBrowserClass {
private:
  uint8_t debugDisplayTxCommand = 0;
  void buildExtraMenu(uint16_t pos);
  void buildDebugMenu(uint16_t pos);
  void handleExtraMenu();
  void handleDebugMenu();
public:
  char selectedFilename[LONG_FILENAME_LENGTH];
  char selectedDirectory[LONG_FILENAME_LENGTH];
  DwinTFTFileBrowserClass();
  void reset();
  void listFiles();
  void selectFile();
  void refreshFileList();
};

extern DwinTFTFileBrowserClass DwinTFTFileBrowser;
