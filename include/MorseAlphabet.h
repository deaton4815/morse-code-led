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

        static constexpr LetterPattern m_charTable[] = {
            {'A', ".-"},    {'B', "-..."},  {'C', "-.-."},  {'D', "-.."},
            {'E', "."},     {'F', "..-."},  {'G', "--."},   {'H', "...."},
            {'I', ".."},    {'J', ".---"},  {'K', "-.-"},   {'L', ".-.."},
            {'M', "--"},    {'N', "-."},    {'O', "---"},   {'P', ".--."},
            {'Q', "--.-"},  {'R', ".-."},   {'S', "..."},   {'T', "-"},
            {'U', "..-"},   {'V', "...-"},  {'W', ".--"},   {'X', "-..-"},
            {'Y', "-.--"},  {'Z', "--.."}
        };

        static constexpr uint8_t m_nChars = sizeof(m_charTable) / sizeof(m_charTable[0]);

    public:
        MorseAlphabet() = delete;
        static const char* getPattern(char letter);
};
