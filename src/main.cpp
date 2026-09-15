#include <Arduino.h>

#include "LineReader.h"
#include "PatternGenerator.h"
#include "Time.h"

namespace
{
    constexpr uint8_t LED_PIN = 13;

    LineReader lineReader;
    PatternGenerator patternGenerator;
    Time time;
    bool halted = false;

    bool executingPattern = false;
    uint16_t currentSymbolIndex = 0;

    bool isMarkSymbol(Symbol symbol)
    {
        return (symbol == Symbol::Dit) || (symbol == Symbol::Dah);
    }

    void beginSymbol(uint16_t index)
    {
        Symbol symbol = patternGenerator.getBuffer()[index];
        time.newSymbol(symbol);
        digitalWrite(LED_PIN, isMarkSymbol(symbol) ? HIGH : LOW);
    }

    void beginExecutingPattern()
    {
        if (patternGenerator.getSizeBuffer() == 0)
        {
            return; // nothing to play (e.g. an unrecognized/empty line)
        }

        currentSymbolIndex = 0;
        beginSymbol(currentSymbolIndex);
        executingPattern = true;
    }

    void advanceExecutingPattern()
    {
        if (!time.isSymbolComplete())
        {
            return; // still on the current symbol; nothing to do this cycle
        }

        ++currentSymbolIndex;

        if (currentSymbolIndex < patternGenerator.getSizeBuffer())
        {
            beginSymbol(currentSymbolIndex);
        }
        else
        {
            executingPattern = false;
        }
    }
}

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW); // start from a known state rather than whatever the pin reset to

    Serial.begin(9600);
    Serial.println("Type text and press Enter for its Morse pattern. Ctrl-Z to quit.");
}

void loop()
{
    if (halted)
    {
        return;
    }

    // Keep draining Serial every cycle regardless of playback state, so
    // input isn't lost while a message is playing out.
    LineStatus status = lineReader.poll();

    if (status == LineStatus::Sentinel)
    {
        Serial.println("Exiting.");
        halted = true;
        return;
    }

    if (executingPattern)
    {
        advanceExecutingPattern();
        return;
    }

    if (status == LineStatus::LineReady)
    {
        patternGenerator.generatePattern(lineReader.getLine());
        beginExecutingPattern();
    }
}
