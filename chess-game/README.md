
# Chess Game (C++) ♟️

## Overview

This project is a text-based **Chess Game** developed in C++ using **Object-Oriented Programming (OOP)** concepts. It provides a classic two-player chess experience with a focus on implementing the core rules and logic of the game through a clean, console-based interface.

-----

## ✨ Features

  * **Two-player gameplay** on a standard 8x8 board 🧑‍🤝‍🧑
  * **Move validation** according to chess rules for each piece type (Pawn, Rook, Knight, Bishop, Queen, King) ✅
  * **Turn-based system** to alternate between players 🔄
  * **Detection of check** and **checkmate** conditions 👑
  * Display of the **chessboard** in the console 📊
  * Well-structured OOP design using classes for each component (Board, Piece, Player, etc.) 🏗️

-----

## 🛠️ Technologies Used

  * **C++** programming language
  * **Object-Oriented Programming** principles (Encapsulation, Inheritance, Polymorphism)
  * **Standard Template Library (STL)** for efficient data handling

## ⚙️ System Requirements

  * A C++ compiler (GCC, MinGW, or any modern C++ compiler)
  * Compatible with Windows, Linux, and macOS terminals

-----

## 🚀 Getting Started

### Clone the Repository

```
git clone https://github.com/alphaxt/Chess-game.git
```

### Compile the Project

Using `make`:

```
make
```

Or using CMake:

```
cmake -B build -S .
cmake --build build
```

Or directly with g++:

```
g++ -std=c++17 -Iinclude -o ChessGame src/*.cpp
```

### Run the Program

```
./ChessGame
```

-----

## 📂 Code Structure

```
Chess-game/
├── include/        # Header files (.h)
├── src/            # Source files (.cpp)
├── Makefile        # Build via `make`
├── CMakeLists.txt  # Build via CMake
└── README.md
```

  * `main.cpp` — Contains the program’s entry point and the main game loop.
  * `Board.h`/`Board.cpp` — Manages the chessboard state and display.
  * `Piece.h`/`Piece.cpp` — Serves as the base class for all chess pieces, handling common attributes.
  * Individual piece classes (`Pawn`, `Knight`, `Bishop`, `Rook`, `Queen`, `King`) — Inherit from `Piece` and implement specific move validation logic.
  * `Game.h`/`Game.cpp` — Manages the turn-based game loop and player turns.

## 💡 How It Works

1.  Upon launch, the game initializes a standard chessboard with all pieces in their starting positions.
2.  The game alternates between Player 1 (White) and Player 2 (Black) turns.
3.  Each player enters their desired move (e.g., `e2e4`).
4.  The system validates the move to ensure it adheres to the rules of chess for the selected piece.
5.  If the move is valid, the board is updated, and the game checks for check or checkmate conditions.
6.  The game continues until a checkmate, stalemate, or draw occurs.

-----

## 🎯 Future Enhancements

  * Implementation of castling, en passant, and pawn promotion rules
  * Addition of a simple AI opponent
  * Development of a Graphical User Interface (GUI) for a better user experience
  * Implementation of a game history or log to track all moves

-----

## 🤝 Contribution

Contributions are highly appreciated\! Please feel free to open issues for bugs or feature requests, or submit pull requests to improve the project.

-----

## 📜 License

This project is licensed under the **MIT License**.

-----

**Developed by Muhammad Danish**
