# Hospital Appointment System (C++) 🏥

A console-based Hospital Appointment Management System built in **C++**, demonstrating real-world use of **Object-Oriented Programming** — inheritance, polymorphism, encapsulation, and dynamic dispatch.

---

## ✨ Features

- View all available doctors and their specializations
- Add new patients to the system
- Book appointments with available doctors
- Cancel appointments and restore doctor availability
- View full appointment history
- Multiple doctor types with different consultation fees (via polymorphism)

---

## 🧠 OOP Concepts Used

| Concept | Where Applied |
|---|---|
| **Inheritance** | `Doctor`, `Patient` inherit from `Person`; `SpecialistDoctor` and `DifferentDoctor` inherit from `Doctor` |
| **Polymorphism** | `consultationFee()` and `display()` are virtual — overridden per doctor type |
| **Encapsulation** | Private/protected member variables accessed through public methods |
| **Dynamic Memory** | `Doctor*` array with `new`/`delete` for runtime polymorphism |
| **Virtual Destructor** | `Doctor` has `virtual ~Doctor()` to ensure correct cleanup of derived objects |

---

## 📐 Class Hierarchy

```
Person
├── Doctor
│   ├── SpecialistDoctor   (higher consultation fee)
│   └── DifferentDoctor    (different consultation fee)
└── Patient

Appointment                 (holds a Patient + Doctor*)
```

---

## 💻 Tech Stack

- **Language:** C++17
- **Paradigm:** Object-Oriented Programming
- **Build:** GNU Make / CMake
- **Compiler:** GCC / G++ (any modern C++ compiler)

---

## 📂 Project Structure

```
Hospital-Management-System-OOP/
├── include/
│   └── Hospital.h          # All class declarations (Person, Doctor, Patient, Appointment)
├── src/
│   ├── main.cpp            # Entry point and interactive menu
│   └── Hospital.cpp        # Full implementation of all classes
├── build/                  # Compiled output (git-ignored)
├── Makefile                # Build via `make`
├── CMakeLists.txt          # Build via CMake
└── README.md
```

---

## 🚀 Getting Started

**Clone the repository**
```bash
git clone https://github.com/alphaxt/Hospital-Management-System-OOP.git
cd Hospital-Management-System-OOP
```

**Build with Make**
```bash
make
./build/HospitalApp
```

**Build with CMake**
```bash
cmake -B build -S .
cmake --build build
./build/HospitalApp
```

**Build manually with g++**
```bash
g++ -std=c++17 -Iinclude -o build/HospitalApp src/main.cpp src/Hospital.cpp
./build/HospitalApp
```

---

## 🔮 Future Enhancements

- File handling to persist patients and appointments across sessions
- Input validation and error handling for invalid menu choices
- Database integration (SQLite) for scalable storage
- Multi-department filtering and appointment scheduling by date/time

---

## 📜 License

This project is licensed under the [MIT License](LICENSE).

---

**Developed by Muhammad Danish**
