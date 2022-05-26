#include "eeprom_data.h"

static struct eepromMetadata_t eepromMetadata;

bool eepromWrite(eepromValues_t eepromValuesNew) {
  /*
    No need to do these check since it checks UNSIGNED integers

    if (eepromValuesNew.preinfusionHold < 0)
    if (eepromValuesNew.preinfusionLength < 0)
    if (eepromValuesNew.preinfusionSec < 0)
    if (eepromValuesNew.preinfusionSoak < 0)
    if (eepromValuesNew.preinfusionLength < 0)
    if (eepromValuesNew.offset < 0)
    if (eepromValuesNew.hpwr < 0) {
  */

  String errMsg = String("Data out of range");

  if (eepromValuesNew.preinfusionState != 0 && eepromValuesNew.preinfusionState != 1) {
    LOG_ERROR(errMsg.c_str());
    return false;
  }

  if (eepromValuesNew.preinfusionProfile != 0 && eepromValuesNew.preinfusionProfile != 1) {
    LOG_ERROR(errMsg.c_str());
    return false;
  }

  if (eepromValuesNew.homeOnShotFinish != 0 && eepromValuesNew.homeOnShotFinish != 1) {
    LOG_ERROR(errMsg.c_str());
    return false;
  }

  if (eepromValuesNew.graphBrew != 0 && eepromValuesNew.graphBrew != 1) {
    LOG_ERROR(errMsg.c_str());
    return false;
  }

  if (eepromValuesNew.warmupState != 0 && eepromValuesNew.warmupState != 1) {
    LOG_ERROR(errMsg.c_str());
    return false;
  }

  if (eepromValuesNew.brewDeltaState != 0 && eepromValuesNew.brewDeltaState != 1) {
    LOG_ERROR(errMsg.c_str());
    return false;
  }

  if (eepromValuesNew.preinfusionStart < 1) {
    LOG_ERROR(errMsg.c_str());
    return false;
  }

  if (eepromValuesNew.preinfusionFinish < 1) {
    LOG_ERROR(errMsg.c_str());
    return false;
  }

  if (eepromValuesNew.setpoint < 1) {
    LOG_ERROR(errMsg.c_str());
    return false;
  }

  if (eepromValuesNew.mainDivider < 1) {
    LOG_ERROR(errMsg.c_str());
    return false;
  }

  if (eepromValuesNew.brewDivider < 1) {
    LOG_ERROR(errMsg.c_str());
    return false;
  }

  if (eepromValuesNew.powerLineFrequency != 50 && eepromValuesNew.powerLineFrequency != 60) {
    LOG_ERROR(errMsg.c_str());
    return false;
  }

  eepromMetadata.timestamp = millis();
  eepromMetadata.version = EEPROM_DATA_VERSION;
  eepromMetadata.values = eepromValuesNew;
  eepromMetadata.versionTimestampXOR = eepromMetadata.timestamp ^ eepromMetadata.version;
  EEPROM.put(0, eepromMetadata);

  return true;
}

eepromValues_t getEepromDefaults(void) {
  eepromValues_t defaultData;

  defaultData.setpoint            = 100;
  defaultData.offsetTemp          = 7;
  defaultData.hpwr                = 550;
  defaultData.mainDivider         = 5;
  defaultData.brewDivider         = 2;
  defaultData.preinfusionStart    = 9;
  defaultData.preinfusionFinish   = 6;
  defaultData.preinfusionHold     = 5;
  defaultData.preinfusionLength   = 15;
  defaultData.preinfusionProfile  = 1;
  defaultData.preinfusionState    = true;
  defaultData.preinfusionSec      = 10;
  defaultData.preinfusionBar      = 2;
  defaultData.preinfusionSoak     = 10;
  defaultData.powerLineFrequency  = 50;
  defaultData.warmupState         = false;
  defaultData.homeOnShotFinish    = true;
  defaultData.graphBrew           = true;
  defaultData.brewDeltaState      = true;
  defaultData.scalesF1            = 4000;
  defaultData.scalesF2            = 4000;

  return defaultData;
}

void eepromInit(void) {
  EEPROM.get(0, eepromMetadata);
  uint32_t XOR = eepromMetadata.timestamp ^ eepromMetadata.version;

  if (eepromMetadata.version != EEPROM_DATA_VERSION || eepromMetadata.versionTimestampXOR != XOR) {
    LOG_ERROR("SECU_CHECK FAILED! Applying defaults!");
    eepromWrite(getEepromDefaults());
  }
}

struct eepromValues_t eepromGetCurrentValues(void) {
  return eepromMetadata.values;
}
