#ifndef ROOM_H
#define ROOM_H

#include "enums.h"
#include <string>
#include <vector>

class Room {
private:
    int roomNumber;
    RoomType type;
    RoomStatus status;
    double pricePerNight;
    int capacity;
    std::vector<std::string> amenities;

    void initializeAmenities();
    std::string getTypeString() const;
    std::string getStatusString() const;

public:
    Room(int number, RoomType t, double price, int cap);

    int getRoomNumber() const;
    RoomType getType() const;
    RoomStatus getStatus() const;
    double getPricePerNight() const;
    int getCapacity() const;
    std::vector<std::string> getAmenities() const;

    void setStatus(RoomStatus s);
    void setPricePerNight(double price);

    void displayInfo() const;
    bool isAvailable() const;
};

#endif // ROOM_H