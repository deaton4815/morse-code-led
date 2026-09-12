# pragma once
#include "MorseSymbol.h"
#include "MorseAlphabet.h"

class PatternGenerator
{
    private:

        static constexpr uint16_t MAX_PATTERN_SYMBOLS = 512;
        
        Symbol m_buffer;
        MorseAlphabet m_alphabet;

        uint16_t m_sizeBuffer;

        void generatePattern(const char* text);
        void generateLetter(const char* pattern, uint16_t count, Symbol prev);
        void generateSpace(uint16_t count)

    public:
        PatternGenerator() = default;
        
        Symbol* getBuffer();
        uint16_t getSizeBuffer();
}