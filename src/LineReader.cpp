#include "LineReader.h"

#include <Arduino.h>

LineStatus LineReader::poll()
{
    // Consumes every byte already sitting in the Serial receive buffer.
    // Does not wait for bytes that have not arrived
    while (Serial.available() > 0)
    {
        char c = static_cast<char>(Serial.read());

        // Ctrl + Z entered
        if (c == SENTINEL_CHAR)
        {
            // Discard partial line if sentinel
            m_length = 0;
            return LineStatus::Sentinel;
        }

        // Line terminator
        if ((c == '\n') || (c == '\r'))
        {
            if (m_length == 0)
            {
                // skip reading empty line
                continue;
            }

            // return line ready with terminating character in buffer for coimpleted line
            m_buffer[m_length] = '\0';
            m_length = 0;
            return LineStatus::LineReady;
        }

        // Add character to buffer
        if (m_length < (MAX_LINE_LENGTH - 1))
        {
            m_buffer[m_length++] = c;
        }
        // Drop characters beyond max length
    }

    return LineStatus::Pending;
}

const char* LineReader::getLine() const
{
    return m_buffer;
}
