#ifndef EEPROM_DATA_H
#define EEPROM_DATA_H

#include <Arduino.h>

#if defined(ARDUINO_ARCH_STM32)
  #include "FlashStorage_STM32.hpp"
#else
  #include <EEPROM.h>
#endif

#include "log.h"

#define EEPROM_DATA_VERSION 1

struct eepromValues_t {
  uint16_t setpoint;
  uint16_t offsetTemp;
  uint16_t hpwr;
  uint16_t mainDivider;
  uint16_t brewDivider;
  uint16_t preinfusionStart;
  uint16_t preinfusionFinish;
  uint16_t preinfusionHold;
  uint16_t preinfusionLength;
  bool     preinfusionProfile;
  bool     preinfusionState;
  uint16_t preinfusionSec;
  uint16_t preinfusionBar;
  uint16_t preinfusionSoak;
  uint16_t powerLineFrequency;
  bool     warmupState;
  bool     homeOnShotFinish;
  bool     graphBrew;
  bool     brewDeltaState;
  float    scalesF1;
  float    scalesF2;
};

struct eepromMetadata_t {
  uint16_t version;
  unsigned long timestamp;
  struct eepromValues_t values;
  uint32_t versionTimestampXOR;
};

void eepromInit(void);
bool eepromWrite(eepromValues_t);
struct eepromValues_t eepromGetCurrentValues(void);

#endif
