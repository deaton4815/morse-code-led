#include <Arduino.h>

#include "LineReader.h"
#include "PatternGenerator.h"
#include "Time.h"

// Anonymous namespace
namespace
{
    constexpr uint8_t LED_PIN = 13;

    // One instance of each class for whole system
    LineReader lineReader;
    PatternGenerator patternGenerator;
    Time time;

    bool halted = false; // true when sentinel

    // Playback state, persisted between loop() calls.
    bool executingPattern = false; // If a pattern is curruently being displayed
    uint16_t currentSymbolIndex = 0; // which symbol in buffer is active

    // dit and dah symbols light up LED
    bool isMarkSymbol(Symbol symbol)
    {
        return (symbol == Symbol::Dit) || (symbol == Symbol::Dah);
    }

    // Starts timing the symbol at the given buffer index
    //  and drives the LED to match it
    // Light and the timer always change state together
    void beginSymbol(uint16_t index)
    {
        Symbol symbol = patternGenerator.getBuffer()[index];
        time.newSymbol(symbol);
        digitalWrite(LED_PIN, isMarkSymbol(symbol) ? HIGH : LOW);
    }

    // set up new pattern
    void beginExecutingPattern()
    {
        if (patternGenerator.getSizeBuffer() == 0)
        {
            return;
        }

        currentSymbolIndex = 0;
        beginSymbol(currentSymbolIndex);
        executingPattern = true;
    }

    // Called every loop() iteration while a pattern is playing
    // Advances at most one symbol per call. Does not wait for a symbol to finish
    void advanceExecutingPattern()
    {
        if (!time.isSymbolComplete())
        {
            return; // still on the current symbol, do nothing
        }

        // Advance to next symbol

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
    digitalWrite(LED_PIN, LOW); // start with pin off

    Serial.begin(9600);
    Serial.println("Type text and press Enter for its Morse pattern. Ctrl-Z to quit.");
}

void loop()
{
    if (halted)
    {
        return;
    }

    // Drain Serial every cycle regardless of playback state.
    // Input is not lost if another message is playing out,
    // but LineReady status is only acted on if executingPattern is false.
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
