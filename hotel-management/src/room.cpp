#include "room.h"
#include <iostream>
#include <iomanip>

Room::Room(int number, RoomType t, double price, int cap)
    : roomNumber(number), type(t), status(RoomStatus::AVAILABLE),
      pricePerNight(price), capacity(cap) {
    initializeAmenities();
}

void Room::initializeAmenities() {
    switch (type) {
        case RoomType::SINGLE:
            amenities = {"WiFi", "TV", "AC"};
            break;
        case RoomType::DOUBLE:
            amenities = {"WiFi", "TV", "AC", "Mini Bar"};
            break;
        case RoomType::DELUXE:
            amenities = {"WiFi", "TV", "AC", "Mini Bar", "Balcony", "Room Service"};
            break;
        case RoomType::SUITE:
            amenities = {"WiFi", "TV", "AC", "Mini Bar", "Balcony", "Room Service", "Jacuzzi", "Kitchen"};
            break;
    }
}

int Room::getRoomNumber() const { return roomNumber; }
RoomType Room::getType() const { return type; }
RoomStatus Room::getStatus() const { return status; }
double Room::getPricePerNight() const { return pricePerNight; }
int Room::getCapacity() const { return capacity; }
std::vector<std::string> Room::getAmenities() const { return amenities; }

void Room::setStatus(RoomStatus s) { status = s; }
void Room::setPricePerNight(double price) { pricePerNight = price; }

std::string Room::getTypeString() const {
    switch (type) {
        case RoomType::SINGLE: return "Single";
        case RoomType::DOUBLE: return "Double";
        case RoomType::DELUXE: return "Deluxe";
        case RoomType::SUITE: return "Suite";
        default: return "Unknown";
    }
}

std::string Room::getStatusString() const {
    switch (status) {
        case RoomStatus::AVAILABLE: return "Available";
        case RoomStatus::OCCUPIED: return "Occupied";
        case RoomStatus::MAINTENANCE: return "Maintenance";
        case RoomStatus::RESERVED: return "Reserved";
        default: return "Unknown";
    }
}

void Room::displayInfo() const {
    std::cout << "Room Number: " << roomNumber << std::endl;
    std::cout << "Type: " << getTypeString() << std::endl;
    std::cout << "Status: " << getStatusString() << std::endl;
    std::cout << "Price per Night: $" << std::fixed << std::setprecision(2) << pricePerNight << std::endl;
    std::cout << "Capacity: " << capacity << " guests" << std::endl;
    std::cout << "Amenities: ";
    for (size_t i = 0; i < amenities.size(); ++i) {
        std::cout << amenities[i];
        if (i < amenities.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
}

bool Room::isAvailable() const {
    return status == RoomStatus::AVAILABLE;
}