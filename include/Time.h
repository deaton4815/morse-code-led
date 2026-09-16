/*
Elapsted-time tracking for single Morse symbol (dit, dah, and three gaps).
Does not track whole message or run its own clod. Time rembmers when the current
symbol started and how long it is meant to last, checking on each iteration 
of the main round-robin loop.
*/

#pragma once

#include <cstdint>

#include "MorseSymbol.h"

class Time
{
    private:

        // Base time unit (BTU) in milliseconds .
        const uint32_t m_btuMs;

        // Durations for each symbol
        struct Durations
        {
            uint32_t ditMs;
            uint32_t dahMs;
            uint32_t symbolGapMs;
            uint32_t letterGapMs;
            uint32_t wordGapMs;
        };
        const Durations m_durationsMs;

        uint32_t m_symbolStartMs = 0;
        uint32_t m_symbolDurationMs = 0;

        uint32_t getTimestampMs() const;
        uint32_t getDurationMs(Symbol symbol) const;

    public:
        // btuMs defaults to 132ms
        Time(uint32_t btuMs = 132);

        // Called  once when a new symbol begins playing
        // Sets starting time for that symbol
        void newSymbol(Symbol symbol);

        // True once the symbol started by the most recent newSymbol() call
        // has been displayed for its full duration.
        // Safe to call any number each loop iteration. Does not block
        bool isSymbolComplete() const;
};
