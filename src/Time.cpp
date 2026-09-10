// Time.cpp

#include "Time.h"

#include <Arduino.h>

Time::Time(uint16_t btuMs) 
: m_btuMs(btuMs)
{

}

uint32_t Time::getTimestampMs() const
{
    return static_cast<uint32_t>(millis());
}