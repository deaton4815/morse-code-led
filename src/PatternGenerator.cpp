#include "PatternGenerator.h"

#include <cstdint>

// Generate pattern for new line of text
void PatternGenerator::generatePattern(const char* text)
{
    // Reset buffer size (used by this pattern) to zero
    m_sizeBuffer = 0;

    // Seed prev to WordGap. Skips leading LetterGap before first word
    Symbol prev = Symbol::WordGap;

    // iterate through text
    for (uint16_t i = 0; text[i] != '\0'; ++i)
    {
        char c = text[i];

        const char* pattern = MorseAlphabet::getPattern(c);

        bool isLetter = nullptr != pattern; // is a letter or digit
        bool isSpace = (' ' == c); // is a space

        // Add letter/digit or space to pattern sequence with appropriate spaces
        if (isLetter)
        {
            generateLetter(pattern, prev);
        }
        else if (isSpace)
        {
            generateSpace();
        }

        // Update prev
        if ((isLetter || isSpace) && m_sizeBuffer > 0)
        {
            prev = m_buffer[m_sizeBuffer - 1];
        }
    }

    // Append word gap to end of pattern in case new sequence stars right after
    generateSpace();
}

// Generate pattern for letter/digit
void PatternGenerator::generateLetter(const char* pattern, Symbol prev)
{
    // Check if first letter of a word
    bool isNewWord = (prev == Symbol::WordGap);

    // Iterate through the character's pattern
    for (uint16_t j = 0; pattern[j] != '\0'; ++j)
    {
        // Add appropriate preceding gap to buffer
        if ((j == 0) && (!isNewWord)) // Preceding etter gap if first symbol of Morse pattern and not a new word
        {
            writeSymbol(Symbol::LetterGap);
        }
        else if (j > 0)
        {
            writeSymbol(Symbol::SymbolGap); // Preceding symbol gap for all other symbols of the Morse pattern
        }

        // Write symbol to buffer
        writeSymbol(('.' == pattern[j]) ? Symbol::Dit : Symbol::Dah);
    }
}

//  Write wordgap (when space character) too buffer
void PatternGenerator::generateSpace()
{
    writeSymbol(Symbol::WordGap);
}

// Write symbol to buffer
void PatternGenerator::writeSymbol(Symbol sym)
{
    // Fixed-size buffer, silently drop if overflow
    if (m_sizeBuffer >= MAX_PATTERN_SYMBOLS) { return; }

    // write symbol and iterate buffer size counter
    m_buffer[m_sizeBuffer++] = sym;
}

const Symbol* PatternGenerator::getBuffer() const
{
    return m_buffer;
}

uint16_t PatternGenerator::getSizeBuffer() const
{
    return m_sizeBuffer;
}