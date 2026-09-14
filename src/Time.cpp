// Time.cpp

#include "Time.h"

#include <Arduino.h>

Time::Time(uint32_t btuMs)
: m_btuMs(btuMs)
, m_durationsMs{
    btuMs,
    static_cast<uint32_t>(3 * btuMs),
    btuMs,
    static_cast<uint32_t>(3 * btuMs),
    static_cast<uint32_t>(7 * btuMs)
}
{
}

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
    m_symbolStartMs = getTimestampMs();
    m_symbolDurationMs = getDurationMs(symbol);
}

bool Time::isSymbolComplete() const
{
    return (getTimestampMs() - m_symbolStartMs) >= m_symbolDurationMs;
}
