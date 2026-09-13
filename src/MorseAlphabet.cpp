#include "MorseAlphabet.h"

#include <cstdint>
#include <cctype>

const MorseAlphabet::LetterPattern MorseAlphabet::m_charTable[] = {
    {'A', ".-"},    {'B', "-..."},  {'C', "-.-."},  {'D', "-.."},
    {'E', "."},     {'F', "..-."},  {'G', "--."},   {'H', "...."},
    {'I', ".."},    {'J', ".---"},  {'K', "-.-"},   {'L', ".-.."},
    {'M', "--"},    {'N', "-."},    {'O', "---"},   {'P', ".--."},
    {'Q', "--.-"},  {'R', ".-."},   {'S', "..."},   {'T', "-"},
    {'U', "..-"},   {'V', "...-"},  {'W', ".--"},   {'X', "-..-"},
    {'Y', "-.--"},  {'Z', "--.."}
};

const char* MorseAlphabet::getPattern(char letter) const
{
    letter = static_cast<char>(toupper(static_cast<unsigned char>(letter)));

    for (uint8_t i = 0; i < m_nChars; ++i)
    {
        if (m_charTable[i].letter == letter)
        {
            return m_charTable[i].pattern;
        }
    }

    return nullptr;
}
