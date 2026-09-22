#include "hotel_management.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <limits> // for std::numeric_limits

// Helper functions for data persistence
int roomTypeToInt(RoomType type) {
    return static_cast<int>(type);
}

RoomType intToRoomType(int type) {
    return static_cast<RoomType>(type);
}

int roomStatusToInt(RoomStatus status) {
    return static_cast<int>(status);
}

RoomStatus intToRoomStatus(int status) {
    return static_cast<RoomStatus>(status);
}

int bookingStatusToInt(BookingStatus status) {
    return static_cast<int>(status);
}

BookingStatus intToBookingStatus(int status) {
    return static_cast<BookingStatus>(status);
}

HotelManagementSystem::HotelManagementSystem(const std::string& name) : hotelName(name) {
    // Rooms will be initialized either by loading from file or by the default initializer
}

double HotelManagementSystem::getRoomPrice(RoomType type) const {
    switch (type) {
        case RoomType::SINGLE: return 100.0;
        case RoomType::DOUBLE: return 150.0;
        case RoomType::DELUXE: return 250.0;
        case RoomType::SUITE: return 400.0;
        default: return 0.0;
    }
}

void HotelManagementSystem::initializeRooms() {
    // Add sample rooms if no rooms.dat file exists
    for (int i = 101; i <= 105; ++i) {
        addRoom(std::make_shared<Room>(i, RoomType::SINGLE, getRoomPrice(RoomType::SINGLE), 1));
    }
    for (int i = 201; i <= 205; ++i) {
        addRoom(std::make_shared<Room>(i, RoomType::DOUBLE, getRoomPrice(RoomType::DOUBLE), 2));
    }
    for (int i = 301; i <= 303; ++i) {
        addRoom(std::make_shared<Room>(i, RoomType::DELUXE, getRoomPrice(RoomType::DELUXE), 3));
    }
    for (int i = 401; i <= 402; ++i) {
        addRoom(std::make_shared<Room>(i, RoomType::SUITE, getRoomPrice(RoomType::SUITE), 4));
    }
}

// Data Persistence Methods
bool HotelManagementSystem::saveData() {
    bool saved = saveCustomersToFile() && saveRoomsToFile() && saveBookingsToFile() && saveBillsToFile();
    if (saved) {
        std::cout << "All data saved successfully." << std::endl;
    } else {
        std::cerr << "Failed to save some data." << std::endl;
    }
    return saved;
}

bool HotelManagementSystem::loadData() {
    bool loaded = loadCustomersFromFile() && loadRoomsFromFile() && loadBookingsFromFile() && loadBillsFromFile();
    if(rooms.empty()) {
        
        initializeRooms(); // Initialize default rooms if no rooms were loaded
	}

    if (loaded) {
        std::cout << "All data loaded successfully." << std::endl;
    } else {
        std::cerr << "Some data files were not found. Starting with available data." << std::endl;
    }
    return loaded;
}

bool HotelManagementSystem::saveCustomersToFile() const {
    std::ofstream file("customers.dat");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open customers.dat for writing." << std::endl;
        return false;
    }
    for (const auto& pair : customers) {
        auto customer = pair.second;
        file << customer->getId() << "|" << customer->getName() << "|"
             << customer->getPhone() << "|" << customer->getEmail() << "|"
             << customer->getAddress() << "|" << customer->getIdProof() << std::endl;
    }
    file.close();
    return true;
}

bool HotelManagementSystem::loadCustomersFromFile() {
    customers.clear();
    std::ifstream file("customers.dat");
    if (!file.is_open()) {
        std::cerr << "Warning: customers.dat not found. Starting with no customer data." << std::endl;
        Person::nextId = 0; // Reset ID counter
        return false;
    }

    std::string line;
    int maxId = 0;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, name, phone, email, address, idProof;
        std::getline(ss, idStr, '|');
        std::getline(ss, name, '|');
        std::getline(ss, phone, '|');
        std::getline(ss, email, '|');
        std::getline(ss, address, '|');
        std::getline(ss, idProof, '|');

        int id = std::stoi(idStr);
        auto customer = std::make_shared<Customer>(name, phone, email, address, idProof);
        customers[id] = customer;
        maxId = std::max(maxId, id);
    }
    Person::nextId = maxId;
    file.close();
    return true;
}

bool HotelManagementSystem::saveRoomsToFile() const {
    std::ofstream file("rooms.dat");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open rooms.dat for writing." << std::endl;
        return false;
    }
    for (const auto& pair : rooms) {
        auto room = pair.second;
        file << room->getRoomNumber() << "|" << roomTypeToInt(room->getType()) << "|"
             << roomStatusToInt(room->getStatus()) << "|"
             << room->getPricePerNight() << "|" << room->getCapacity() << std::endl;
    }
    file.close();
    return true;
}

bool HotelManagementSystem::loadRoomsFromFile() {
    rooms.clear();
    std::ifstream file("rooms.dat");
    if (!file.is_open()) {
        std::cerr << "Warning: rooms.dat not found. Initializing default rooms." << std::endl;
        initializeRooms();
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string roomNumStr, typeStr, statusStr, priceStr, capacityStr;
        std::getline(ss, roomNumStr, '|');
        std::getline(ss, typeStr, '|');
        std::getline(ss, statusStr, '|');
        std::getline(ss, priceStr, '|');
        std::getline(ss, capacityStr, '|');

        int roomNum = std::stoi(roomNumStr);
        RoomType type = intToRoomType(std::stoi(typeStr));
        RoomStatus status = intToRoomStatus(std::stoi(statusStr));
        double price = std::stod(priceStr);
        int capacity = std::stoi(capacityStr);

        auto room = std::make_shared<Room>(roomNum, type, price, capacity);
        room->setStatus(status);
        rooms[roomNum] = room;
    }
    file.close();
    return true;
}

bool HotelManagementSystem::saveBookingsToFile() const {
    std::ofstream file("bookings.dat");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open bookings.dat for writing." << std::endl;
        return false;
    }
    for (const auto& pair : bookings) {
        auto booking = pair.second;
        file << booking->getBookingId() << "|" << booking->getCustomerId() << "|"
             << booking->getRoomNumber() << "|" << booking->getCheckInDate().toString() << "|"
             << booking->getCheckOutDate().toString() << "|"
             << bookingStatusToInt(booking->getStatus()) << "|"
             << booking->getTotalAmount() << "|" << booking->getNumberOfGuests() << std::endl;
    }
    file.close();
    return true;
}

bool HotelManagementSystem::loadBookingsFromFile() {
    bookings.clear();
    std::ifstream file("bookings.dat");
    if (!file.is_open()) {
        std::cerr << "Warning: bookings.dat not found. Starting with no booking data." << std::endl;
        Booking::nextBookingId = 0;
        return false;
    }

    std::string line;
    int maxId = 0;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string bookingIdStr, custIdStr, roomNumStr, checkInStr, checkOutStr, statusStr, amountStr, guestsStr;
        std::getline(ss, bookingIdStr, '|');
        std::getline(ss, custIdStr, '|');
        std::getline(ss, roomNumStr, '|');
        std::getline(ss, checkInStr, '|');
        std::getline(ss, checkOutStr, '|');
        std::getline(ss, statusStr, '|');
        std::getline(ss, amountStr, '|');
        std::getline(ss, guestsStr, '|');

        int day1, month1, year1, day2, month2, year2;
        char slash;
        std::stringstream ss1(checkInStr);
        ss1 >> day1 >> slash >> month1 >> slash >> year1;
        std::stringstream ss2(checkOutStr);
        ss2 >> day2 >> slash >> month2 >> slash >> year2;

        Date checkIn(day1, month1, year1);
        Date checkOut(day2, month2, year2);

        int bookingId = std::stoi(bookingIdStr);
        int custId = std::stoi(custIdStr);
        int roomNum = std::stoi(roomNumStr);
        BookingStatus status = intToBookingStatus(std::stoi(statusStr));
        double amount = std::stod(amountStr);
        int guests = std::stoi(guestsStr);

        auto booking = std::make_shared<Booking>(custId, roomNum, checkIn, checkOut, amount, guests);
        booking->setStatus(status);
        bookings[bookingId] = booking;
        maxId = std::max(maxId, bookingId);
    }
    Booking::nextBookingId = maxId;
    file.close();
    return true;
}

bool HotelManagementSystem::saveBillsToFile() const {
    std::ofstream file("bills.dat");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open bills.dat for writing." << std::endl;
        return false;
    }
    for (const auto& pair : bills) {
        auto bill = pair.second;
        file << bill->getBillId() << "|" << bill->getBookingId() << "|"
             << bill->getTotalAmount() << "|" << bill->getIsPaid() << std::endl;
    }
    file.close();
    return true;
}

bool HotelManagementSystem::loadBillsFromFile() {
    bills.clear();
    std::ifstream file("bills.dat");
    if (!file.is_open()) {
        std::cerr << "Warning: bills.dat not found. Starting with no bill data." << std::endl;
        Bill::nextBillId = 0;
        return false;
    }

    std::string line;
    int maxId = 0;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string billIdStr, bookingIdStr, amountStr, isPaidStr;
        std::getline(ss, billIdStr, '|');
        std::getline(ss, bookingIdStr, '|');
        std::getline(ss, amountStr, '|');
        std::getline(ss, isPaidStr, '|');

        int billId = std::stoi(billIdStr);
        int bookingId = std::stoi(bookingIdStr);
        double amount = std::stod(amountStr);
        bool isPaid = (isPaidStr == "1");

        auto bill = std::make_shared<Bill>(bookingId, amount);
        if (isPaid) {
            bill->markAsPaid();
        }
        bills[billId] = bill;
        maxId = std::max(maxId, billId);
    }
    Bill::nextBillId = maxId;
    file.close();
    return true;
}

bool HotelManagementSystem::addCustomer(std::shared_ptr<Customer> customer) {
    if (customer) {
        customers[customer->getId()] = customer;
        return true;
    }
    return false;
}

bool HotelManagementSystem::addRoom(std::shared_ptr<Room> room) {
    if (room) {
        rooms[room->getRoomNumber()] = room;
        return true;
    }
    return false;
}

std::shared_ptr<Customer> HotelManagementSystem::findCustomer(int customerId) const {
    auto it = customers.find(customerId);
    return (it != customers.end()) ? it->second : nullptr;
}

std::shared_ptr<Room> HotelManagementSystem::findRoom(int roomNumber) const {
    auto it = rooms.find(roomNumber);
    return (it != rooms.end()) ? it->second : nullptr;
}

std::shared_ptr<Booking> HotelManagementSystem::findBooking(int bookingId) const {
    auto it = bookings.find(bookingId);
    return (it != bookings.end()) ? it->second : nullptr;
}

std::shared_ptr<Booking> HotelManagementSystem::makeBooking(int customerId, int roomNumber,
                                                           const Date& checkIn, const Date& checkOut, int guests) {
    auto customer = findCustomer(customerId);
    auto room = findRoom(roomNumber);

    if (!customer) {
        std::cout << "Error: Customer not found!" << std::endl;
        return nullptr;
    }

    if (!room) {
        std::cout << "Error: Room not found!" << std::endl;
        return nullptr;
    }

    if (!room->isAvailable()) {
        std::cout << "Error: Room is not available!" << std::endl;
        return nullptr;
    }

    if (guests > room->getCapacity()) {
        std::cout << "Error: Number of guests exceeds room capacity!" << std::endl;
        return nullptr;
    }

    int nights = checkIn.getDaysDifference(checkOut);
    if (nights <= 0) {
        std::cout << "Error: Invalid dates!" << std::endl;
        return nullptr;
    }

    double totalAmount = nights * room->getPricePerNight();

    auto booking = std::make_shared<Booking>(customerId, roomNumber, checkIn, checkOut, totalAmount, guests);
    bookings[booking->getBookingId()] = booking;

    room->setStatus(RoomStatus::RESERVED);

    std::cout << "Booking successful! Booking ID: " << booking->getBookingId() << std::endl;
    return booking;
}

bool HotelManagementSystem::checkIn(int bookingId) {
    auto booking = findBooking(bookingId);
    if (!booking) {
        std::cout << "Error: Booking not found!" << std::endl;
        return false;
    }

    if (booking->getStatus() != BookingStatus::CONFIRMED) {
        std::cout << "Error: Booking is not in confirmed status!" << std::endl;
        return false;
    }

    auto room = findRoom(booking->getRoomNumber());
    if (room) {
        room->setStatus(RoomStatus::OCCUPIED);
        booking->setStatus(BookingStatus::CHECKED_IN);
        std::cout << "Check-in successful for Booking ID: " << bookingId << std::endl;
        return true;
    }
    return false;
}

bool HotelManagementSystem::checkOut(int bookingId) {
    auto booking = findBooking(bookingId);
    if (!booking) {
        std::cout << "Error: Booking not found!" << std::endl;
        return false;
    }

    if (booking->getStatus() != BookingStatus::CHECKED_IN) {
        std::cout << "Error: Customer is not checked in!" << std::endl;
        return false;
    }

    auto room = findRoom(booking->getRoomNumber());
    if (room) {
        room->setStatus(RoomStatus::AVAILABLE);
        booking->setStatus(BookingStatus::CHECKED_OUT);
        
        auto bill = std::make_shared<Bill>(bookingId, booking->getTotalAmount());
        bills[bill->getBillId()] = bill;
        
        std::cout << "Check-out successful for Booking ID: " << bookingId << std::endl;
        std::cout << "Bill generated with Bill ID: " << bill->getBillId() << std::endl;
        bill->displayBill();
        return true;
    }
    return false;
}

void HotelManagementSystem::displayAvailableRooms() const {
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "                     AVAILABLE ROOMS" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    
    bool found = false;
    for (const auto& pair : rooms) {
        if (pair.second->isAvailable()) {
            pair.second->displayInfo();
            std::cout << std::string(80, '-') << std::endl;
            found = true;
        }
    }
    
    if (!found) {
        std::cout << "No rooms available at the moment." << std::endl;
    }
}

void HotelManagementSystem::displayAllBookings() const {
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "                      ALL BOOKINGS" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    
    if (bookings.empty()) {
        std::cout << "No bookings found." << std::endl;
        return;
    }

    for (const auto& pair : bookings) {
        pair.second->displayInfo();
        std::cout << std::string(80, '-') << std::endl;
    }
}

void HotelManagementSystem::displayAllCustomers() const {
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "                      ALL CUSTOMERS" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    
    if (customers.empty()) {
        std::cout << "No customers found." << std::endl;
        return;
    }

    for (const auto& pair : customers) {
        pair.second->displayInfo();
        std::cout << std::string(80, '-') << std::endl;
    }
}

void HotelManagementSystem::displayRoomsByType(RoomType type) const {
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "                      ROOMS BY TYPE" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    
    bool found = false;
    for (const auto& pair : rooms) {
        if (pair.second->getType() == type) {
            pair.second->displayInfo();
            std::cout << std::string(80, '-') << std::endl;
            found = true;
        }
    }
    
    if (!found) {
        std::cout << "No rooms found for the specified type." << std::endl;
    }
}

void HotelManagementSystem::searchCustomerByName(const std::string& name) const {
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "                 CUSTOMER SEARCH RESULTS" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    
    bool found = false;
    for (const auto& pair : customers) {
        if (pair.second->getName().find(name) != std::string::npos) {
            pair.second->displayInfo();
            std::cout << std::string(80, '-') << std::endl;
            found = true;
        }
    }
    
    if (!found) {
        std::cout << "No customers found with name containing: " << name << std::endl;
    }
}

void HotelManagementSystem::generateOccupancyReport() const {
    size_t totalRooms = rooms.size();
    int occupiedRooms = 0;
    int availableRooms = 0;
    int maintenanceRooms = 0;
    int reservedRooms = 0;

    for (const auto& pair : rooms) {
        switch (pair.second->getStatus()) {
            case RoomStatus::OCCUPIED: occupiedRooms++; break;
            case RoomStatus::AVAILABLE: availableRooms++; break;
            case RoomStatus::MAINTENANCE: maintenanceRooms++; break;
            case RoomStatus::RESERVED: reservedRooms++; break;
        }
    }

    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "                  OCCUPANCY REPORT" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    std::cout << "Total Rooms: " << totalRooms << std::endl;
    std::cout << "Occupied: " << occupiedRooms << " ("
              << std::fixed << std::setprecision(1)
              << (double)occupiedRooms/totalRooms*100 << "%)" << std::endl;
    std::cout << "Available: " << availableRooms << " ("
              << std::fixed << std::setprecision(1)
              << (double)availableRooms/totalRooms*100 << "%)" << std::endl;
    std::cout << "Reserved: " << reservedRooms << " ("
              << std::fixed << std::setprecision(1)
              << (double)reservedRooms/totalRooms*100 << "%)" << std::endl;
    std::cout << "Maintenance: " << maintenanceRooms << " ("
              << std::fixed << std::setprecision(1)
              << (double)maintenanceRooms/totalRooms*100 << "%)" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
}

void HotelManagementSystem::payBill(int billId) {
    auto it = bills.find(billId);
    if (it != bills.end()) {
        it->second->markAsPaid();
        std::cout << "Payment successful for Bill ID: " << billId << std::endl;
    } else {
        std::cout << "Error: Bill not found!" << std::endl;
    }
}

std::string HotelManagementSystem::getHotelName() const { return hotelName; }
