#include <CRC32.h>
#include <EEPROM.h>
#include "eeprom_data.h"
#include "log.h"

#define EEPROM_RESET 1
CRC32 crc;

bool eepromWrite() {
  char errMsg[] = "Data out of range";

  if (eepromData.values.pStart < 1) {
    LOG_E(errMsg);
    return false;
  }

  if (eepromData.values.pFinish < 1) {
    LOG_E(errMsg);
    return false;
  }

  if (eepromData.values.pHold < 0) {
    LOG_E(errMsg);
    return false;
  }

  if (eepromData.values.pLength < 0) {
    LOG_E(errMsg);
    return false;
  }

  if (eepromData.values.preinfusion != 0 && eepromData.values.preinfusion != 1) {
    LOG_E(errMsg);
    return false;
  }

  if (eepromData.values.pProfile != 0 && eepromData.values.pProfile != 1) {
    LOG_E(errMsg);
    return false;
  }

  if (eepromData.values.preinfusion_sec < 0) {
    LOG_E(errMsg);
    return false;
  }

  if (eepromData.values.preinfusion_soak < 0) {
    LOG_E(errMsg);
    return false;
  }

  if (eepromData.values.pLength < 0) {
    LOG_E(errMsg);
    return false;
  }

  if (eepromData.values.homeOnShotFinish != 0 && eepromData.values.homeOnShotFinish != 1) {
    LOG_E(errMsg);
    return false;
  }

  if (eepromData.values.graphBrew != 0 && eepromData.values.graphBrew != 1) {
    LOG_E(errMsg);
    return false;
  }

  if (eepromData.values.setpoint <= 0) {
    LOG_E(errMsg);
    return false;
  }

  if (eepromData.values.offset < 0) {
    LOG_E(errMsg);
    return false;
  }

  if (eepromData.values.hpwr < 0) {
    LOG_E(errMsg);
    return false;
  }

  if (eepromData.values.mDivider < 1) {
    LOG_E(errMsg);
    return false;
  }

  if (eepromData.values.bDivider < 1) {
    LOG_E(errMsg);
    return false;
  }

  if (eepromData.values.regpwrHz != 50 && eepromData.values.regpwrHz != 60) {
    LOG_E(errMsg);
    return false;
  }

  if (eepromData.values.warmup != 0 && eepromData.values.warmup != 1) {
    LOG_E(errMsg);
    return false;
  }

  eepromData.crc = CRC32::calculate(&eepromData.values, sizeof(eepromData.values));
  EEPROM.put(0, eepromData);
  return true;
}

void setEepromDefaults() {
  eepromData.reset_flag = EEPROM_RESET;

  eepromData.values.setpoint          = 100;
  eepromData.values.offset            = 7;
  eepromData.values.hpwr              = 550;
  eepromData.values.mDivider          = 5;
  eepromData.values.bDivider          = 2;
  eepromData.values.pStart            = 9;
  eepromData.values.pFinish           = 6;
  eepromData.values.pHold             = 7;
  eepromData.values.pLength           = 30;
  eepromData.values.pProfile          = 0;
  eepromData.values.preinfusion       = false;
  eepromData.values.preinfusion_sec   = 8;
  eepromData.values.preinfusion_bar   = 2;
  eepromData.values.preinfusion_soak  = 5;
  eepromData.values.regpwrHz          = 60;
  eepromData.values.warmup            = false;
  eepromData.values.homeOnShotFinish  = true;
  eepromData.values.graphBrew         = false;
  eepromData.values.scalesF1          = 1955.571428f;
  eepromData.values.scalesF2          = -2091.571428f;
}

void eepromInit() {
  EEPROM.get(0, eepromData);
  uint32_t checksum = CRC32::calculate(&eepromData.values, sizeof(eepromData.values));

	if (eepromData.reset_flag != EEPROM_RESET || eepromData.crc != checksum) {
    LOG_E("SECU_CHECK FAILED! Applying defaults!");
    setEepromDefaults();
    eepromWrite();
  }
}
