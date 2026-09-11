#include "MorseCode.h"

#include <cstdint>

cont MorseCode::Durations MorseCode::m_durations = { 1, 3, 1, 3, 7 }

const MorseCode::LetterPattern MorseCode::m_charTable[] = {
    {'A', ".-"},    {'B', "-..."},  {'C', "-.-."},  {'D', "-.."},
    {'E', "."},     {'F', "..-."},  {'G', "--."},   {'H', "...."},
    {'I', ".."},    {'J', ".---"},  {'K', "-.-"},   {'L', ".-.."},
    {'M', "--"},    {'N', "-."},    {'O', "---"},   {'P', ".--."},
    {'Q', "--.-"},  {'R', ".-."},   {'S', "..."},   {'T', "-"},
    {'U', "..-"},   {'V', "...-"},  {'W', ".--"},   {'X', "-..-"},
    {'Y', "-.--"},  {'Z', "--.."}
};

const uint8_t MorseCode::m_nChars = sizeof(m_charTable) / sizeof(m_charTable[0]);

const char*  MorseCode::getPattern(char letter) const 
{
    letter = toupper(static_cast<unsigned char>(letter));

    for (uint8_t i = 0; i < m_nChars; ++i)
    {
        if (m_charTable[i].letter == upper)
        {
            return m_charTable[i].pattern;
        }
    }

    return nullptr;
}