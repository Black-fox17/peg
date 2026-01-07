# Peg Solitaire (C Implementation)

This project is a modular C implementation of the classic Peg Solitaire game. It features a text-based interface, move validation, undo functionality, and a game timer.

## Code Logic & Structure

The codebase is organized into logical modules to separate concerns, making it clean, maintainable, and easy to extend.

### 1. Main Entry (`src/main.c`)
This file is the specific entry point for the program.
- **Logic**: It handles the read-eval-print loop (REPL). It captures user input, parses commands (moves, quit, undo), and calls the appropriate functions in the `Game` module.
- **Key Functions**:
  - `main()`: Initializes the game and runs the loop.
  - `process_input()`: Helper to parse raw user input strings.

### 2. Game Logic (`src/game.c`)
This module orchestrates the high-level rules and state of the game.
- **Logic**: It tracks the game status (active/over), the start time, and the number of penalties (invalid moves). It also checks for victory conditions (1 peg left) or loss conditions (no valid moves remaining).
- **Key Functions**:
  - `game_init()`: Sets up the board and resets the timer/history.
  - `game_play_move()`: Attempts to make a move; if valid, it applies it and saves it to history.
  - `game_undo()`: Reverses the last move if possible.
  - `game_over()`: Scans the board to see if any valid moves remain.

### 3. Board Management (`src/board.c`)
This module handles the physical representation of the board.
- **Logic**: The board is a 7x7 grid. This module knows how to initialize the classic "English Cross" shape and how to print it to the console.
- **Key Functions**:
  - `create_board()`: Fills the grid with pegs (`o`), empty spots (`.`), and invalid zones (spaces).
  - `print_board()`: Visualize the current state of the grid.
  - `count_pegs()`: Returns the number of pegs currently on the board.

### 4. Move Rules (`src/move.c`)
This module implements the specific mechanics of valid peg movement.
- **Logic**: A valid move requires a "from" peg, a "to" empty cell, and a "jumped over" peg in between. It handles coordinate conversion (e.g., "D2" -> `row:3, col:1`) and state updates.
- **Key Functions**:
  - `is_valid_move()`: Checks bounds, cell contents, and geometric validity of a jump.
  - `apply_move()`: Updates cells to reflect a move (1 peg jumps, 1 peg removed).
  - `undo_move()`: Restores the board state to before the move.
  - `convert()`: Translates user-friendly coordinates (A-G, 1-7) to array indices.

### 5. History System (`src/history.c`)
This module implements a stack data structure to support the undo feature.
- **Logic**: Stores a sequence of moves. "Push" adds a move when played, "Pop" retrieves the last move when undoing.
- **Key Functions**:
  - `history_push()`, `history_pop()`, `history_is_empty()`.

### 6. Cell Helpers (`src/cell.c`)
A utility module for safe grid access.
- **Logic**: Provides bounds-checked read/write access to the board array to prevent segmentation faults.
- **Key Functions**:
  - `check_cell()`: Returns the content of a cell (PEG, EMPTY, INVALID).
  - `set_cell()`: Safely modifies a cell's value.

---

## How to Compile and Run

You can compile the project using `gcc`. Ensure you represent the directory structure correctly (source files in `src/`, headers in `include/`).

### Compilation Command:
Run this command from the root project directory:

```bash
gcc src/*.c -Iinclude -o game
```

### Running the Game:
```bash
./game.exe
```

### Controls:
- **Move**: Enter coordinates in the format `FROM TO`.
  - Example: `D2 D4` (Moves the peg at D2 to the empty spot at D4).
- **Undo**: Enter `u` to undo the last move.
- **Quit**: Enter `q` to exit the game.
