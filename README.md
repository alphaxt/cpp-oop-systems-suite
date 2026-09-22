# 🏛️ C++ Systems Suite: OOP, Data Structures & Game Engine Collection

[![C++](https://img.shields.io/badge/Language-C%2B%2B17-00599C?style=flat&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/Build-CMake%20%7C%20Make-064F8C?style=flat&logo=cmake&logoColor=white)](https://cmake.org/)
[![Architecture](https://img.shields.io/badge/Design-Object--Oriented%20%2B%20Data%20Structures-F79F1F?style=flat)](https://github.com/alphaxt)
[![License](https://img.shields.io/badge/License-MIT-green?style=flat)](LICENSE)

A unified suite of **four modular console management engines and turn-based game systems** written in modern **C++17**. This collection serves as a complete showcase of core computer science principles: **Object-Oriented Architecture (Inheritance, Polymorphism, Dynamic Dispatch)**, **Custom Dynamic Data Structures (Linked Lists, Stacks, Queues)**, **Robust File Persistence**, and **Matrix Game State Engines**.

---

## 🧭 Systems Overview & Concept Matrix

| System | Primary CS Focus | Key Concepts & Patterns | State / Persistence |
| :--- | :--- | :--- | :--- |
| **🏥 Hospital Appointment System** | **Advanced OOP & Polymorphism** | Abstract base `Person`, virtual dispatch (`consultationFee()`, `display()`), runtime dynamic polymorphism via `Doctor*`, virtual destructors | Dynamic in-memory dispatch |
| **🏨 Hotel Management System** | **Modular Multi-Entity Architecture** | Separation of concerns across 8 classes (`Room`, `Booking`, `Bill`, `Date`, etc.), reservation state machine, automatic billing calculation | Persistent text-file storage (`fstream`) |
| **🎓 Student Records & Queue System** | **Custom Data Structures & Algorithms** | Custom Singly Linked List (no STL fixed bounds), LIFO Stack (undo deletion), FIFO Queue (sequential admissions), Bubble Sort | Dynamic heap node chains |
| **♟️ Terminal Chess Engine** | **OOP Game Architecture & Matrix Math** | Abstract base `Piece`, polymorphic piece classes (`King`, `Queen`, `Rook`, `Bishop`, `Knight`, `Pawn`), 8x8 matrix board state, geometric move validation | In-memory 2D board state matrix |

---

## 📂 Suite Directory Structure

```text
cpp-oop-systems-suite/
├── CMakeLists.txt                      # Unified CMake build script (builds all 4)
├── Makefile                            # Root Makefile for multi-target compilation
├── .gitignore                          # C++ binary & build artifact exclusions
├── README.md                           # Suite master documentation
│
├── hospital-management/                # Module 1: OOP & Dynamic Dispatch
│   ├── include/Hospital.h              # Base Person, Doctor hierarchy, Patient, Appointment
│   ├── src/Hospital.cpp & main.cpp     # Polymorphic logic & appointment scheduling
│   └── CMakeLists.txt & Makefile
│
├── hotel-management/                   # Module 2: Multi-Class Engine & File Persistence
│   ├── include/                        # Modular headers (enums, date, room, bill, etc.)
│   ├── src/                            # Modular implementations (bill, booking, date, etc.)
│   └── CMakeLists.txt & Makefile
│
├── student-management/                 # Module 3: Linked Lists, Stacks & Queues
│   ├── include/Student.h & StudentSystem.h # Custom node definitions & system class
│   ├── src/StudentSystem.cpp & main.cpp    # Custom data structures & sorting algorithms
│   └── CMakeLists.txt & Makefile
│
└── chess-game/                         # Module 4: Terminal Chess Engine & State Matrix
    ├── include/                        # Piece.h, Board.h, Game.h, King.h, Queen.h, ...
    ├── src/                            # Piece logic, 2D matrix validation & game loop
    └── CMakeLists.txt & Makefile
```

---

## 🔬 In-Depth Module Breakdown

### 1. 🏥 Hospital Appointment System
- **Class Hierarchy:**
  ```text
  Person (Base)
  ├── Doctor (Virtual methods: consultationFee(), display())
  │   ├── SpecialistDoctor   (Overridden fee & specialist profile)
  │   └── DifferentDoctor    (Custom consultation pricing)
  └── Patient                (Medical records & patient metadata)

  Appointment (Aggregates Patient and polymorphic Doctor*)
  ```
- **Key Engineering Features:** Runtime dynamic dispatch using base pointer collections (`Doctor*`), virtual destructors for safe dynamic deallocation.

### 2. 🏨 Hotel Management System
- **Modular Entities:** `Room`, `Booking`, `Bill`, `Date`, `Person`, and `HotelManagement`.
- **Key Engineering Features:** Multi-file modular architecture cleanly separating interface (`.h`) from implementation (`.cpp`), persistent disk storage using C++ file streams (`std::ifstream`, `std::ofstream`).

### 3. 🎓 Student Records & Queue System
- **Custom Structures Implemented:**
  - **Singly Linked List:** Primary scalable database eliminating fixed array size constraints.
  - **LIFO Stack (Undo Buffer):** Stores pointers to recently deleted student records for instant rollback.
  - **FIFO Queue (Admissions Processing):** Sequential order of arrival processing for applicant intake.
  - **In-Memory Sort:** Transcripts sorted by Roll Number on demand.

### 4. ♟️ Terminal Chess Engine
- **Piece Polymorphism Hierarchy:**
  ```text
  Piece (Abstract Base with virtual isMoveValid() & getSymbol())
  ├── King
  ├── Queen
  ├── Rook
  ├── Bishop
  ├── Knight
  └── Pawn
  ```
- **Key Engineering Features:**
  - 8x8 matrix board representation managing piece occupancy, movement legality, and path collision checks.
  - Turn-based alternating game loop with algebraic coordinate translation (e.g. `e2` to `e4`).
  - Strict movement boundary checks and king capture win condition detection.

---

## ⚡ Quick Start & Compilation

### Option A: Build Everything with CMake (Recommended)
Compile all four executables into a single `bin/` directory with two commands:

```bash
# Generate build configuration
cmake -B build

# Compile all 4 systems
cmake --build build

# Run any of the compiled binaries:
./build/bin/hospital_system
./build/bin/hotel_system
./build/bin/student_system
./build/bin/chess_game
```

---

### Option B: Build Everything with `make` (Linux / macOS / MinGW)

```bash
# Build all systems into bin/
make all

# Run:
./bin/hospital_system
./bin/hotel_system
./bin/student_system
./bin/chess_game
```

---

### Option C: Compile Any Individual System Directly via `g++`

```bash
# 1. Hospital Management
g++ -std=c++17 -Ihospital-management/include hospital-management/src/*.cpp -o hospital_system

# 2. Hotel Management
g++ -std=c++17 -Ihotel-management/include hotel-management/src/*.cpp -o hotel_system

# 3. Student Management
g++ -std=c++17 -Istudent-management/include student-management/src/*.cpp -o student_system

# 4. Chess Game
g++ -std=c++17 -Ichess-game/include chess-game/src/*.cpp -o chess_game
```

---

## 🛠️ Engineering Standards & Code Quality

- **Modern C++17 Standard:** Utilizes structured initializers, clean memory constructs, and standard library algorithms.
- **Zero Memory Leaks:** Dynamic memory allocations are paired with rigorous cleanup protocols and virtual destructors.
- **Cross-Platform Compatibility:** Builds cleanly on Windows (MSVC / MinGW), Linux (GCC / Clang), and macOS.
- **Separation of Concerns:** Clear directory segregation of headers (`include/`) from implementation units (`src/`).

---

## 👤 Author

**Muhammad Danish**
- **GitHub:** [@alphaxt](https://github.com/alphaxt)
- **LinkedIn:** [Muhammad Danish](https://www.linkedin.com/in/muhammad-danish1/)
- **Degree:** B.S. Data Science @ University of Central Punjab (UCP)

---

## 📄 License
This project is open-source under the [MIT License](LICENSE).
