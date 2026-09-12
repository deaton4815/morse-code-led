#include "PatternGenerator.h"

#include <cstdint>

class PatternGenerator
{
    private:

        void PatternGenerator::generatePattern(cont char* text)
        {
            uint16_t count = 0;
            Symbol prev = Symbol::WordGap;

            char c;
            for (uint16_t i = 0; text[i] != '\0'; ++i)
            {
                c = text[i];
                
                const char* pattern = m_alphabet.getPattern(c);
                
                bool isLetter = nullptr != pattern;
                bool isSpace = ' ' == c;
                if isLetter { generateLetter(pattern, count, prev); }
                else if isSpace { generateSpace(count); }

                prev = m_buffer[count-1];
            }
        }

        void PatternGenerator::generateLetter(cont char* pattern, uint16_t count, Symbol prev)
        {
            bool isNewWord = prev == Symbol::WordGap;
                for (uint16_t j = 0; pattern[j] != '\0'; ++j)
                {
                    if (j == 0) && (!isNewWord)
                    {
                        m_buffer[count++] == Symbol::LetterGap;
                     }
                    else if (j > 0)
                    {
                        m_buffer[count++] = Symbol::SymbolGap;
                    }
                    m_buffer[count++] = ('.' == pattern[j]) ? Symbol::Dit : Symbol::Dah;
                }
        }

        void PatternGenerator::generateSpace(uint16_t count)
        {
            m_buffer[count++] = Symbol::WordGap;
        }
}