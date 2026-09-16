/*
Map characters to Morse code representation
*/
#pragma once

#include <cstdint>

class MorseAlphabet
{
    private:

        // letter + Morse code data representation
        struct LetterPattern
        {
            char letter;
            const char* pattern;
        };

        // Morse code lookup table
        static constexpr LetterPattern m_charTable[] = {
            {'A', ".-"},    {'B', "-..."},  {'C', "-.-."},  {'D', "-.."},
            {'E', "."},     {'F', "..-."},  {'G', "--."},   {'H', "...."},
            {'I', ".."},    {'J', ".---"},  {'K', "-.-"},   {'L', ".-.."},
            {'M', "--"},    {'N', "-."},    {'O', "---"},   {'P', ".--."},
            {'Q', "--.-"},  {'R', ".-."},   {'S', "..."},   {'T', "-"},
            {'U', "..-"},   {'V', "...-"},  {'W', ".--"},   {'X', "-..-"},
            {'Y', "-.--"},  {'Z', "--.."},
            {'0', "-----"}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"},
            {'4', "....-"}, {'5', "....."}, {'6', "-...."}, {'7', "--..."},
            {'8', "---.."}, {'9', "----."}
        };

        static constexpr uint8_t m_nChars = sizeof(m_charTable) / sizeof(m_charTable[0]);

    public:
        MorseAlphabet() = delete;
        static const char* getPattern(char letter);
};
