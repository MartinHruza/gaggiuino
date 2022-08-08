#ifndef OTA_PACKAGE_H
#define OTA_PACKAGE_H

#include <Arduino.h>

#define str(x) #x
#define OTA_PACKAGE_HEADER str(GAGGIUINO_FW)

struct ota_package_tlv_header {
  uint8_t   tag;
  uint32_t  length;
}

typedef enum {
  ota_package_tlv_tag_backend = 1,
  ota_package_tlv_tag_frontend = 10
} ota_package_tlv_tags;

#endif
