#pragma once

#include <cstdint>

enum class LineStatus : uint8_t
{
    Pending,    // no complete line yet; keep polling
    LineReady,  // a full line is available via getLine()
    Sentinel    // the Ctrl-Z sentinel was seen; caller should stop
};

// Non-blocking accumulator for one line of Serial input at a time.
// poll() must be called every loop() iteration; it only consumes bytes
// that are already waiting, so it never stalls the round-robin loop.
class LineReader
{
    private:

        static constexpr uint16_t MAX_LINE_LENGTH = 128;
        static constexpr char SENTINEL_CHAR = 0x1A; // Ctrl-Z (ASCII SUB)

        char m_buffer[MAX_LINE_LENGTH];
        uint16_t m_length = 0;

    public:
        LineReader() = default;
        LineReader(const LineReader&) = delete;
        LineReader& operator=(const LineReader&) = delete;

        LineStatus poll();
        const char* getLine() const;
};
