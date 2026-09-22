cmake_minimum_required(VERSION 3.15)
project(CppSystemsSuite VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 1. Hospital Management System
add_executable(hospital_system
    hospital-management/src/main.cpp
    hospital-management/src/Hospital.cpp
)
target_include_directories(hospital_system PRIVATE hospital-management/include)

# 2. Hotel Management System
add_executable(hotel_system
    hotel-management/src/main.cpp
    hotel-management/src/bill.cpp
    hotel-management/src/booking.cpp
    hotel-management/src/date.cpp
    hotel-management/src/hotel_management.cpp
    hotel-management/src/menu_system.cpp
    hotel-management/src/person.cpp
    hotel-management/src/room.cpp
)
target_include_directories(hotel_system PRIVATE hotel-management/include)

# 3. Student Management System
add_executable(student_system
    student-management/src/main.cpp
    student-management/src/StudentSystem.cpp
)
target_include_directories(student_system PRIVATE student-management/include)

# 4. Chess Game
add_executable(chess_game
    chess-game/src/main.cpp
    chess-game/src/Bishop.cpp
    chess-game/src/Board.cpp
    chess-game/src/Game.cpp
    chess-game/src/King.cpp
    chess-game/src/Knight.cpp
    chess-game/src/Pawn.cpp
    chess-game/src/Piece.cpp
    chess-game/src/Queen.cpp
    chess-game/src/Rook.cpp
)
target_include_directories(chess_game PRIVATE chess-game/include)
