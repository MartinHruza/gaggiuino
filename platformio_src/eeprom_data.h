#ifndef EEPROM_DATA_H
#define EEPROM_DATA_H

#include <Arduino.h>

struct eepromValues_t {
    uint16_t setpoint;
    uint16_t offset;
    uint16_t hpwr;
    uint16_t mDivider;
    uint16_t bDivider;
    uint16_t pStart;
    uint16_t pFinish;
    uint16_t pHold;
    uint16_t pLength;
    bool     pProfile;
    bool     preinfusion;
    uint16_t preinfusionSec;
    uint16_t preinfusionBar;
    uint16_t preinfusionSoak;
    uint16_t regpwrHz;
    bool     warmup;
    bool     homeOnShotFinish;
    bool     graphBrew;
    float    scalesF1;
    float    scalesF2;
};

struct eepromMetadata_t {
  uint16_t resetFlag;
  struct eepromValues_t values;
  uint32_t crc;
};

void eepromInit(void);
bool eepromWrite(eepromValues_t);
struct eepromValues_t eepromGetCurrentValues(void);

#endif
