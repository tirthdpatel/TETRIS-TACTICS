# Tetris Game README

## Introduction

### Group Name
- **ELITES**

### Members

- Het Sachani - 202404035
- Tirth Patel - 202401227
- Jeet Patel - 202404026

---

### Requirement to Run
- **Operating System**: Windows only

---

### Objective

The Tetris Game is a classic puzzle game where the player controls falling tetrominoes (geometric shapes composed of four squares) that must be arranged to form complete horizontal lines. Completed lines are cleared, earning the player points, and the game ends when the stack of tetrominoes reaches the top of the play area.

---

## Files Used
1. `main.cpp`
2. `tetrominoes.h`
3. `tetrominoes.cpp`

---

## Header Files Used

1. `bits/stdc++.h`
2. `windows.h`
3. `conio.h`
4. `vector`

---

## Brief File Description

### main.cpp

The file `main.cpp` is used for:
- Starting the game
- Managing the game loop
- Rendering the grid and handling user input

### tetrominoes.h

5. Contains the `tetrominoes` class and a `node` structure.
6. **Structure `node`**:
   - `COORD p`: Position coordinates
   - `node* next`: Self-referencing pointer for linked list
   - Constructor to initialize the node
7. **Class `tetrominoes`**:
   - **Private**:
     - `vector<node*> shape`: Stores tetromino shapes
     - `node* current_shape`: Active tetromino
     - `char dir`: Movement direction
   - **Public**:
     - Shape generation functions: `O()`, `I()`, `S()`, `Z()`, `L()`, `J()`, `T()`
     - `Shape()`: Randomly selects a tetromino
     - `change_dir(char d)`: Sets movement direction
     - `move(const vector<vector<int>>& grid)`: Moves the tetromino
     - `collision(const vector<vector<int>>& grid)`: Detects collisions
     - `rotation(const vector<vector<int>>& grid)`: Rotates the tetromino
     - `get_current_shape()`: Accesses the current tetromino
     - `canSpawn(const vector<vector<int>>& grid)`: Checks if a tetromino can spawn
     - `freeShape(node* shape)`: Frees memory

### tetrominoes.cpp

Contains the implementation of functions declared in `tetrominoes.h`:
8. Constructor and destructor for `tetrominoes`
9. Functions to create each tetromino shape: `O()`, `I()`, `S()`, `Z()`, `L()`, `J()`, `T()`
10. `Shape()`: Randomly generates a new tetromino
11. `change_dir`: Updates movement direction
12. `move`: Handles tetromino movement (left, right, down)
13. `collision`: Checks for collisions with the grid or boundaries
14. `rotation`: Rotates the tetromino around a pivot point
15. `canSpawn`: Verifies if a new tetromino can appear without overlap
16. `freeShape`: Deallocates memory for tetromino nodes

---

## How Code Works

17. The `Grid` class in `main.cpp` creates a 20x10 grid (plus a 3-row buffer at the top) to manage the play area.
18. The `tetrominoes` class generates and controls falling tetrominoes using a linked list of nodes.
19. **Game Loop** (in `main.cpp`):
   - Renders the grid with the current tetromino
   - Handles user input:
     - `a`: Move left
     - `d`: Move right
     - `w`: Rotate clockwise
     - `q`: Quit game
   - Moves the tetromino down automatically and checks for collisions
20. When a tetromino collides with the grid or floor:
   - It locks into place
   - Full rows are cleared
   - A new tetromino spawns
21. **Game Over**: Occurs if a new tetromino cannot spawn without overlapping existing blocks.
22. The `hideCursor` function (from `windows.h`) hides the console cursor for a cleaner display.

---

## Features of The Game

23. **Start**: Begins with a randomly selected tetromino at the top center of the grid.
24. **Controls**:
   - `a`: Move left
   - `d`: Move right
   - `w`: Rotate clockwise
   - `q`: Quit game
25. **Display**:
   - `❌`: Walls
   - `⬜`: Tetromino blocks and locked pieces
   - Empty spaces: Unoccupied areas
26. **Scoring**:
   - 10 points per cleared row
   - Score displayed below the grid
27. **Game Over**:
   - Triggered when the grid fills to the top
   - Displays "Game Over! Final Score: [score]" and exits after a 2-second delay

---

## What We Learnt

28. **Linked Lists**: For tetromino representation
29. **Windows.h**: For console manipulation
30. **Conio.h**: For keyboard input
31. **Classes**: Object-oriented programming
32. **Header Files**: Multi-file compilation
33. **Random Number Generation**: For tetromino selection
34. **Grid-Based Game Logic**

---

## Acknowledgment

- **ChatGPT**

---