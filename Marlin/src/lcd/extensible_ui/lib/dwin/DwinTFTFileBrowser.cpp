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

#include "../../../../inc/MarlinConfigPre.h"

#if BOTH(DWIN_TFT, SDSUPPORT)

#include "../../../../sd/cardreader.h"
#include "../../ui_api.h"

#include "DwinTFTFileBrowser.h"
#include "DwinTFTSerial.h"
#include "DwinTFTCommand.h"

static ExtUI::FileList fileList;

DwinTFTFileBrowserClass DwinTFTFileBrowser;

DwinTFTFileBrowserClass::DwinTFTFileBrowserClass()
{
  
}

void DwinTFTFileBrowserClass::reset()
{
  selectedFilename[0] = '\0';
  selectedDirectory[0] = '\0';
}

void DwinTFTFileBrowserClass::listFiles()
{
  if(!ExtUI::isMediaInserted()) {
    DWIN_TFT_SERIAL_PROTOCOLPGM(DWIN_TFT_TX_SD_CARD_NOT_INSERTED); //no sd card found
    DWIN_TFT_SERIAL_ENTER();
    return;
  }

  uint16_t itemPos = 0;
  if(DwinTFTCommand.codeSeen('S')) {
    itemPos = DwinTFTCommand.codeValue();
  }

  DWIN_TFT_SERIAL_PROTOCOLPGM(DWIN_TFT_TX_SD_CARD_FILE_LIST_START); // Filelist start
  DWIN_TFT_SERIAL_ENTER();

  if(strcasecmp_P(selectedDirectory, PSTR(EXTRA_MENU)) == 0) {
    buildExtraMenu(itemPos);
  } else if(strcasecmp_P(selectedDirectory, PSTR(DEBUG_MENU)) == 0) {
    buildDebugMenu(itemPos);
  } else {
    uint16_t itemCount = fileList.count();
    uint16_t maxItems = 0;
    if(itemPos == 0) {
      if(!fileList.isAtRootDir()) {
        DWIN_TFT_SERIAL_PROTOCOLLNPGM(DIR_UP);
        DWIN_TFT_SERIAL_PROTOCOLLNPGM(DIR_UP);
        maxItems = constrain(3, 1, itemCount);
      } else {
        DWIN_TFT_SERIAL_PROTOCOLLNPGM(EXTRA_MENU);
        DWIN_TFT_SERIAL_PROTOCOLLNPGM(EXTRA_MENU);
        maxItems = constrain(3, 1, itemCount);
      }
    } else {
      itemPos--; //items above zero are counted regular
      maxItems = constrain(itemPos + 4, 0, itemCount);
    }
    
    for(uint16_t pos = itemPos; pos < maxItems; pos++) {
      fileList.seek(pos);

      if(fileList.isDir()) {
        DWIN_TFT_SERIAL_PROTOCOL(fileList.shortFilename());
        DWIN_TFT_SERIAL_PROTOCOLLNPGM("/");
        DWIN_TFT_SERIAL_PROTOCOL(fileList.filename());
        DWIN_TFT_SERIAL_PROTOCOLLNPGM("/");
        SERIAL_ECHO(pos);
        SERIAL_ECHOPGM(":");
        SERIAL_ECHO(fileList.filename());
        SERIAL_ECHOLNPGM("/");
      } else {
        DWIN_TFT_SERIAL_PROTOCOLLN(fileList.shortFilename());
        DWIN_TFT_SERIAL_PROTOCOLLN(fileList.filename());
        SERIAL_ECHO(pos);
        SERIAL_ECHOPGM(":");
        SERIAL_ECHOLN(fileList.filename());
      }
    }
  }

  DWIN_TFT_SERIAL_PROTOCOLPGM(DWIN_TFT_TX_SD_CARD_FILE_LIST_END); // Filelist stop
  DWIN_TFT_SERIAL_ENTER();
  ExtUI::delay_ms(DWIN_TFT_UPDATE_INTERVAL_MS); // prohibits double entries
}

void DwinTFTFileBrowserClass::selectFile()
{
  if(!ExtUI::isMediaInserted()) {
    DWIN_TFT_SERIAL_PROTOCOLPGM(DWIN_TFT_TX_SD_CARD_NOT_INSERTED);
    DWIN_TFT_SERIAL_ENTER();
    return;
  }
  char *starpos = strchr(DwinTFTCommand.TFTstrchr_pointer + 4, '*');
  size_t lastCharPos = strlen(DwinTFTCommand.TFTstrchr_pointer) - 1;
  if (DwinTFTCommand.TFTstrchr_pointer[lastCharPos] == '/' && 
    DwinTFTCommand.TFTstrchr_pointer[4] == '.' && 
    DwinTFTCommand.TFTstrchr_pointer[5] == '.') { //dir up
    fileList.upDir();
    listFiles();
  } else if (DwinTFTCommand.TFTstrchr_pointer[lastCharPos] == '/') { //directory
    memcpy(selectedDirectory, DwinTFTCommand.TFTstrchr_pointer + 4, lastCharPos - 1);
    selectedDirectory[strlen(selectedDirectory) - 1] = '\0';
    fileList.changeDir(selectedDirectory);
    listFiles();
  } else if(strcasecmp_P(DwinTFTCommand.TFTstrchr_pointer + 4, PSTR(EXTRA_MENU)) == 0 || 
    strcasecmp_P(DwinTFTCommand.TFTstrchr_pointer + 4, PSTR(DEBUG_MENU)) == 0) {
    strcpy(selectedDirectory, DwinTFTCommand.TFTstrchr_pointer + 4);
    listFiles();
  } else if(DwinTFTCommand.TFTstrchr_pointer[4] == '<' && 
    DwinTFTCommand.TFTstrchr_pointer[lastCharPos] == '>') {
    strcpy(selectedFilename, DwinTFTCommand.TFTstrchr_pointer + 4);
    if(strcasecmp_P(selectedDirectory, PSTR(EXTRA_MENU)) == 0) {
      handleExtraMenu();
    } else if(strcasecmp_P(selectedDirectory, PSTR(DEBUG_MENU)) == 0) {
      handleDebugMenu();
    }
  } else {
    if(starpos != NULL) {
      *(starpos - 1) = '\0';
    }
    strcpy(selectedFilename, DwinTFTCommand.TFTstrchr_pointer + 4);
    card.openFileRead(selectedFilename);
    if(card.isFileOpen()) {
      DWIN_TFT_SERIAL_PROTOCOLPGM(DWIN_TFT_TX_SD_CARD_OPEN_SUCCESS); // J20 Open successful
      DWIN_TFT_SERIAL_ENTER();
      #ifdef DWIN_TFT_DEBUG
        SERIAL_ECHOLNPGM("TFT Serial Debug: File open successful... J20");
      #endif
    } else {
      DWIN_TFT_SERIAL_PROTOCOLPGM(DWIN_TFT_TX_SD_CARD_OPEN_FAILED); // J21 Open failed
      DWIN_TFT_SERIAL_ENTER();
      #ifdef DWIN_TFT_DEBUG
        SERIAL_ECHOLNPGM("TFT Serial Debug: File open failed... J21");
      #endif
    }
  }
  DWIN_TFT_SERIAL_ENTER();
}

void DwinTFTFileBrowserClass::refreshFileList()
{
  reset();
  if(!ExtUI::isMediaInserted()) {
    DWIN_TFT_SERIAL_PROTOCOLPGM(DWIN_TFT_TX_SD_CARD_NOT_INSERTED);
    DWIN_TFT_SERIAL_ENTER();
    return;
  }
  while (!fileList.isAtRootDir()) {
    fileList.upDir();
  }
  listFiles();
}

void DwinTFTFileBrowserClass::buildExtraMenu(uint16_t pos)
{
  if(pos % 4 != 0) { //check if pos is divisible by 4
    return;
  }
  switch (int(pos / 4)) //max display 4 items per page
  {
    case 0:
      DWIN_TFT_SERIAL_PROTOCOLLNPGM_LOOP(EXTRA_MENU_DIR_UP);
      #ifdef DWIN_TFT_DEBUG
        DWIN_TFT_SERIAL_PROTOCOLLNPGM_LOOP(DEBUG_MENU);
      #else
        DWIN_TFT_SERIAL_PROTOCOLLNPGM_LOOP(EXTRA_MENU_SPACER);
      #endif
      DWIN_TFT_SERIAL_PROTOCOLLNPGM_LOOP(EXTRA_MENU_AUTO_TUNE_HOTEND_PID);
      DWIN_TFT_SERIAL_PROTOCOLLNPGM_LOOP(EXTRA_MENU_AUTO_TUNE_HOTBED_PID);
      break;
    case 1:
      DWIN_TFT_SERIAL_PROTOCOLLNPGM_LOOP(EXTRA_MENU_SAVE_EEPROM);
      DWIN_TFT_SERIAL_PROTOCOLLNPGM_LOOP(EXTRA_MENU_LOAD_FW_DEFAULTS);
      DWIN_TFT_SERIAL_PROTOCOLLNPGM_LOOP(EXTRA_MENU_SPACER);
      DWIN_TFT_SERIAL_PROTOCOLLNPGM_LOOP(EXTRA_MENU_SPACER);
      break;
    case 2:
      DWIN_TFT_SERIAL_PROTOCOLLNPGM_LOOP(EXTRA_MENU_PREHEAT_BED);
      #ifndef BLTOUCH
        DWIN_TFT_SERIAL_PROTOCOLLNPGM_LOOP(EXTRA_MENU_START_MESH_LEVELING);
        DWIN_TFT_SERIAL_PROTOCOLLNPGM_LOOP(EXTRA_MENU_NEXT_MESH_POINT);
        DWIN_TFT_SERIAL_PROTOCOLLNPGM_LOOP(EXTRA_MENU_SPACER);
      #else
        DWIN_TFT_SERIAL_PROTOCOLLNPGM_LOOP(EXTRA_MENU_START_BLTOUCH_LEVELING);
        DWIN_TFT_SERIAL_PROTOCOLLNPGM_LOOP(EXTRA_MENU_SPACER);
        DWIN_TFT_SERIAL_PROTOCOLLNPGM_LOOP(EXTRA_MENU_SPACER);
      #endif
      break;
    case 3:
      DWIN_TFT_SERIAL_PROTOCOLLNPGM_LOOP(EXTRA_MENU_Z_UP_01);
      DWIN_TFT_SERIAL_PROTOCOLLNPGM_LOOP(EXTRA_MENU_Z_UP_002);
      DWIN_TFT_SERIAL_PROTOCOLLNPGM_LOOP(EXTRA_MENU_Z_DOWN_002);
      DWIN_TFT_SERIAL_PROTOCOLLNPGM_LOOP(EXTRA_MENU_Z_DOWN_01);
    default: // if last page has 4 items, then is next page empty
      break;
  }
}

void DwinTFTFileBrowserClass::buildDebugMenu(uint16_t pos)
{
  #ifdef DWIN_TFT_DEBUG
    if(pos % 4 != 0) { //check if pos is divisible by 4
      return;
    }
    switch (int(pos / 4)) //max display 4 items per page
    {
      case 0:
        DWIN_TFT_SERIAL_PROTOCOLLNPGM_LOOP(EXTRA_MENU_DIR_UP);
        DWIN_TFT_SERIAL_PROTOCOLLNPGM_LOOP(DEBUG_MENU_TEST_DISPLAY_TX_COMMANDS);
        DWIN_TFT_SERIAL_PROTOCOLLNPGM_LOOP(DEBUG_MENU_TEST_DISPLAY_INTERACTION);
        break;
      default: // if last page has 4 items, then is next page empty
        break;
    }
  #endif
}

void DwinTFTFileBrowserClass::handleExtraMenu()
{
  if(strcasecmp_P(selectedFilename, PSTR(EXTRA_MENU_DIR_UP)) == 0) {
    reset();
    listFiles();
    return;
  } else if (strcasecmp(selectedFilename, EXTRA_MENU_AUTO_TUNE_HOTEND_PID) == 0) {
    SERIAL_ECHOLNPGM("Extra Menu: Auto Tune Hotend PID");
    DwinTFT.gcodeNow_P(PSTR("M106 S204\nM303 E0 S210 C15 U1"));
  } else if (strcasecmp(selectedFilename, EXTRA_MENU_AUTO_TUNE_HOTBED_PID) == 0) {
    SERIAL_ECHOLNPGM("Extra Menu: Auto Tune Hotbed PID");
    DwinTFT.gcodeNow_P(PSTR("M303 E-1 S60 C6 U1"));
  } else if (strcasecmp(selectedFilename, EXTRA_MENU_SAVE_EEPROM) == 0) {
    SERIAL_ECHOLNPGM("Extra Menu: Save EEPROM");
    DwinTFT.gcodeNow_P(DWIN_TFT_GCODE_M500);
  } else if (strcasecmp(selectedFilename, EXTRA_MENU_LOAD_FW_DEFAULTS) == 0) {
    SERIAL_ECHOLNPGM("Extra Menu: Load FW Defaults");
    DwinTFT.gcodeNow_P(DWIN_TFT_GCODE_M502);
  } else if (strcasecmp(selectedFilename, EXTRA_MENU_PREHEAT_BED) == 0) {
    SERIAL_ECHOLNPGM("Extra Menu: Preheat Bed");
    DwinTFT.gcodeNow_P(PSTR("M140 S60"));
  } else if (strcasecmp(selectedFilename, EXTRA_MENU_START_MESH_LEVELING) == 0) {
    SERIAL_ECHOLNPGM("Extra Menu: Start Mesh Leveling");
    DwinTFT.gcodeNow_P(PSTR("G29 S1"));
  } else if (strcasecmp(selectedFilename, EXTRA_MENU_NEXT_MESH_POINT) == 0) {
    SERIAL_ECHOLNPGM("Extra Menu: Next Mesh Point");
    DwinTFT.gcodeNow_P(PSTR("G29 S2"));
  } else if(strcasecmp(selectedFilename, EXTRA_MENU_Z_UP_01) == 0) {
    SERIAL_ECHOLNPGM("Extra Menu: Z Up 0.1");
    DwinTFT.gcodeQueue_P(DWIN_TFT_GCODE_G91);
    DwinTFT.gcodeQueue_P(PSTR("G0 Z-0.1"));
    DwinTFT.gcodeQueue_P(DWIN_TFT_GCODE_G90);
  } else if (strcasecmp(selectedFilename, EXTRA_MENU_Z_UP_002) == 0) {
    SERIAL_ECHOLNPGM("Extra Menu: Z Up 0.02");
    DwinTFT.gcodeQueue_P(DWIN_TFT_GCODE_G91);
    DwinTFT.gcodeQueue_P(PSTR("G0 Z-0.02"));
    DwinTFT.gcodeQueue_P(DWIN_TFT_GCODE_G90);
  } else if (strcasecmp(selectedFilename, EXTRA_MENU_Z_DOWN_002) == 0) {
    SERIAL_ECHOLNPGM("Extra Menu: Z Down 0.02");
    DwinTFT.gcodeQueue_P(DWIN_TFT_GCODE_G91);
    DwinTFT.gcodeQueue_P(PSTR("G0 Z0.02"));
    DwinTFT.gcodeQueue_P(DWIN_TFT_GCODE_G90);
  } else if(strcasecmp(selectedFilename, EXTRA_MENU_Z_DOWN_01) == 0) {
    SERIAL_ECHOLNPGM("Extra Menu: Z Down 0.1");
    DwinTFT.gcodeQueue_P(DWIN_TFT_GCODE_G91);
    DwinTFT.gcodeQueue_P(PSTR("G0 Z0.1"));
    DwinTFT.gcodeQueue_P(DWIN_TFT_GCODE_G90);
  } else if (strcasecmp(selectedFilename, EXTRA_MENU_START_BLTOUCH_LEVELING) == 0) {
    SERIAL_ECHOLNPGM("Extra Menu: Start BLTouch Leveling");
    DwinTFT.gcodeNow_P(PSTR("G28\nG29"));
  } else { //do nothing for spacer
    return;
  }
  DwinTFT.playInfoTone();
}

void DwinTFTFileBrowserClass::handleDebugMenu()
{
  #ifdef DWIN_TFT_DEBUG
    if(strcasecmp_P(selectedFilename, PSTR(EXTRA_MENU_DIR_UP)) == 0) {
      reset();
      strcpy(selectedDirectory, EXTRA_MENU);
      listFiles();
      return;
    } else if (strcasecmp(selectedFilename, DEBUG_MENU_TEST_DISPLAY_TX_COMMANDS) == 0) {
      char value[4];
      sprintf(value, "J%02d", debugDisplayTxCommand);
      DWIN_TFT_SERIAL_PROTOCOLLN(value);
      SERIAL_ECHOLNPAIR("Debug Menu: test display tx commands... ", value);
      debugDisplayTxCommand++;
    } else if(strcasecmp(selectedFilename, DEBUG_MENU_TEST_DISPLAY_INTERACTION) == 0) {
      DwinTFT.waitForUserConfirm();
      SERIAL_ECHOLNPGM("Debug Menu: test display interaction");
    } else { //do nothing for spacer
      return;
    }
    DwinTFT.playInfoTone();
  #endif
}

#endif
