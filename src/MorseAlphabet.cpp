#include "MorseAlphabet.h"

#include <cstdint>
#include <cctype>

// Return Morse pattern for single character
const char* MorseAlphabet::getPattern(char letter)
{

    // convert to upper case for lookup table
    letter = static_cast<char>(toupper(static_cast<unsigned char>(letter)));

    // iterate through lookup table until correct character is found
    for (uint8_t i = 0; i < m_nChars; ++i)
    {
        if (m_charTable[i].letter == letter)
        {
            return m_charTable[i].pattern;
        }
    }

    // Move on with no errors if unrecognized character
    return nullptr;
}
