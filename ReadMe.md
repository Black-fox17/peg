# Peg Solitaire Game

This project implements a console-based Peg Solitaire game in C.

## Code Structure

The source code is organized into the following files:

### Header Files (.h)
*   **`cell.h`**
    *   Defines the `cell` enum used to represent the state of each board position:
        *   `INVALID`: Unplayable areas (corners of the board).
        *   `EMPTY`: A hole with no peg.
        *   `PEG`: A hole with a peg.

*   **`move.h`**
    *   Defines the `move_t` structure for internal coordinate-based moves.
    *   Defines the `symbolized_move_t` structure for parsing user input (e.g., 'A1').
    *   Declares `convert()` to translate user input into internal coordinates.

*   **`board.h`**
    *   Defines the `board_t` structure, which holds the 7x7 grid of cells.
    *   Declares public functions for game logic, such as `create_board`, `print_board`, `is_valid`, and `apply_move`.

### Source Files (.c)
*   **`board.c`**
    *   **Logic Implementation**: Contains the actual code for the game rules.
    *   `create_board()`: Initializes the standard cross-shaped board layout.
    *   `is_valid()`: Checks if a move is legal (moving a peg over another peg into an empty spot).
    *   `apply_move()`: Updates the board state by removing the jumped peg and moving the source peg.
    *   `game_over()`: Checks if the game is won (only 1 peg remaining).

*   **`main.c`**
    *   **Entry Point**: Contains the `main()` function.
    *   **Game Loop**: Runs the `while(1)` loop that:
        1.  Checks for game over conditions.
        2.  Reads user input (e.g., "D2 D4").
        3.  Parses the input and converts it to coordinates.
        4.  Validates and applies the move.
        5.  Repairs the board display.

## How to Compile and Run

### Prerequisites
You need a C compiler installed on your system, such as GCC.

### Compilation
Open your terminal (Command Prompt, PowerShell, or bash) in the directory containing the source files and run the following command:

```bash
gcc main.c board.c -o peg_solitaire
```

This will compile `main.c` and `board.c`, linking them into an executable named `peg_solitaire`.

### Running the Game

**Windows:**
```cmd
peg_solitaire.exe
```

**Linux / macOS:**
```bash
./peg_solitaire
```

## How to Play
1.  The board is displayed with rows labeled **A-G** and columns **1-7**.
2.  Enter a move by specifying the **FROM** formatted coordinate and the **TO** formatted coordinate, separated by a space.
    *   *Example*: `D2 D4` (Moves the peg at D2 to D4, jumping over D3).
3.  Enter `q` to quit the game.
