#include <Arduino.h>

#include "LineReader.h"
#include "PatternGenerator.h"

namespace
{
    LineReader lineReader;
    PatternGenerator patternGenerator;
    bool halted = false;

    const char* symbolName(Symbol symbol)
    {
        switch (symbol)
        {
            case Symbol::Dit:       return "Dit";
            case Symbol::Dah:       return "Dah";
            case Symbol::SymbolGap: return "SymbolGap";
            case Symbol::LetterGap: return "LetterGap";
            case Symbol::WordGap:   return "WordGap";
        }
        return "?";
    }

    void printPattern(const Symbol* buffer, uint16_t size)
    {
        for (uint16_t i = 0; i < size; ++i)
        {
            Serial.print(symbolName(buffer[i]));

            if ((i + 1) < size)
            {
                Serial.print(' ');
            }
        }

        Serial.println();
    }
}

void setup()
{
    Serial.begin(9600);
    Serial.println("Type text and press Enter for its Morse pattern. Ctrl-Z to quit.");
}

void loop()
{
    if (halted)
    {
        return;
    }

    LineStatus status = lineReader.poll();

    if (status == LineStatus::LineReady)
    {
        patternGenerator.generatePattern(lineReader.getLine());
        printPattern(patternGenerator.getBuffer(), patternGenerator.getSizeBuffer());
    }
    else if (status == LineStatus::Sentinel)
    {
        Serial.println("Exiting.");
        halted = true;
    }
}
