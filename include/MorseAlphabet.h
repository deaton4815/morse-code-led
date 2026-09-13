#pragma once

#include <cstdint>

class MorseAlphabet
{
    private:

        struct LetterPattern
        {
            char letter;
            const char* pattern;
        };

        static const LetterPattern m_charTable[];
        static const uint8_t m_nChars;

    public:
        MorseAlphabet() = default;
        const char* getPattern(char letter) const;
};
