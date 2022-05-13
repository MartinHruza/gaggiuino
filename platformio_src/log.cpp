#include <Arduino.h>
#include "log.h"

void log_e(const char * file, const int line, const char *msg)
{
    Serial.print("ERROR (");
    Serial.print(file);
    Serial.print(":");
    Serial.print(line);
    Serial.print("): ");
    Serial.println(msg);
}
