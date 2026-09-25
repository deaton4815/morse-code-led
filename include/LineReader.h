#pragma once

#include <cstdint>

enum class LineStatus : uint8_t
{
    Pending,    // No complete line. Keep polling
    LineReady,  // User hits Enter key. Full line is available via getLine()
    Sentinel    // Ctrl-Z sentinel was seen; Stop Caller
};

/*
Non-blocking accumulator for one line of Serial input at a time.
Poll() must be called every loop() iteration.
It only consumes bytes that are already waiting, so it never stalls the round-robin loop.
*/
class LineReader
{
    private:

        // Longest line including the terminating '\0'.
        // Characters typed beyond this are silently dropped.
        static constexpr uint16_t MAX_LINE_LENGTH = 128;

        // Ctrl-Z sentinel
        static constexpr char SENTINEL_CHAR = 0x1A;

        char m_buffer[MAX_LINE_LENGTH];
        uint16_t m_length = 0;

    public:
        LineReader() = default;

        // Copying is disabled
        LineReader(const LineReader&) = delete;
        LineReader& operator=(const LineReader&) = delete;

        // Drains bytes (or no bytes) waiting in serial each loop iteration.
        // Returns LineReady once per completed line.
        // Completed line read with getLine() before next poll() call
        LineStatus poll();

        // Returns a null-terminated pointer into this object's own internal buffer,
        // only valid until the next poll() call.
        const char* getLine() const;
};
