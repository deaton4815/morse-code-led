// Morse code timing

#pragma once

#include <cstdint>

class Time 
{
private:
    const uint16_t m_btuMs;
    uint32_t m_startTime;
public:
    Time(uint16_t value = 132);
    uint32_t getTimestampMs() const;
};