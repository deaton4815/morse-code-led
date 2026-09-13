#pragma once

#include <cstdint>

#include "MorseSymbol.h"
#include "MorseAlphabet.h"

class PatternGenerator
{
    private:

        static constexpr uint16_t MAX_PATTERN_SYMBOLS = 512;

        Symbol m_buffer[MAX_PATTERN_SYMBOLS];

        uint16_t m_sizeBuffer;

        void generateLetter(const char* pattern, Symbol prev);
        void generateSpace();
        void writeSymbol(Symbol sym);

    public:
        PatternGenerator(const PatternGenerator&) = delete;

        void generatePattern(const char* text);

        const Symbol* getBuffer() const;
        const uint16_t getSizeBuffer() const;
};
