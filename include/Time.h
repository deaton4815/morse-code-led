// Morse code timing

#pragma once

#include <cstdint>

#include "MorseSymbol.h"

class Time
{
    private:

        const uint32_t m_btuMs;

        struct Durations
        {
            uint32_t ditMs;
            uint32_t dahMs;
            uint32_t symbolGapMs;
            uint32_t letterGapMs;
            uint32_t wordGapMs;
        };
        const Durations m_durationsMs;
        
        uint32_t m_symbolCompletionMs = 0;

        uint32_t getTimestampMs() const;
        uint32_t getDurationMs(Symbol symbol) const;

    public:
        Time(uint32_t btuMs = 132);

        void newSymbol(Symbol symbol);
        bool isSymbolComplete(Symbol symbol);

};