#include "PatternGenerator.h"

#include <cstdint>

void PatternGenerator::PatternGenerator()
: m_sizeBuffer(0) {};

void PatternGenerator::generatePattern(const char* text)
{
    m_sizeBuffer = 0;
    Symbol prev = Symbol::WordGap;

    for (uint16_t i = 0; text[i] != '\0'; ++i)
    {
        char c = text[i];

        const char* pattern = MorseAlphabet::getPattern(c);

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
    }
}

void PatternGenerator::generateLetter(const char* pattern, Symbol prev)
{
    bool isNewWord = (prev == Symbol::WordGap);

    for (uint16_t j = 0; pattern[j] != '\0'; ++j)
    {

        if ((j == 0) && (!isNewWord))
        {
            writeSymbol(Symbol::LetterGap);
        }
        else if (j > 0)
        {
            writeSymbol(Symbol::SymbolGap);
        }
        sym = ('.' == pattern[j]) ? Symbol::Dit : Symbol::Dah;
        writeSymbol(sym);
    }
}

void PatternGenerator::generateSpace()
{
    writeSymbol(Symbol::WordGap);
}

void PatternGenerator::writeSymbol(Symbol sym)
{
    if (m_sizeBuffer >= MAX_PATTERN_SYMBOLS) { return; }
    m_buffer[m_sizeBuffer++] = sym;
}

const Symbol* PatternGenerator::getBuffer() const
{
    return m_buffer;
}

const uint16_t PatternGenerator::getSizeBuffer() const
{
    return m_sizeBuffer;
}
