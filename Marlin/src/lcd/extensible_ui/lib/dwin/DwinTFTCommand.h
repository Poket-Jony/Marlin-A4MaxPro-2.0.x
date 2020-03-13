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
#include "DwinTFT.h"

#define DWIN_TFT_BAUDRATE 115200
#define DWIN_TFT_BUFSIZE 4
#define DWIN_TFT_MAX_CMD_SIZE 96

enum DwinTFTCommandsRx : uint8_t {
  DWIN_TFT_RX_GET_HOTEND_TEMP = 0,
  DWIN_TFT_RX_GET_HOTEND_TARGET_TEMP = 1,
  DWIN_TFT_RX_GET_HOTBED_TEMP = 2,
  DWIN_TFT_RX_GET_HOTBED_TARGET_TEMP = 3,
  DWIN_TFT_RX_GET_FAN_SPEED = 4,
  DWIN_TFT_RX_GET_CURRENT_COORDINATES = 5,
  DWIN_TFT_RX_GET_SD_CARD_PRINT_STATUS = 6,
  DWIN_TFT_RX_GET_PRINTING_TIME = 7,
  DWIN_TFT_RX_GET_SD_CARD_LIST = 8,
  DWIN_TFT_RX_SD_CARD_PRINT_PAUSE = 9,
  DWIN_TFT_RX_SD_CARD_PRINT_RESUME = 10,
  DWIN_TFT_RX_SD_CARD_PRINT_STOP = 11,
  DWIN_TFT_RX_KILL = 12,
  DWIN_TFT_RX_SD_CARD_FILE_SELECT = 13,
  DWIN_TFT_RX_SD_CARD_PRINT_START = 14,
  DWIN_TFT_RX_OUTAGE_RESUME = 15,
  DWIN_TFT_RX_SET_HOTEND_TEMP = 16,
  DWIN_TFT_RX_SET_HOTBED_TEMP = 17,
  DWIN_TFT_RX_SET_FAN_SPEED = 18,
  DWIN_TFT_RX_STEPPER_DRIVER_STOP = 19,
  DWIN_TFT_RX_GET_PRINT_SPEED = 20,
  DWIN_TFT_RX_HOME_ALL = 21,
  DWIN_TFT_RX_MOVE = 22,
  DWIN_TFT_RX_PREHEAT_PLA = 23,
  DWIN_TFT_RX_PREHEAT_ABS = 24,
  DWIN_TFT_RX_COOLDOWN = 25,
  DWIN_TFT_RX_SD_CARD_FILE_REFRESH = 26,
  DWIN_TFT_RX_ADJUST_SERVO = 27,
  DWIN_TFT_RX_TEST_FILAMENT = 28,
  DWIN_TFT_RX_SET_Z_PROBE_OFFSET = 29,
  DWIN_TFT_RX_LEVELING_ASSIST = 30,
  DWIN_TFT_RX_SET_Z_OFFSET = 31,
  DWIN_TFT_RX_LEVELING_CLEAN_BEEP_FLAG = 32,
  DWIN_TFT_RX_GET_VERSION_INFO = 33,
  DWIN_TFT_RX_RESET_MAINBOARD = 40,
  DWIN_TFT_RX_AUTO_POWER_OFF = 41,
  DWIN_TFT_RX_SET_CASE_LED = 42
};

#define DWIN_TFT_TX_SD_CARD_INSERTED "J00" //Status: SD Card inserted
#define DWIN_TFT_TX_SD_CARD_REMOVED "J01" //Alert: No SD Card
#define DWIN_TFT_TX_SD_CARD_NOT_INSERTED "J02" //Alert: No SD Card
#define DWIN_TFT_TX_PRINT_VIA_HOST "J03" //Status: USB Host online
#define DWIN_TFT_TX_PRINT_RESUME "J04" //Status: Print from SD Card
#define DWIN_TFT_TX_PRINT_PAUSE "J05" //Alert: Command has been sent, wait for response
#define DWIN_TFT_TX_HOTEND_HEATING_START "J06" //Status: Nozzle heating
#define DWIN_TFT_TX_HOTEND_HEATING_END "J07" //Status: Nozzle heating done
#define DWIN_TFT_TX_HOTBED_HEATING_START "J08" //Status: Bed heating
#define DWIN_TFT_TX_HOTBED_HEATING_END "J09" //Status: Bed heating done
#define DWIN_TFT_TX_HOTEND_ABNORMAL "J10" //Alert: T1 Sensor abnormal
#define DWIN_TFT_TX_KILL "J11"
#define DWIN_TFT_TX_READY "J12" //Status: Ready
#define DWIN_TFT_TX_HOTEND_TEMP_LOW "J13" //Status: Low E0 Temp
#define DWIN_TFT_TX_PRINT_FINISHED "J14" //Alert: Print done
//#define DWIN_TFT_TX_FILAMENT_RUNOUT "J15" //Alert: Lack of filament //replaced by J23
#define DWIN_TFT_TX_PRINT_STOPPED "J16" //Switch Screen to Status: Stopped
#define DWIN_TFT_TX_MAINBOARD_RESET "J17" //Status: Stop
#define DWIN_TFT_TX_PRINT_PAUSE_REQ "J18" //Status: Pause
#define DWIN_TFT_TX_SD_CARD_OPEN_SUCCESS "J20" //Switch Screen to File Browser: Print avalible
#define DWIN_TFT_TX_SD_CARD_OPEN_FAILED "J21" //Switch Screen to File Browser: Print not avalible
#define DWIN_TFT_TX_FILAMENT_RUNOUT "J23" //Alert: Lack of filament
#define DWIN_TFT_TX_VERSION_INFO "J33 "
#define DWIN_TFT_TX_AUTO_SHUTDOWN_STATUS_OFF "J34 "
#define DWIN_TFT_TX_AUTO_SHUTDOWN_STATUS_ON "J35 "
#define DWIN_TFT_TX_SD_CARD_FILE_LIST_START "FN "
#define DWIN_TFT_TX_SD_CARD_FILE_LIST_END "END"
#define DWIN_TFT_TX_PRINT_SPEED "A20V "
#define DWIN_TFT_TX_PRINTING_TIME "A7V "
#define DWIN_TFT_TX_PRINTING_STATUS "A6V "
#define DWIN_TFT_TX_CURRENT_COORDINATES "A5V"
#define DWIN_TFT_TX_FAN_SPEED "A4V "
#define DWIN_TFT_TX_HOTBED_TARGET_TEMP "A3V "
#define DWIN_TFT_TX_HOTBED_TEMP "A2V "
#define DWIN_TFT_TX_HOTEND_TARGET_TEMP "A1V "
#define DWIN_TFT_TX_HOTEND_TEMP "A0V "

#define DWIN_TFT_RX_CODE_ENABLE 'O'
#define DWIN_TFT_RX_CODE_DISABLE 'C'
#define DWIN_TFT_RX_CODE_STATUS 'S'

class DwinTFTCommandClass {
public:
  char *TFTstrchr_pointer;
  DwinTFTCommandClass();
  void handleCommand(DwinTFTCommandsRx command);
  float codeValue();
  bool codeSeen(char code);
  void loop();

private:
  char TFTcmdbuffer[DWIN_TFT_BUFSIZE][DWIN_TFT_MAX_CMD_SIZE];
  int TFTbuflen = 0;
  int TFTbufindr = 0;
  int TFTbufindw = 0;
  char serial3_char;
  int serial3_count = 0;
  void receiveCommands();
  void handleGetHotendTemp();
  void handleGetHotendTargetTemp();
  void handleGetHotbedTemp();
  void handleGetHotbedTargetTemp();
  void handleGetFanSpeed();
  void handleGetCurrentCoordinates();
  void handleGetSDCardPrintingStatus();
  void handleGetPrintingTime();
  void handleGetSDCardList();
  void handleSDCardPause();
  void handleSDCardResume();
  void handleSDCardStop();
  void handleSDCardFileSelect();
  void handleSDCardStart();
  void handleSetHotendTemp();
  void handleSetHotbedTemp();
  void handleSetFanSpeed();
  void handleStopStepperDriver();
  void handleGetPrintSpeed();
  void handleHomeAll();
  void handleMove();
  void handlePreheatPLA();
  void handlePreheatABS();
  void handleCooldown();
  void handleSDCardRefresh();
  void handleFilamentTest();
  void handleGetVersionInfo();
  void handleResetMainboard();
  void handleAutoPowerOff();
  void handleSetCaseLight();
};

extern DwinTFTCommandClass DwinTFTCommand;
