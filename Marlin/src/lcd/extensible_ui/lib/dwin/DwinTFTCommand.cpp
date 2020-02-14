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

#if ENABLED(DWIN_TFT)

#include "Arduino.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../../MarlinCore.h"
#include "../../../../core/language.h"
#include "../../../../core/macros.h"
#include "../../../../core/serial.h"
#include "../../../../gcode/queue.h"
#include "../../../../feature/emergency_parser.h"
#include "../../../../feature/pause.h"
#include "../../../../libs/buzzer.h"
#include "../../../../module/planner.h"
#include "../../../../module/printcounter.h"
#include "../../../../module/stepper.h"
#include "../../../../module/temperature.h"
#include "../../../../sd/cardreader.h"
#include "../../ui_api.h"

#include "DwinTFTCommand.h"
#include "DwinTFT.h"
#include "DwinTFTSerial.h"
#include "DwinTFTFileBrowser.h"

DwinTFTCommandClass DwinTFTCommand;

DwinTFTCommandClass::DwinTFTCommandClass()
{
  
}

void DwinTFTCommandClass::handleCommand(DwinTFTCommandsRx command)
{
  switch(command) {
    case DWIN_TFT_RX_GET_HOTEND_TEMP: //A0 GET HOTEND TEMP
      sendGetHotendTemp();
      break;
    case DWIN_TFT_RX_GET_HOTEND_TARGET_TEMP: //A1  GET HOTEND TARGET TEMP
      sendGetHotendTargetTemp();
      break;
    case DWIN_TFT_RX_GET_HOTBED_TEMP: //A2 GET HOTBED TEMP
      sendGetHotbedTemp();
      break;
    case DWIN_TFT_RX_GET_HOTBED_TARGET_TEMP: //A3 GET HOTBED TARGET TEMP
      sendGetHotbedTargetTemp();
      break;
    case DWIN_TFT_RX_GET_FAN_SPEED://A4 GET FAN SPEED
      sendGetFanSpeed();
      break;
    case DWIN_TFT_RX_GET_CURRENT_COORDINATES:// A5 GET CURRENT COORDINATE
      sendGetCurrentCoordinates();
      break;
    case DWIN_TFT_RX_GET_SD_CARD_PRINT_STATUS: //A6 GET SD CARD PRINTING STATUS
      sendGetSDCardPrintingStatus();
      break;
    case DWIN_TFT_RX_GET_PRINTING_TIME://A7 GET PRINTING TIME
      sendGetPrintingTime();
      break;
    case DWIN_TFT_RX_GET_SD_CARD_LIST: // A8 GET  SD LIST
      sendGetSDCardList();
      break;
    case DWIN_TFT_RX_SD_CARD_PRINT_PAUSE: // A9 pause sd print
      sendSDCardPause();
      break;
    case DWIN_TFT_RX_SD_CARD_PRINT_RESUME: // A10 resume sd print
      if(DwinTFT.isWaitingForUserConfirm()) {
        ExtUI::setUserConfirmed();
      } else {
        sendSDCardResume();
      }
      break;
    case DWIN_TFT_RX_SD_CARD_PRINT_STOP: // A11 STOP SD PRINT
      sendSDCardStop();
      break;
    case DWIN_TFT_RX_KILL: // A12 kill
      kill(PSTR(MSG_ERR_KILLED));
      break;
    case DWIN_TFT_RX_SD_CARD_FILE_SELECT: // A13 SELECTION FILE
      sendSDCardFileSelect();
      break;
    case DWIN_TFT_RX_SD_CARD_PRINT_START: // A14 START PRINTING
      sendSDCardStart();
      break;
    case DWIN_TFT_RX_OUTAGE_RESUME: // A15 RESUMING FROM OUTAGE
      break;
    case DWIN_TFT_RX_SET_HOTEND_TEMP: // A16 set hotend temp
      sendSetHotendTemp();
      break;
    case DWIN_TFT_RX_SET_HOTBED_TEMP:// A17 set heated bed temp
      sendSetHotbedTemp();
      break;
    case DWIN_TFT_RX_SET_FAN_SPEED:// A18 set fan speed
      sendSetFanSpeed();
      break;
    case DWIN_TFT_RX_STEPPER_DRIVER_STOP: // A19 stop stepper drivers
      sendStopStepperDriver();
      break;
    case DWIN_TFT_RX_GET_PRINT_SPEED:// A20 read printing speed
      sendGetPrintSpeed();
      break;
    case DWIN_TFT_RX_HOME_ALL: // A21 all home
      sendHomeAll();
      break;
    case DWIN_TFT_RX_MOVE: // A22 move X/Y/Z or extrude
      sendMove();
      break;
    case DWIN_TFT_RX_PREHEAT_PLA: // A23 preheat pla
      sendPreheatPLA();
      break;
    case DWIN_TFT_RX_PREHEAT_ABS:// A24 preheat abs
      sendPreheatABS();
      break;
    case DWIN_TFT_RX_COOLDOWN: // A25 cool down
      sendCooldown();
      break;
    case DWIN_TFT_RX_SD_CARD_FILE_REFRESH: // A26 refresh SD
      sendSDCardRefresh();
      break;
    case DWIN_TFT_RX_ADJUST_SERVO: // A27 servos angles  adjust
      break;
    case DWIN_TFT_RX_TEST_FILAMENT: // A28 filament test
      sendFilamentTest();
      break;
    case DWIN_TFT_RX_SET_Z_PROBE_OFFSET: // A29 Z PROBE OFFESET SET
      break;
    case DWIN_TFT_RX_GET_VERSION_INFO: // A33 get version info
      sendGetVersionInfo();
      break;
    case DWIN_TFT_RX_RESET_MAINBOARD: //a40 reset mainboard
      DwinTFT.gcodeNow_P(DWIN_TFT_GCODE_M502);
      break;
    case DWIN_TFT_RX_AUTO_POWER_OFF: // auto power off
      sendAutoPowerOff();
      break;
    case DWIN_TFT_RX_SET_CASE_LED: // 4max pro led strip
      sendSetCaseLight();
      break;
    default:
      break;
  }
}

float DwinTFTCommandClass::codeValue()
{
  return (strtod(&TFTcmdbuffer[TFTbufindr][TFTstrchr_pointer - TFTcmdbuffer[TFTbufindr] + 1], NULL));
}

bool DwinTFTCommandClass::codeSeen(char code)
{
  TFTstrchr_pointer = strchr(TFTcmdbuffer[TFTbufindr], code);
  return (TFTstrchr_pointer != NULL); //Return True if a character was found
}

void DwinTFTCommandClass::receiveCommands()
{
  while( DwinTFTSerial.available() > 0  && TFTbuflen < DWIN_TFT_BUFSIZE)
  {
    serial3_char = DwinTFTSerial.read();
    if(serial3_char == '\n' || serial3_char == '\r' || serial3_char == ':'  || serial3_count >= (DWIN_TFT_MAX_CMD_SIZE - 1) )
    {
      if(!serial3_count) { //if empty line
        return;
      }

      TFTcmdbuffer[TFTbufindw][serial3_count] = 0; //terminate string

      if((strchr(TFTcmdbuffer[TFTbufindw], 'A') != NULL)) {
        int16_t a_command;
        TFTstrchr_pointer = strchr(TFTcmdbuffer[TFTbufindw], 'A');
        a_command = ((int)((strtod(&TFTcmdbuffer[TFTbufindw][TFTstrchr_pointer - TFTcmdbuffer[TFTbufindw] + 1], NULL))));

        #ifdef DWIN_TFT_DEBUG
          if ((a_command>7) && (a_command != 20)) // No debugging of status polls, please!
          SERIAL_ECHOLNPAIR("TFT Serial Command: ", TFTcmdbuffer[TFTbufindw]);
        #endif

        handleCommand((DwinTFTCommandsRx)a_command);
      }
      TFTbufindw = (TFTbufindw + 1) % DWIN_TFT_BUFSIZE;
      TFTbuflen += 1;
      serial3_count = 0; //clear buffer
    }
    else
    {
      TFTcmdbuffer[TFTbufindw][serial3_count++] = serial3_char;
    }
  }
}

void DwinTFTCommandClass::loop()
{
  if(TFTbuflen<(DWIN_TFT_BUFSIZE-1)) {
    receiveCommands();
  }
  if(TFTbuflen) {
    TFTbuflen = (TFTbuflen - 1);
    TFTbufindr = (TFTbufindr + 1) % DWIN_TFT_BUFSIZE;
  }
}

void DwinTFTCommandClass::sendGetHotendTemp()
{
  DWIN_TFT_SERIAL_PROTOCOLPGM("A0V ");
  DWIN_TFT_SERIAL_PROTOCOL(itostr3(int(ExtUI::getActualTemp_celsius(ExtUI::extruder_t::E0))));
  DWIN_TFT_SERIAL_ENTER();
}

void DwinTFTCommandClass::sendGetHotendTargetTemp()
{
  DWIN_TFT_SERIAL_PROTOCOLPGM("A1V ");
  DWIN_TFT_SERIAL_PROTOCOL(itostr3(int(ExtUI::getTargetTemp_celsius(ExtUI::extruder_t::E0))));
  DWIN_TFT_SERIAL_ENTER();
}

void DwinTFTCommandClass::sendGetHotbedTemp()
{
  DWIN_TFT_SERIAL_PROTOCOLPGM("A2V ");
  DWIN_TFT_SERIAL_PROTOCOL(itostr3(int(ExtUI::getActualTemp_celsius(ExtUI::heater_t::BED))));
  DWIN_TFT_SERIAL_ENTER();
}

void DwinTFTCommandClass::sendGetHotbedTargetTemp()
{
  DWIN_TFT_SERIAL_PROTOCOLPGM("A3V ");
  DWIN_TFT_SERIAL_PROTOCOL(itostr3(int(ExtUI::getTargetTemp_celsius(ExtUI::heater_t::BED))));
  DWIN_TFT_SERIAL_ENTER();
}

void DwinTFTCommandClass::sendGetFanSpeed()
{
  DWIN_TFT_SERIAL_PROTOCOLPGM("A4V ");
  DWIN_TFT_SERIAL_PROTOCOL(int(ExtUI::getActualFan_percent(ExtUI::fan_t::FAN0)));
  DWIN_TFT_SERIAL_ENTER();
}

void DwinTFTCommandClass::sendGetCurrentCoordinates()
{
  DWIN_TFT_SERIAL_PROTOCOLPGM("A5V");
  DWIN_TFT_SERIAL_SPACE();
  DWIN_TFT_SERIAL_PROTOCOLPGM("X: ");
  DWIN_TFT_SERIAL_PROTOCOL(ExtUI::getAxisPosition_mm(ExtUI::axis_t::X));
  DWIN_TFT_SERIAL_SPACE();
  DWIN_TFT_SERIAL_PROTOCOLPGM("Y: ");
  DWIN_TFT_SERIAL_PROTOCOL(ExtUI::getAxisPosition_mm(ExtUI::axis_t::Y));
  DWIN_TFT_SERIAL_SPACE();
  DWIN_TFT_SERIAL_PROTOCOLPGM("Z: ");
  DWIN_TFT_SERIAL_PROTOCOL(ExtUI::getAxisPosition_mm(ExtUI::axis_t::Z));
  DWIN_TFT_SERIAL_SPACE();
  DWIN_TFT_SERIAL_ENTER();
}

void DwinTFTCommandClass::sendGetSDCardPrintingStatus()
{
  #ifdef SDSUPPORT
    if(ExtUI::isPrinting()) {
      DWIN_TFT_SERIAL_PROTOCOLPGM("A6V ");
      if(ExtUI::isPrintingFromMedia()) {
        DWIN_TFT_SERIAL_PROTOCOL(itostr3(card.percentDone()));
      } else {
        DWIN_TFT_SERIAL_PROTOCOLPGM(DWIN_TFT_TX_SD_CARD_NOT_INSERTED);
      }
    } else {
      DWIN_TFT_SERIAL_PROTOCOLPGM("A6V ---");
    }
    DWIN_TFT_SERIAL_ENTER();
  #endif
}

void DwinTFTCommandClass::sendGetPrintingTime()
{
  DWIN_TFT_SERIAL_PROTOCOLPGM("A7V ");
  duration_t elapsed = print_job_timer.duration();
  if(elapsed.second() != 0) { // print time
    DWIN_TFT_SERIAL_PROTOCOL(itostr2(elapsed.hour())); //hours
    DWIN_TFT_SERIAL_SPACE();
    DWIN_TFT_SERIAL_PROTOCOLPGM("H");
    DWIN_TFT_SERIAL_SPACE();
    DWIN_TFT_SERIAL_PROTOCOL(itostr2(elapsed.minute())); //minutes
    DWIN_TFT_SERIAL_SPACE();
    DWIN_TFT_SERIAL_PROTOCOLPGM("M");
  } else {
    DWIN_TFT_SERIAL_SPACE();
    DWIN_TFT_SERIAL_PROTOCOLPGM("999:999");
  }
  DWIN_TFT_SERIAL_ENTER();
}

void DwinTFTCommandClass::sendGetSDCardList()
{
  #ifdef SDSUPPORT
    DwinTFTFileBrowser.listFiles();
  #endif
}

void DwinTFTCommandClass::sendSDCardPause()
{
  #ifdef SDSUPPORT
    DWIN_TFT_SERIAL_PROTOCOLPGM(DWIN_TFT_TX_PRINT_PAUSE_REQ);
    DWIN_TFT_SERIAL_ENTER();
    if(ExtUI::isPrintingFromMedia()) {
      ExtUI::pausePrint();
      #ifdef DWIN_TFT_DEBUG
        SERIAL_ECHOLNPGM("DEBUG: SD Card Print paused");
      #endif
    }
  #endif
}

void DwinTFTCommandClass::sendSDCardResume()
{
  #ifdef SDSUPPORT
    if(ExtUI::isPrintingFromMediaPaused()) {
      ExtUI::resumePrint();
      DWIN_TFT_SERIAL_PROTOCOLPGM(DWIN_TFT_TX_PRINT_RESUME);// J04 printing form sd card now
      DWIN_TFT_SERIAL_ENTER();
      #ifdef DWIN_TFT_DEBUG
        SERIAL_ECHOLNPGM("TFT Serial Debug: SD print started... J04");
      #endif
    }
  #endif
}

void DwinTFTCommandClass::sendSDCardStop()
{
  #ifdef SDSUPPORT
    if(ExtUI::isPrintingFromMedia() || ExtUI::isPrintingFromMediaPaused()) {
      ExtUI::stopPrint();
      DWIN_TFT_SERIAL_PROTOCOLPGM(DWIN_TFT_TX_PRINT_STOPPED);
      DWIN_TFT_SERIAL_ENTER();
      #ifdef DWIN_TFT_DEBUG
        SERIAL_ECHOLNPGM("TFT Serial Debug: SD print stopped... J16");
      #endif
    }
  #endif
}

void DwinTFTCommandClass::sendSDCardFileSelect()
{
  #ifdef SDSUPPORT
    DwinTFTFileBrowser.selectFile();
  #endif
}

void DwinTFTCommandClass::sendSDCardStart()
{
  #ifdef SDSUPPORT
    if(ExtUI::isMediaInserted() && !ExtUI::isMoving()) {
      if(card.isFileOpen()) {
        card.startFileprint();
        DWIN_TFT_SERIAL_PROTOCOLPGM(DWIN_TFT_TX_PRINT_RESUME); // J04 Starting Print
        DWIN_TFT_SERIAL_ENTER();
        #ifdef DWIN_TFT_DEBUG
          SERIAL_ECHOLNPGM("TFT Serial Debug: Starting SD Print... J04");
        #endif
      }
    }
  #endif
}

void DwinTFTCommandClass::sendSetHotendTemp()
{
  if(!ExtUI::isPrinting() && !ExtUI::isMoving()) {
    uint16_t temp;
    if(codeSeen('S')) {
      temp = constrain(codeValue(), 0, 275);
      ExtUI::setTargetTemp_celsius(float(temp), ExtUI::extruder_t::E0);
    } else if(codeSeen('C') && !ExtUI::isPrinting() && !ExtUI::isMoving()) {
      if(ExtUI::getAxisPosition_mm(ExtUI::axis_t::Z) < 10) {
        DwinTFT.gcodeNow_P(DWIN_TFT_GCODE_RAIZE_Z_10); //RASE Z AXIS
      }
      temp = constrain(codeValue(), 0, HEATER_0_MAXTEMP);
      ExtUI::setTargetTemp_celsius(float(temp), ExtUI::extruder_t::E0);
    }
  }
}

void DwinTFTCommandClass::sendSetHotbedTemp()
{
  if(!ExtUI::isPrinting() && !ExtUI::isMoving()) {
    if(codeSeen('S')) {
      uint16_t temp = constrain(codeValue(), 0, BED_MAXTEMP);
      ExtUI::setTargetTemp_celsius(float(temp), ExtUI::heater_t::BED);
    }
  }
}

void DwinTFTCommandClass::sendSetFanSpeed()
{
  if(!ExtUI::isPrinting() && !ExtUI::isMoving()) {
    if (codeSeen('S')) {
      ExtUI::setTargetFan_percent(float(codeValue()), ExtUI::fan_t::FAN0);
    } else {
      ExtUI::setTargetFan_percent(float(100), ExtUI::fan_t::FAN0);
    }
    DWIN_TFT_SERIAL_ENTER();
  }
}

void DwinTFTCommandClass::sendStopStepperDriver()
{
  if(!ExtUI::isPrinting() && !ExtUI::isMoving()) {
    quickstop_stepper();
    disable_all_steppers();
    DWIN_TFT_SERIAL_ENTER();
  }
}

void DwinTFTCommandClass::sendGetPrintSpeed()
{
  if(codeSeen('S')) {
    ExtUI::setFeedrate_percent(float(constrain(codeValue(), 40, 999)));
  } else {
    DWIN_TFT_SERIAL_PROTOCOLPGM("A20V ");
    DWIN_TFT_SERIAL_PROTOCOL(int(ExtUI::getFeedrate_percent()));
    DWIN_TFT_SERIAL_ENTER();
  }
}

void DwinTFTCommandClass::sendHomeAll()
{
  if(!ExtUI::isPrinting() && !ExtUI::isMoving()) {
    if(codeSeen('X') || codeSeen('Y') || codeSeen('Z')) {
      if(codeSeen('X')) DwinTFT.gcodeQueue_P(DWIN_TFT_GCODE_HOME_X);
      if(codeSeen('Y')) DwinTFT.gcodeQueue_P(DWIN_TFT_GCODE_HOME_Y);
      if(codeSeen('Z')) DwinTFT.gcodeQueue_P(DWIN_TFT_GCODE_HOME_Z);
    } else if(codeSeen('C')) {
      DwinTFT.gcodeQueue_P(DWIN_TFT_GCODE_HOME_ALL);
    }
  }
}

void DwinTFTCommandClass::sendMove()
{
  if(!ExtUI::isPrinting() && !ExtUI::isMoving()) {
    float coorvalue;
    unsigned int movespeed = 0;
    char value[30];
    if(codeSeen('F')) { // Set feedrate
      movespeed = codeValue();
    }

    DwinTFT.gcodeQueue_P(DWIN_TFT_GCODE_G91); // relative coordinates

    if(codeSeen('X')) { // Move in X direction
      coorvalue=codeValue();
      if((coorvalue<=0.2)&&coorvalue>0) {sprintf_P(value,PSTR("G0 X0.1F%i"),movespeed);}
      else if((coorvalue<=-0.1)&&coorvalue>-1) {sprintf_P(value,PSTR("G0 X-0.1F%i"),movespeed);}
      else {sprintf_P(value,PSTR("G0 X%iF%i"),int(coorvalue),movespeed);}
    } else if(codeSeen('Y')) { // Move in Y direction
      coorvalue=codeValue();
      if((coorvalue<=0.2)&&coorvalue>0) {sprintf_P(value,PSTR("G0 Y0.1F%i"),movespeed);}
      else if((coorvalue<=-0.1)&&coorvalue>-1) {sprintf_P(value,PSTR("G0 Y-0.1F%i"),movespeed);}
      else {sprintf_P(value,PSTR("G0 Y%iF%i"),int(coorvalue),movespeed);}
    } else if(codeSeen('Z')) { // Move in Z direction
      coorvalue=codeValue();
      if((coorvalue<=0.2)&&coorvalue>0) {sprintf_P(value,PSTR("G0 Z0.1F%i"),movespeed);}
      else if((coorvalue<=-0.1)&&coorvalue>-1) {sprintf_P(value,PSTR("G0 Z-0.1F%i"),movespeed);}
      else {sprintf_P(value,PSTR("G0 Z%iF%i"),int(coorvalue),movespeed);}
    } else if(codeSeen('E')) { // Extrude
      coorvalue=codeValue();
      if((coorvalue<=0.2)&&coorvalue>0) {sprintf_P(value,PSTR("G0 E0.1F%i"),movespeed);}
      else if((coorvalue<=-0.1)&&coorvalue>-1) {sprintf_P(value,PSTR("G0 E-0.1F%i"),movespeed);}
      else {sprintf_P(value,PSTR("G0 E%iF500"),int(coorvalue)); }
    }
    if(value != NULL) {
      DwinTFT.gcodeQueue(value);
      #ifdef DWIN_TFT_DEBUG
        SERIAL_ECHOLNPAIR("TFT Serial Debug GCODE: ", value);
      #endif
    }
    DwinTFT.gcodeQueue_P(DWIN_TFT_GCODE_G90); // absolute coordinates
  }
  DWIN_TFT_SERIAL_ENTER();
}

void DwinTFTCommandClass::sendPreheatPLA()
{
  if(!ExtUI::isPrinting() && !ExtUI::isMoving()) {
    if(ExtUI::getAxisPosition_mm(ExtUI::axis_t::Z) < 10) {
      DwinTFT.gcodeNow_P(DWIN_TFT_GCODE_RAIZE_Z_10); // RAISE Z AXIS
    }
    ExtUI::setTargetTemp_celsius(float(PREHEAT_1_TEMP_HOTEND), ExtUI::extruder_t::E0);
    ExtUI::setTargetTemp_celsius(float(PREHEAT_1_TEMP_BED), ExtUI::heater_t::BED);
    #ifdef DWIN_TFT_DEBUG
      SERIAL_ECHOLNPGM("TFT Serial Debug: Preheat PLA");
    #endif
    DWIN_TFT_SERIAL_SUCC_START;
    DWIN_TFT_SERIAL_ENTER();
  }
}

void DwinTFTCommandClass::sendPreheatABS()
{
  if(!ExtUI::isPrinting() && !ExtUI::isMoving()) {
    if(ExtUI::getAxisPosition_mm(ExtUI::axis_t::Z) < 10) {
      DwinTFT.gcodeNow_P(DWIN_TFT_GCODE_RAIZE_Z_10); //RAISE Z AXIS
    }
    ExtUI::setTargetTemp_celsius(float(PREHEAT_2_TEMP_HOTEND), ExtUI::extruder_t::E0);
    ExtUI::setTargetTemp_celsius(float(PREHEAT_2_TEMP_BED), ExtUI::heater_t::BED);
    #ifdef DWIN_TFT_DEBUG
      SERIAL_ECHOLNPGM("TFT Serial Debug: Preheat ABS");
    #endif
    DWIN_TFT_SERIAL_SUCC_START;
    DWIN_TFT_SERIAL_ENTER();
  }
}

void DwinTFTCommandClass::sendCooldown()
{
  if(!ExtUI::isPrinting() && !ExtUI::isMoving()) {
    ExtUI::setTargetTemp_celsius(float(0), ExtUI::extruder_t::E0);
    ExtUI::setTargetTemp_celsius(float(0), ExtUI::heater_t::BED);
    DWIN_TFT_SERIAL_PROTOCOLPGM(DWIN_TFT_TX_READY); // J12 cool down
    DWIN_TFT_SERIAL_ENTER();
    #ifdef DWIN_TFT_DEBUG
      SERIAL_ECHOLNPGM("TFT Serial Debug: Cooling down... J12");
    #endif
  }
}

void DwinTFTCommandClass::sendSDCardRefresh()
{
  #ifdef SDSUPPORT
    DwinTFTFileBrowser.refreshFileList();
  #endif
}

void DwinTFTCommandClass::sendFilamentTest()
{
  if(codeSeen('O')) {

  }
  else if(codeSeen('C')) {
    
  }
  DWIN_TFT_SERIAL_ENTER();
}

void DwinTFTCommandClass::sendGetVersionInfo()
{
  DWIN_TFT_SERIAL_PROTOCOLPGM("J33 ");
  DWIN_TFT_SERIAL_PROTOCOLPGM(CUSTOM_BUILD_VERSION);
  DWIN_TFT_SERIAL_ENTER();
}

void DwinTFTCommandClass::sendAutoPowerOff()
{
  if(codeSeen('O')) {
    DwinTFT.gcodeNow_P(DWIN_TFT_GCODE_INACTIVITY_ON);
  } else if (codeSeen('C')) {
    DwinTFT.gcodeNow_P(DWIN_TFT_GCODE_INACTIVITY_OFF);
  }
}

void DwinTFTCommandClass::sendSetCaseLight()
{
  ExtUI::setCaseLightState(!ExtUI::getCaseLightState());
}

#endif
