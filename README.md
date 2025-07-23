# UNO-game

UNO (2-Player Console Game)

A **console-based UNO game** for 2 players, developed by me and my team mate Hanzala Ahsan. This the classic card game UNO works on Windows terminal, complete with colored cards, special card actions, and a persistent scoreboard.

---

## Features

- **Classic UNO gameplay** for two players.
- **Colored cards** using Windows console text colors.
- **Special Cards**: Skip, Reverse, Draw 2, Wild, Wild Draw 4.
- **Persistent scoreboard** (saved to `scoreboard.txt`).
- **Clear instructions** and easy menu navigation.
- **Replay support**: Play multiple games in a session.

---

## Getting Started

### Prerequisites

- **Windows OS** (uses Windows headers and `system("CLS")`/console colors)
- **C++ compiler** (e.g., MSVC, MinGW, Code::Blocks, or Dev C++)

### Compilation

1. Save the source code to `main.cpp`.
2. Open Command Prompt or your preferred IDE.
3. Compile:

   ```sh
   g++ main.cpp -o uno.exe
   ```

4. Run:

   ```sh
   uno.exe
   ```

---

## How to Play

1. **Launch** the game to see the main menu:
    - Play UNO
    - View Scoreboard
    - Exit

2. **Choose "Play UNO"** to start a new game.
3. **Each player gets 7 cards**. The rest form the deck.
4. **Turns alternate** between Player 1 and Player 2.
5. **Play a card** that matches color or number, or play a Wild card.
6. **Draw a card** if unable to play.
7. **Call UNO ("u")** when you are down to two cards.
8. **First player with no cards wins!**

---

## Game Controls

- **`C`** - Throw a card (then enter card number)
- **`D`** - Draw a card from deck
- **`U`** - Call UNO (when down to two cards)
- **`S`** - View scoreboard
- **`E`** - Exit game (with confirmation)

---

## Scoreboard

- After each game, results are saved to `scoreboard.txt`.
- Shows game number, winner, points, and cumulative scores.

---

## Dependencies

- Standard C++ libraries: `<iostream>`, `<iomanip>`, `<ctime>`, `<fstream>`, `<cstdlib>`, `<conio.h>`
- **Windows-only**: `<windows.h>` (for colored output), uses `system("CLS")` to clear screen.

---

## Future Improvements

- **Exit Option at Any Time**:  
  Add the ability to exit gracefully from any prompt or turn, not just from the main menu.

- **General Improvements**:
  - Input validation and error-proofing for all user inputs.
  - Cross-platform support (remove Windows dependencies, use ANSI colors).
  - Improved card visualization.
  - Add bot/AI for solo play.

*Feel free to contribute or fork this project!*

---

## Authors

- **Ermish Tabassum**
- **Hanzala Ahsan** 

---

## License

This project is provided for educational purposes. No commercial rights claimed.  
UNO is a trademark of Mattel Inc. This project is a fan implementation and **not affiliated with or endorsed by Mattel**.

---
