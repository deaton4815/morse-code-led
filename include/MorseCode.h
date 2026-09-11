#pragma once

#include <cstdint>

class MorseCode
{
    private:
        struct Durations
        {
            uint8_t dit;
            uint8_t dah;
            uint8_t gap;
            uint8_t letterGap;
            uint8_t wordGap;
        };

        struct LetterPattern
        {
            char letter;
            const char* pattern;
        };
        
        static const Durations m_durations;
        static const LetterPattern m_charTable;
        static const uint8_t m_nChars;

    public:
        MorseCode() = default;
        const char* getPattern(char letter) const;
};
