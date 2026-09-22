# Hotel Management System (C++) 🏨

A terminal-based hotel management system built in C++ using Object-Oriented Programming. Manage room bookings, customer records, and billing — all through a clean, interactive menu interface.

---

## ✨ Features

- Room reservation and cancellation
- Customer information management
- Real-time room availability status
- Automatic billing and invoice generation
- Persistent data storage via C++ file I/O
- Well-structured OOP design (Encapsulation, Inheritance, Polymorphism)
- Text-based menu interface compatible with any terminal

---

## 💻 Tech Stack

- **Language:** C++17
- **Paradigm:** Object-Oriented Programming
- **Libraries:** STL (map, memory, vector), File I/O streams
- **Build:** GNU Make / CMake
- **Compiler:** GCC / G++ (any modern C++ compiler)

---

## 📂 Project Structure

```
hotel-management-system/
├── include/                    # Header files (.h)
│   ├── enums.h                 # Shared enumerations (RoomType, BookingStatus, etc.)
│   ├── date.h                  # Date utility class
│   ├── person.h                # Base Person class
│   ├── room.h                  # Room class
│   ├── booking.h               # Booking class
│   ├── bill.h                  # Bill / invoice class
│   ├── hotel_management.h      # Core HotelManagement engine
│   └── menu_system.h           # Terminal menu interface
├── src/                        # Implementation files (.cpp)
│   ├── main.cpp                # Entry point
│   ├── date.cpp
│   ├── person.cpp
│   ├── room.cpp
│   ├── booking.cpp
│   ├── bill.cpp
│   ├── hotel_management.cpp
│   └── menu_system.cpp
├── build/                      # Compiled output (git-ignored)
├── Makefile                    # Build via `make`
├── CMakeLists.txt              # Build via CMake
└── README.md
```

---

## ⚙️ System Requirements

- GCC / G++ with C++17 support (`g++ --version` to check)
- Compatible with Windows, Linux, and macOS

---

## 🚀 Getting Started

**Clone the repository**
```bash
git clone https://github.com/alphaxt/hotel-management-system.git
cd hotel-management-system
```

**Build with Make**
```bash
make
./build/HotelManagement
```

**Build with CMake**
```bash
cmake -B build -S .
cmake --build build
./build/HotelManagement
```

**Build manually with g++**
```bash
g++ -std=c++17 -Iinclude -o build/HotelManagement src/*.cpp
./build/HotelManagement
```

---

## 💡 How It Works

On launch the system presents a menu with options for customer management, room booking, availability checks, billing, and exit. Key behaviours:

- **Booking a room** updates the room status and creates a linked customer record
- **Billing** calculates charges based on room type and length of stay, then prints an invoice
- **Data persistence** — all bookings and customer data are saved to `.dat` files and reloaded automatically on the next run

---

## 🎯 Future Enhancements

- Database integration (SQLite) to replace flat-file storage
- Multi-user roles with authentication and access control
- Additional room types, discounts, and promotions
- GUI front-end or web dashboard

---

## 🤝 Contributing

Contributions are welcome! Open an issue for bugs or feature requests, or submit a pull request.

---

## 📜 License

This project is licensed under the [MIT License](LICENSE).

---

**Developed by Muhammad Danish**
