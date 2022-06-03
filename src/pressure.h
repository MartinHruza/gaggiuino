#ifndef PRESSURE_H
#define PRESSURE_H
#include <Arduino.h>
#include <PSM.h>
#include "mcu_pinout.h"
#include "utils.h"

struct Phase
{
    float startPressure;
    float endPressure;
    unsigned int durationMs;

    float getPressure(unsigned long timeInPhase)
    {
        return mapRange(timeInPhase, 0, durationMs, startPressure, endPressure, 1);
    }
};

struct CurrentPhase
{
    short phaseIndex;
    unsigned long timeInPhase;
};

struct Phases
{
    short count;
    Phase *phases;

    CurrentPhase getCurrentPhase(long timeInPP)
    {
        short phase = 0;
        unsigned long accumulatedTime = 0;

        while (phase < count - 1 && timeInPP >= accumulatedTime + (phases[phase].durationMs))
        {
            accumulatedTime += phases[phase].durationMs;
            phase += 1;
        }
        return CurrentPhase{phase, timeInPP - accumulatedTime};
    }
};

void pressureInit(int hz);
float getPressure();
void setPressure(float targetValue);
void setPump(int pct);

#endif
