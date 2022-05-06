#include <CRC32.h>
#include <EEPROM.h>
#include "eeprom_data.h"
#include "log.h"

#define EEPROM_RESET 1

static struct eepromMetadata_t eepromData;

bool eepromWrite(eepromValues_t eepromValuesNew) {
  /*
    No need to do these check since it checks UNSIGNED integers

    if (eepromValuesNew.pHold < 0)
    if (eepromValuesNew.pLength < 0)
    if (eepromValuesNew.preinfusionSec < 0)
    if (eepromValuesNew.preinfusionSoak < 0)
    if (eepromValuesNew.pLength < 0)
    if (eepromValuesNew.offset < 0)
    if (eepromValuesNew.hpwr < 0) {
  */

  String errMsg = String("Data out of range");

  if (eepromValuesNew.preinfusion != 0 && eepromValuesNew.preinfusion != 1) {
    LOG_E(errMsg.c_str());
    return false;
  }

  if (eepromValuesNew.pProfile != 0 && eepromValuesNew.pProfile != 1) {
    LOG_E(errMsg.c_str());
    return false;
  }

  if (eepromValuesNew.homeOnShotFinish != 0 && eepromValuesNew.homeOnShotFinish != 1) {
    LOG_E(errMsg.c_str());
    return false;
  }

  if (eepromValuesNew.graphBrew != 0 && eepromValuesNew.graphBrew != 1) {
    LOG_E(errMsg.c_str());
    return false;
  }

  if (eepromValuesNew.warmup != 0 && eepromValuesNew.warmup != 1) {
    LOG_E(errMsg.c_str());
    return false;
  }

  if (eepromValuesNew.pStart < 1) {
    LOG_E(errMsg.c_str());
    return false;
  }

  if (eepromValuesNew.pFinish < 1) {
    LOG_E(errMsg.c_str());
    return false;
  }

  if (eepromValuesNew.setpoint < 1) {
    LOG_E(errMsg.c_str());
    return false;
  }

  if (eepromValuesNew.mDivider < 1) {
    LOG_E(errMsg.c_str());
    return false;
  }

  if (eepromValuesNew.bDivider < 1) {
    LOG_E(errMsg.c_str());
    return false;
  }

  if (eepromValuesNew.regpwrHz != 50 && eepromValuesNew.regpwrHz != 60) {
    LOG_E(errMsg.c_str());
    return false;
  }

  CRC32 crc;
  eepromData.values = eepromValuesNew;
  eepromData.crc = CRC32::calculate(&eepromValuesNew, sizeof(eepromValuesNew));
  EEPROM.put(0, eepromData);
  return true;
}

void setEepromDefaults(void) {
  eepromData.resetFlag = EEPROM_RESET;

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
  eepromData.values.preinfusionSec   = 8;
  eepromData.values.preinfusionBar   = 2;
  eepromData.values.preinfusionSoak  = 5;
  eepromData.values.regpwrHz          = 60;
  eepromData.values.warmup            = false;
  eepromData.values.homeOnShotFinish  = true;
  eepromData.values.graphBrew         = false;
  eepromData.values.scalesF1          = 1955.571428f;
  eepromData.values.scalesF2          = -2091.571428f;
}

void eepromInit(void) {
  CRC32 crc;

  EEPROM.get(0, eepromData);
  uint32_t checksum = CRC32::calculate(&eepromData.values, sizeof(eepromData.values));

	if (eepromData.resetFlag != EEPROM_RESET || eepromData.crc != checksum) {
    LOG_E("SECU_CHECK FAILED! Applying defaults!");
    setEepromDefaults();
    eepromWrite(eepromData.values);
  }
}

struct eepromValues_t eepromGetCurrentValues(void) {
  return eepromData.values;
}
