// Time.cpp

#include "Time.h"

#include <Arduino.h>

Time::Time(uint32_t btuMs)
: m_btuMs(btuMs)
// Time durations with BTU multiplier
, m_durationsMs{
    btuMs,
    static_cast<uint32_t>(3 * btuMs),
    btuMs,
    static_cast<uint32_t>(3 * btuMs),
    static_cast<uint32_t>(7 * btuMs)
}
{
}

// return symbol's duration
uint32_t Time::getDurationMs(Symbol symbol) const
{
    switch (symbol)
    {
        case Symbol::Dit:       return m_durationsMs.ditMs;
        case Symbol::Dah:       return m_durationsMs.dahMs;
        case Symbol::SymbolGap: return m_durationsMs.symbolGapMs;
        case Symbol::LetterGap: return m_durationsMs.letterGapMs;
        case Symbol::WordGap:   return m_durationsMs.wordGapMs;
    }
    return 0;
}

uint32_t Time::getTimestampMs() const
{
    return static_cast<uint32_t>(millis());
}

void Time::newSymbol(Symbol symbol)
{
    // Set start time and intended duration of symbol
    m_symbolStartMs = getTimestampMs();
    m_symbolDurationMs = getDurationMs(symbol);
}

bool Time::isSymbolComplete() const
{
    // check if symbol's duration has elapsed
    return (getTimestampMs() - m_symbolStartMs) >= m_symbolDurationMs;
}
