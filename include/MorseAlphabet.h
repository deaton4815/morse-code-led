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
        static constexpr uint8_t m_nChars = sizeof(m_charTable) / sizeof(m_charTable[0]);

    public:
        MorseAlphabet() = delete;
        static const char* getPattern(char letter) const;
};
