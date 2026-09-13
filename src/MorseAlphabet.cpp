#include "MorseAlphabet.h"

#include <cstdint>
#include <cctype>

const char* MorseAlphabet::getPattern(char letter)
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
