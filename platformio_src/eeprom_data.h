#ifndef __EEPROM_DATA_H_
#define __EEPROM_DATA_H_

#include <Arduino.h>

static volatile struct eeprom_data_struct {
  uint16_t reset_flag;
  struct values_struct {
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
    uint16_t preinfusion_sec;
    uint16_t preinfusion_bar;
    uint16_t preinfusion_soak;
    uint16_t regpwrHz;
    bool     warmup;
    bool     homeOnShotFinish;
    bool     graphBrew;
    float    scalesF1;
    float    scalesF2;
  } values;
  uint32_t crc;
} eepromData;

void eepromInit();
bool eepromWrite();

#endif
