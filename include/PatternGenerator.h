/*
Fill buffer with sequence of morse code signals generated from char array input
*/
#pragma once

#include <cstdint>

#include "MorseSymbol.h"
#include "MorseAlphabet.h"

class PatternGenerator
{
    private:

        // Max allowable buffer size
        static constexpr uint16_t MAX_PATTERN_SYMBOLS = 512;

        // buffer that contains final Morse code sequence
        Symbol m_buffer[MAX_PATTERN_SYMBOLS];
        uint16_t m_sizeBuffer = 0;

        void generateLetter(const char* pattern, Symbol prev); // letter patterns
        void generateSpace(); // interword spacing
        void writeSymbol(Symbol sym); // write pattern to buffer

    public:
        PatternGenerator() = default;
        PatternGenerator(const PatternGenerator&) = delete;
        PatternGenerator& operator=(const PatternGenerator&) = delete;

        // Generate pattern from character text
        void generatePattern(const char* text);

        // return buffer
        const Symbol* getBuffer() const;
        uint16_t getSizeBuffer() const;
};
