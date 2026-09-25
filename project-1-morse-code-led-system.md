# Project 1: Morse Code LED (or LCD) System Development

## Project – "Hello World"

Develop a C or C++ (or whatever other language you prefer) application which executes on an Arduino and displays a user-typed string, such as `Hello World`, as Morse code on an LED (or several LEDs), or an LCD. Implement all of the Morse code letters. The word or phrase should be typed and followed by Enter, and need not be an entire sentence with periods, commas, apostrophes, or other punctuation.

Use a round-robin design: repeatedly wait for a string, display it in Morse code, and exit the loop only when a sentinel like Ctrl-Z is entered.

Your round-robin design should be a simple, non-preemptive scheduling architecture where a main `while(1)` loop continuously performs the tasks of displaying Morse code in a sequential, cyclic order. It runs without a real-time operating system (RTOS), making it ideal for a simple Morse code application where the task of displaying Morse code does not have a strict timing requirement and there are no other tasks to be performed.

## The 5 Rules of Morse Code

1. **Dot Duration (1 unit)** — A dot (or "dit") is the basic unit of time, representing the shortest signal.
2. **Dash Duration (3 units)** — A dash (or "dah") is three times longer than a dot.
3. **Intra-Character Gap (1 unit)** — The silence between dots and dashes within a single letter is equal to 1 dot (1 unit).
4. **Inter-Character Gap (3 units)** — The space between two letters is equal to 3 dots (one dash duration).
5. **Inter-Word Gap (7 units)** — The space between two words is equal to 7 dots (or two dash durations plus one dit).

The basic unit of time corresponds to 12 words per minute, which results in a base unit of approximately 0.132 seconds (132 milliseconds).

This application can be developed using VS Code, Arduino Sketch, AVRDude, AVR Studio, WinAVR, or any other IDE you wish to use.

Submit per the directions in `Project Submission.docx`.

## Worked Example: "SOS"

An excellent example of Morse code that demonstrates all 5 timing rules is the distress signal SOS, frequently transmitted as:

```
... (pause) --- (pause) ...
```

### The 5 Rules Demonstrated in "SOS"

1. **Dot Duration (1 unit)** — The short marks (`.`) are each one unit long.
2. **Dash Duration (3 units)** — The long marks (`-`) are each three times longer than a dot.
3. **Intra-Character Gap (1 unit)** — The space between the dots within `S` (or dashes within `O`) is equal to one dot duration.
4. **Inter-Character Gap (3 units)** — The space separating the `S` from the `O` is equal to three dots.
5. **Word Gap (7 units)** — If `SOS` is followed by another word, the space between them is equal to seven dots.

### Visual Breakdown of "SOS"

| Segment | Pattern | Timing |
|---|---|---|
| S | `·` `(1)` `(1)` `·` `(1)` `(1)` `·` | Three dots with 1-unit gaps |
| Gap | — | 3 units between S and O |
| O | `−−−` `(3)` `(1)` `−−−` `(3)` `(1)` `−−−` | Three dashes with 1-unit gaps |
| Gap | — | 3 units between O and S |
| S | `·` `(1)` `(1)` `·` `(1)` `(1)` `·` | Three dots with 1-unit gaps |

The full sequence `...---...` represents the letters, while the precise timing of the gaps between them makes the message intelligible.

## International Morse Code Reference

| Char | Code | | Char | Code |
|---|---|---|---|---|
| A | `.-` | | U | `..-` |
| B | `-...` | | V | `...-` |
| C | `-.-.` | | W | `.--` |
| D | `-..` | | X | `-..-` |
| E | `.` | | Y | `-.--` |
| F | `..-.` | | Z | `--..` |
| G | `--.` | | | |
| H | `....` | | 1 | `.----` |
| I | `..` | | 2 | `..---` |
| J | `.---` | | 3 | `...--` |
| K | `-.-` | | 4 | `....-` |
| L | `.-..` | | 5 | `.....` |
| M | `--` | | 6 | `-....` |
| N | `-.` | | 7 | `--...` |
| O | `---` | | 8 | `---..` |
| P | `.--.` | | 9 | `----.` |
| Q | `--.-` | | 0 | `-----` |
| R | `.-.` | | | |
| S | `...` | | | |
| T | `-` | | | |
