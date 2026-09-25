# Morse Code LED — Class Diagram

Generated from the current state of `include/*.h` and `src/main.cpp`.

```mermaid
classDiagram
    class LineStatus {
        <<enumeration>>
        Pending
        LineReady
        Sentinel
    }

    class Symbol {
        <<enumeration>>
        Dit
        Dah
        SymbolGap
        LetterGap
        WordGap
    }

    class LineReader {
        -char[] m_buffer
        -uint16_t m_length
        +LineReader()
        +poll() LineStatus
        +getLine() const char*
    }

    class MorseAlphabet {
        -LetterPattern[] m_charTable$
        -uint8_t m_nChars$
        +getPattern(char letter)$ const char*
    }

    class PatternGenerator {
        -Symbol[] m_buffer
        -uint16_t m_sizeBuffer
        -generateLetter(const char* pattern, Symbol prev)
        -generateSpace()
        -writeSymbol(Symbol sym)
        +generatePattern(const char* text)
        +getBuffer() const Symbol*
        +getSizeBuffer() uint16_t
    }

    class Time {
        -uint32_t m_btuMs
        -Durations m_durationsMs
        -uint32_t m_symbolStartMs
        -uint32_t m_symbolDurationMs
        -getTimestampMs() uint32_t
        -getDurationMs(Symbol symbol) uint32_t
        +Time(uint32_t btuMs)
        +newSymbol(Symbol symbol)
        +isSymbolComplete() bool
    }

    class Main {
        <<main.cpp>>
        -LineReader lineReader
        -PatternGenerator patternGenerator
        -Time time
        -bool halted
        -bool executingPattern
        -uint16_t currentSymbolIndex
        +setup()
        +loop()
    }

    Main *-- LineReader : owns
    Main *-- PatternGenerator : owns
    Main *-- Time : owns
    Main ..> Symbol : uses
    LineReader ..> LineStatus : returns
    PatternGenerator ..> MorseAlphabet : uses
    PatternGenerator *-- Symbol : owns
    Time ..> Symbol : uses
```

## Notes on how to read this

- `$` after a member marks it `static` (e.g. `MorseAlphabet::m_charTable`, `MorseAlphabet::getPattern`) — the class-level data/behavior that isn't tied to any one instance.
- `*--` (filled diamond) is composition: `Main` owns one `LineReader`, one `PatternGenerator`, and one `Time` as direct members, and their lifetimes are tied to `Main`'s.
- `..>` (dashed arrow) is a dependency: one type uses another (as a parameter, return type, or through a static call) without owning it.
- `Main` isn't a real C++ class — it's the anonymous namespace plus `setup()`/`loop()` in `main.cpp`, represented here as a class so its relationships to the real classes are visible in the same diagram.
