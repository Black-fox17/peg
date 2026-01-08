# Design Decisions: Refactoring Peg Game

## Overview
This document explains the reasoning behind the architectural changes in the Peg Game implementation, specifically moving from a monolithic `main.c` (as originally documented) to a modular design utilizing a dedicated `game` source file.

## Key Reasons

### 1. Preventing Code Duplication
*   **Old Design**: The original design exposed specific game logic steps directly in `main.c`. The main loop had to manually orchestrate `convert()`, `is_valid()`, `apply_move()`, and updating `game.moves`.
*   **Issue**: If we needed to implement another interface (like a test suite, an AI solver, or a GUI), we would have to duplicate that exact sequence of calls.
*   **Solution**: The new `game.c` creates a centralized place for this logic. `game_play_move()` encapsulates the entire process of making a move.

### 2. Avoiding Circular Dependencies
*   **Issue**: Tightly coupling the main application logic with the internal data structures (`board`, `move`) can lead to complex include chains and circular dependencies as the project grows.
*   **Solution**: We "reimagined" the architecture to layer the dependencies:
    *   Level 1: `Cell`, `Move` (Basic building blocks)
    *   Level 2: `Board` (Uses Cell and Move)
    *   Level 3: `Game` (Manages Board and Game State)
    *   Level 4: `Main` (Uses Game)
*   This hierarchy ensures a one-way flow of dependencies, keeping the architecture clean and compilable without hacks.

### 3. Simplified `main.c` & Clean Layout
*   **Before**:
    ```c
    // Logic cluttering the main loop
    move = convert(symmove);
    if(is_valid(&game.board,move)){
        apply_move(&game.board, move);
        game.moves++;
    }
    ```
*   **After**:
    ```c
    // Clean, high-level API usage
    if(game_play_move(&game, sym_move)){
        game_display(&game);
    }
    ```
*   The `main.c` file is now significantly smaller and cleaner. It is responsible only for **User Interaction** (Input/Output), while `game.c` is responsible for **Game Logic**.

### 4. Robustness
*   By using functions like `game_play_move`, we ensure that state updates (like incrementing the move counter) happen automatically whenever a valid move is made. The caller cannot accidentally "forget" to update the score, preventing bugs.
