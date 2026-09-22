#include "menu_system.h"
#include <iostream>
#include <limits>

MenuSystem::MenuSystem(std::shared_ptr<HotelManagementSystem> h) : hotel(h) {}

void MenuSystem::clearScreen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void MenuSystem::pause() const {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

int MenuSystem::getIntInput(const std::string& prompt) const {
    int value;
    std::cout << prompt;
    while (!(std::cin >> value)) {
        std::cout << "Invalid input! Please enter a number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

double MenuSystem::getDoubleInput(const std::string& prompt) const {
    double value;
    std::cout << prompt;
    while (!(std::cin >> value)) {
        std::cout << "Invalid input! Please enter a number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

std::string MenuSystem::getStringInput(const std::string& prompt) const {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

Date MenuSystem::getDateInput(const std::string& prompt) const {
    std::cout << prompt << std::endl;
    int day = getIntInput("Day (1-31): ");
    int month = getIntInput("Month (1-12): ");
    int year = getIntInput("Year: ");
    return Date(day, month, year);
}

void MenuSystem::displayWelcome() const {
    clearScreen();
    std::cout << std::string(60, '*') << std::endl;
    std::cout << "*" << std::string(58, ' ') << "*" << std::endl;
    std::cout << "*" << std::string(15, ' ') << "WELCOME TO " << hotel->getHotelName()
              << std::string(15, ' ') << "*" << std::endl;
    std::cout << "*" << std::string(18, ' ') << "Management System" << std::string(18, ' ') << "*" << std::endl;
    std::cout << "*" << std::string(58, ' ') << "*" << std::endl;
    std::cout << std::string(60, '*') << std::endl;
}

void MenuSystem::displayMainMenu() const {
    std::cout << "\n" << std::string(40, '=') << std::endl;
    std::cout << "           MAIN MENU" << std::endl;
    std::cout << std::string(40, '=') << std::endl;
    std::cout << "1. Customer Management" << std::endl;
    std::cout << "2. Room Management" << std::endl;
    std::cout << "3. Booking Management" << std::endl;
    std::cout << "4. Reports" << std::endl;
    std::cout << "5. Billing" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << std::string(40, '=') << std::endl;
}

void MenuSystem::customerMenu() {
    while (true) {
        clearScreen();
        std::cout << "\n" << std::string(40, '=') << std::endl;
        std::cout << "        CUSTOMER MANAGEMENT" << std::endl;
        std::cout << std::string(40, '=') << std::endl;
        std::cout << "1. Add New Customer" << std::endl;
        std::cout << "2. View All Customers" << std::endl;
        std::cout << "3. Search Customer by Name" << std::endl;
        std::cout << "0. Back to Main Menu" << std::endl;
        std::cout << std::string(40, '=') << std::endl;

        int choice = getIntInput("Enter your choice: ");

        switch (choice) {
            case 1: addNewCustomer(); break;
            case 2: hotel->displayAllCustomers(); pause(); break;
            case 3: searchCustomer(); break;
            case 0: return;
            default: std::cout << "Invalid choice! Please try again." << std::endl; pause(); break;
        }
    }
}

void MenuSystem::addNewCustomer() {
    std::cout << "\n" << std::string(40, '=') << std::endl;
    std::cout << "         ADD NEW CUSTOMER" << std::endl;
    std::cout << std::string(40, '=') << std::endl;

    std::string name = getStringInput("Enter customer name: ");
    std::string phone = getStringInput("Enter phone number: ");
    std::string email = getStringInput("Enter email address: ");
    std::string address = getStringInput("Enter address: ");
    std::string idProof = getStringInput("Enter ID proof (e.g., Aadhar, Passport): ");

    auto newCustomer = std::make_shared<Customer>(name, phone, email, address, idProof);
    if (hotel->addCustomer(newCustomer)) {
        std::cout << "Customer added successfully with ID: " << newCustomer->getId() << std::endl;
    } else {
        std::cout << "Failed to add customer." << std::endl;
    }
    pause();
}

void MenuSystem::searchCustomer() {
    std::string name = getStringInput("Enter customer name or part of name: ");
    hotel->searchCustomerByName(name);
    pause();
}

void MenuSystem::roomMenu() {
    while (true) {
        clearScreen();
        std::cout << "\n" << std::string(40, '=') << std::endl;
        std::cout << "          ROOM MANAGEMENT" << std::endl;
        std::cout << std::string(40, '=') << std::endl;
        std::cout << "1. View All Available Rooms" << std::endl;
        std::cout << "2. View Rooms by Type" << std::endl;
        std::cout << "0. Back to Main Menu" << std::endl;
        std::cout << std::string(40, '=') << std::endl;

        int choice = getIntInput("Enter your choice: ");

        switch (choice) {
            case 1: hotel->displayAvailableRooms(); pause(); break;
            case 2: handleRoomTypeSearch(); break;
            case 0: return;
            default: std::cout << "Invalid choice! Please try again." << std::endl; pause(); break;
        }
    }
}

void MenuSystem::handleRoomTypeSearch() {
    std::cout << "\n" << std::string(40, '=') << std::endl;
    std::cout << "        ROOM TYPES" << std::endl;
    std::cout << std::string(40, '=') << std::endl;
    std::cout << "1. Single" << std::endl;
    std::cout << "2. Double" << std::endl;
    std::cout << "3. Deluxe" << std::endl;
    std::cout << "4. Suite" << std::endl;
    int typeChoice = getIntInput("Enter room type: ");
    RoomType type;
    switch(typeChoice) {
        case 1: type = RoomType::SINGLE; break;
        case 2: type = RoomType::DOUBLE; break;
        case 3: type = RoomType::DELUXE; break;
        case 4: type = RoomType::SUITE; break;
        default: std::cout << "Invalid room type." << std::endl; pause(); return;
    }
    hotel->displayRoomsByType(type);
    pause();
}

void MenuSystem::bookingMenu() {
    while (true) {
        clearScreen();
        std::cout << "\n" << std::string(40, '=') << std::endl;
        std::cout << "        BOOKING MANAGEMENT" << std::endl;
        std::cout << std::string(40, '=') << std::endl;
        std::cout << "1. Make a New Booking" << std::endl;
        std::cout << "2. Check-in a Customer" << std::endl;
        std::cout << "3. Check-out a Customer" << std::endl;
        std::cout << "4. View All Bookings" << std::endl;
        std::cout << "0. Back to Main Menu" << std::endl;
        std::cout << std::string(40, '=') << std::endl;

        int choice = getIntInput("Enter your choice: ");

        switch (choice) {
            case 1: addNewBooking(); break;
            case 2: handleCheckIn(); break;
            case 3: handleCheckOut(); break;
            case 4: hotel->displayAllBookings(); pause(); break;
            case 0: return;
            default: std::cout << "Invalid choice! Please try again." << std::endl; pause(); break;
        }
    }
}

void MenuSystem::addNewBooking() {
    int customerId = getIntInput("Enter customer ID: ");
    int roomNumber = getIntInput("Enter room number: ");
    Date checkIn = getDateInput("Enter Check-in Date:");
    Date checkOut = getDateInput("Enter Check-out Date:");
    int guests = getIntInput("Enter number of guests: ");

    hotel->makeBooking(customerId, roomNumber, checkIn, checkOut, guests);
    pause();
}

void MenuSystem::handleCheckIn() {
    int bookingId = getIntInput("Enter booking ID to check in: ");
    hotel->checkIn(bookingId);
    pause();
}

void MenuSystem::handleCheckOut() {
    int bookingId = getIntInput("Enter booking ID to check out: ");
    hotel->checkOut(bookingId);
    pause();
}

void MenuSystem::reportsMenu() {
    while (true) {
        clearScreen();
        std::cout << "\n" << std::string(40, '=') << std::endl;
        std::cout << "           REPORTS MENU" << std::endl;
        std::cout << std::string(40, '=') << std::endl;
        std::cout << "1. Occupancy Report" << std::endl;
        std::cout << "0. Back to Main Menu" << std::endl;
        std::cout << std::string(40, '=') << std::endl;

        int choice = getIntInput("Enter your choice: ");

        switch (choice) {
            case 1: hotel->generateOccupancyReport(); pause(); break;
            case 0: return;
            default: std::cout << "Invalid choice! Please try again." << std::endl; pause(); break;
        }
    }
}

void MenuSystem::billingMenu() {
    while (true) {
        clearScreen();
        std::cout << "\n" << std::string(40, '=') << std::endl;
        std::cout << "           BILLING MENU" << std::endl;
        std::cout << std::string(40, '=') << std::endl;
        std::cout << "1. Pay a Bill" << std::endl;
        std::cout << "0. Back to Main Menu" << std::endl;
        std::cout << std::string(40, '=') << std::endl;

        int choice = getIntInput("Enter your choice: ");

        switch (choice) {
            case 1: handlePayBill(); break;
            case 0: return;
            default: std::cout << "Invalid choice! Please try again." << std::endl; pause(); break;
        }
    }
}

void MenuSystem::handlePayBill() {
    int billId = getIntInput("Enter bill ID to pay: ");
    hotel->payBill(billId);
    pause();
}

void MenuSystem::run() {
    displayWelcome();
    pause();
    while (true) {
        clearScreen();
        displayMainMenu();
        int choice = getIntInput("Enter your choice: ");
        switch (choice) {
            case 1: customerMenu(); break;
            case 2: roomMenu(); break;
            case 3: bookingMenu(); break;
            case 4: reportsMenu(); break;
            case 5: billingMenu(); break;
            case 0: std::cout << "Exiting system. Goodbye!" << std::endl; return;
            default: std::cout << "Invalid choice! Please try again." << std::endl; pause(); break;
        }
    }
}