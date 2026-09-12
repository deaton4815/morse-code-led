#pragma once

#include <cstdint>

class MorseCode
{
    private:

        struct LetterPattern
        {
            char letter;
            const char* pattern;
        };
        
        static const LetterPattern m_charTable;
        static const uint8_t m_nChars;

    public:
        MorseCode() = default;
        const char* getPattern(char letter) const;
};
