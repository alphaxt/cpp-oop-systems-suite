# 🏛️ C++ Systems Suite: OOP & Data Structures Collection

[![C++](https://img.shields.io/badge/Language-C%2B%2B17-00599C?style=flat&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/Build-CMake%20%7C%20Make-064F8C?style=flat&logo=cmake&logoColor=white)](https://cmake.org/)
[![Architecture](https://img.shields.io/badge/Design-Object--Oriented%20%2B%20Data%20Structures-F79F1F?style=flat)](https://github.com/alphaxt)
[![License](https://img.shields.io/badge/License-MIT-green?style=flat)](LICENSE)

A unified suite of **three modular console management engines** written in modern **C++17**. This collection serves as a complete showcase of core computer science principles: **Object-Oriented Architecture (Inheritance, Polymorphism, Dynamic Dispatch)**, **Custom Dynamic Data Structures (Linked Lists, Stacks, Queues)**, and **Robust File Persistence**.

---

## 🧭 Systems Overview & Concept Matrix

| System | Primary CS Focus | Key Concepts & Patterns | State / Persistence |
| :--- | :--- | :--- | :--- |
| **🏥 Hospital Appointment System** | **Advanced OOP & Polymorphism** | Abstract base `Person`, virtual dispatch (`consultationFee()`, `display()`), runtime dynamic polymorphism via `Doctor*`, virtual destructors | Dynamic in-memory dispatch |
| **🏨 Hotel Management System** | **Modular Multi-Entity Architecture** | Separation of concerns across 8 classes (`Room`, `Booking`, `Bill`, `Date`, etc.), reservation state machine, automatic billing calculation | Persistent text-file storage (`fstream`) |
| **🎓 Student Records & Queue System** | **Custom Data Structures & Algorithms** | Custom Singly Linked List (no STL fixed bounds), LIFO Stack (undo deletion), FIFO Queue (sequential admissions), Bubble Sort | Dynamic heap node chains |

---

## 📂 Suite Directory Structure

```text
cpp-oop-systems-suite/
├── CMakeLists.txt                      # Unified CMake build script (builds all 3)
├── Makefile                            # Root Makefile for multi-target compilation
├── .gitignore                          # C++ binary & build artifact exclusions
├── README.md                           # Suite master documentation
│
├── hospital-management/                # Module 1: OOP & Dynamic Dispatch
│   ├── include/
│   │   └── Hospital.h                  # Base Person, Doctor hierarchy, Patient, Appointment
│   ├── src/
│   │   ├── Hospital.cpp                # Polymorphic logic & appointment scheduling
│   │   └── main.cpp                    # Interactive terminal CLI
│   ├── CMakeLists.txt & Makefile
│   └── README.md
│
├── hotel-management/                   # Module 2: Multi-Class Engine & File Persistence
│   ├── include/                        # Modular headers (enums, date, room, bill, etc.)
│   │   ├── bill.h, booking.h, date.h, enums.h, hotel_management.h, menu_system.h, ...
│   │   └── person.h, room.h
│   ├── src/                            # Modular implementations
│   │   ├── bill.cpp, booking.cpp, date.cpp, hotel_management.cpp, ...
│   │   └── main.cpp
│   ├── CMakeLists.txt & Makefile
│   └── README.md
│
└── student-management/                 # Module 3: Linked Lists, Stacks & Queues
    ├── include/
    │   ├── Student.h                   # Student record & linked list Node definition
    │   └── StudentSystem.h             # Core engine: linked list, undo stack, queue
    ├── src/
    │   ├── StudentSystem.cpp           # Custom data structures & sorting algorithms
    │   └── main.cpp                    # Interactive terminal CLI
    ├── CMakeLists.txt & Makefile
    └── README.md
```

---

## 🔬 In-Depth Module Breakdown

### 1. 🏥 Hospital Appointment System
Designed around strict **OOP design principles** and dynamic polymorphism:
- **Class Hierarchy:**
  ```text
  Person (Base)
  ├── Doctor (Virtual methods: consultationFee(), display())
  │   ├── SpecialistDoctor   (Overridden fee & specialist profile)
  │   └── DifferentDoctor    (Custom consultation pricing)
  └── Patient                (Medical records & patient metadata)

  Appointment (Aggregates Patient and polymorphic Doctor*)
  ```
- **Key Engineering Features:**
  - Runtime dynamic dispatch using base pointer collections (`Doctor*`).
  - Virtual destructors ensuring complete and leak-free memory teardown during dynamic allocation.
  - Appointment lifecycle management: booking, doctor availability toggling, and history inspection.

---

### 2. 🏨 Hotel Management System
An enterprise-style terminal reservation engine organized across 8 decoupled classes:
- **Core Entities:**
  - `Room`: Tracks room categories (Standard, Deluxe, Suite), pricing, and real-time occupancy.
  - `Booking`: Manages check-in / check-out date intervals and customer linkage.
  - `Bill`: Generates detailed invoices calculating stay duration, taxes, and service items.
  - `Date`: Custom date validation, formatting, and day-difference calculation utilities.
- **Key Engineering Features:**
  - Multi-file modular C++ architecture cleanly separating interface (`.h`) from implementation (`.cpp`).
  - Persistent disk storage using C++ file streams (`std::ifstream`, `std::ofstream`).
  - Defensive terminal input sanitization with validation loops.

---

### 3. 🎓 Student Records & Queue System
Engineered using **from-scratch data structures** rather than relying solely on generic STL containers:
- **Custom Structures Implemented:**
  - **Singly Linked List:** Serves as the primary scalable database, eliminating fixed array limits and allowing $O(1)$ front insertion.
  - **LIFO Stack (Undo Buffer):** Stores pointers to recently deleted student records, providing a resilient 1-click **Undo Delete** feature.
  - **FIFO Queue (Admissions Processing):** Manages prospective applicants in sequential order of arrival for enrollment batches.
  - **In-Memory Sort:** Implements sorting algorithms to produce roll-number ordered transcripts on demand.

---

## ⚡ Quick Start & Compilation

### Option A: Build Everything with CMake (Recommended)
You can compile all three executables into a single `bin/` directory with two commands:

```bash
# Generate build configuration
cmake -B build

# Compile all 3 systems
cmake --build build

# Run any of the compiled binaries:
./build/bin/hospital_system
./build/bin/hotel_system
./build/bin/student_system
```

*(On Windows with MSVC, binaries will be located in `./build/bin/Debug/` or `./build/bin/`)*.

---

### Option B: Build Everything with `make` (Linux / macOS / MinGW)

```bash
# Build all systems into bin/
make all

# Run:
./bin/hospital_system
./bin/hotel_system
./bin/student_system
```

---

### Option C: Compile Any Individual System Directly via `g++`

```bash
# 1. Hospital Management
g++ -std=c++17 -Ihospital-management/include hospital-management/src/*.cpp -o hospital_system
./hospital_system

# 2. Hotel Management
g++ -std=c++17 -Ihotel-management/include hotel-management/src/*.cpp -o hotel_system
./hotel_system

# 3. Student Management
g++ -std=c++17 -Istudent-management/include student-management/src/*.cpp -o student_system
./student_system
```

---

## 🛠️ Engineering Standards & Code Quality

- **Modern C++17 Standard:** Utilizes structured initializers, clean memory constructs, and standard library algorithms.
- **Zero Memory Leaks:** Dynamic memory allocations are matched with rigorous cleanup protocols and virtual destructors.
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
