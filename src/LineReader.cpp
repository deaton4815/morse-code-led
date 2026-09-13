#include "LineReader.h"

#include <Arduino.h>

LineStatus LineReader::poll()
{
    while (Serial.available() > 0)
    {
        char c = static_cast<char>(Serial.read());

        if (c == SENTINEL_CHAR)
        {
            m_length = 0;
            return LineStatus::Sentinel;
        }

        if ((c == '\n') || (c == '\r'))
        {
            if (m_length == 0)
            {
                // Swallow a lone terminator (e.g. the '\n' half of a
                // "\r\n" pair already handled by the '\r') so it doesn't
                // read as a spurious empty line.
                continue;
            }

            m_buffer[m_length] = '\0';
            m_length = 0;
            return LineStatus::LineReady;
        }

        if (m_length < (MAX_LINE_LENGTH - 1))
        {
            m_buffer[m_length++] = c;
        }
        // else: silently drop characters beyond MAX_LINE_LENGTH - 1
    }

    return LineStatus::Pending;
}

const char* LineReader::getLine() const
{
    return m_buffer;
}
