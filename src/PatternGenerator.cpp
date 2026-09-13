#include "PatternGenerator.h"

#include <cstdint>

void PatternGenerator::generate(const char* text)
{
    m_sizeBuffer = 0;
    generatePattern(text);
}

void PatternGenerator::generatePattern(const char* text)
{
    Symbol prev = Symbol::WordGap;

    for (uint16_t i = 0; text[i] != '\0'; ++i)
    {
        char c = text[i];

        const char* pattern = m_alphabet.getPattern(c);

        bool isLetter = nullptr != pattern;
        bool isSpace = (' ' == c);

        if (isLetter)
        {
            generateLetter(pattern, prev);
        }
        else if (isSpace)
        {
            generateSpace();
        }

        if ((isLetter || isSpace) && m_sizeBuffer > 0)
        {
            prev = m_buffer[m_sizeBuffer - 1];
        }

        if (m_sizeBuffer >= MAX_PATTERN_SYMBOLS-5) { return; }
    }
}

void PatternGenerator::generateLetter(const char* pattern, Symbol prev)
{
    bool isNewWord = (prev == Symbol::WordGap);

    for (uint16_t j = 0; pattern[j] != '\0'; ++j)
    {

        if ((j == 0) && (!isNewWord))
        {
            m_buffer[m_sizeBuffer++] = Symbol::LetterGap;
        }
        else if (j > 0)
        {
            m_buffer[m_sizeBuffer++] = Symbol::SymbolGap;
        }

        m_buffer[m_sizeBuffer++] = ('.' == pattern[j]) ? Symbol::Dit : Symbol::Dah;
    }
}

void PatternGenerator::generateSpace()
{
    m_buffer[m_sizeBuffer++] = Symbol::WordGap;
}

Symbol* PatternGenerator::getBuffer()
{
    return m_buffer;
}

uint16_t PatternGenerator::getSizeBuffer() const
{
    return m_sizeBuffer;
}
