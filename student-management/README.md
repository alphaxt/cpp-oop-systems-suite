# Student Management System (C++) 🎓

A console-based Student Management System built in C++, demonstrating practical use of core **Data Structures** — linked lists, stacks, and queues — alongside modular OOP design.

---

## ✨ Features

- **Add Students** — Store Roll Number, Name, Department, Semester, CGPA, and Contact Number
- **Display Records** — View all enrolled students in a formatted list
- **Search** — Locate a student instantly by Roll Number (Linear Search)
- **Delete Records** — Remove a student from the active database
- **Undo Delete** — Restore the most recently deleted student (Stack-powered)
- **Registration Queue** — Add pending students to a queue and enrol them sequentially (Queue-powered)
- **Sort Students** — View the list sorted numerically by Roll Number (Bubble Sort)

---

## 🧠 Data Structures Used

| Structure | Purpose |
|---|---|
| **Singly Linked List** | Primary dynamic database — scales without fixed-size limits |
| **Stack (LIFO)** | Powers the Undo Delete feature |
| **Queue (FIFO)** | Handles the Registration Queue in arrival order |
| **Vector + Bubble Sort** | Temporary sorted view without disrupting the main list |

---

## 💻 Tech Stack

- **Language:** C++17
- **Paradigm:** Object-Oriented Programming + Data Structures
- **Build:** GNU Make / CMake
- **Compiler:** GCC / G++ (any modern C++ compiler)

---

## 📂 Project Structure

```
Student-Management-System/
├── include/
│   ├── Student.h           # Student class and linked list Node definition
│   └── StudentSystem.h     # StudentSystem class declaration
├── src/
│   ├── main.cpp            # Entry point and interactive menu
│   └── StudentSystem.cpp   # Full implementation (add, delete, sort, search, etc.)
├── build/                  # Compiled output (git-ignored)
├── Makefile                # Build via `make`
├── CMakeLists.txt          # Build via CMake
└── README.md
```

---

## 🚀 Getting Started

**Clone the repository**
```bash
git clone https://github.com/alphaxt/Student-Management-System.git
cd Student-Management-System
```

**Build with Make**
```bash
make
./build/StudentApp
```

**Build with CMake**
```bash
cmake -B build -S .
cmake --build build
./build/StudentApp
```

**Build manually with g++**
```bash
g++ -std=c++17 -Iinclude -o build/StudentApp src/main.cpp src/StudentSystem.cpp
./build/StudentApp
```

---

## 🔮 Future Enhancements

- File handling (`<fstream>`) to persist records across sessions
- Input validation to handle non-numeric entries gracefully
- Binary Search Tree for O(log n) student lookup
- Multi-department filtering and reporting

---

## 📜 License

This project does not currently include a license file. To open-source it, add an [MIT License](https://choosealicense.com/licenses/mit/).

---

**Developed by Muhammad Danish**
