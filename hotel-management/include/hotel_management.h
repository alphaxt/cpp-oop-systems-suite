#ifndef HOTEL_MANAGEMENT_H
#define HOTEL_MANAGEMENT_H

#include "date.h"
#include "enums.h"
#include "person.h"
#include "room.h"
#include "booking.h"
#include "bill.h"
#include <string>
#include <map>
#include <memory>
#include <iostream>

// Helper functions for data persistence
int roomTypeToInt(RoomType type);
RoomType intToRoomType(int type);
int roomStatusToInt(RoomStatus status);
RoomStatus intToRoomStatus(int status);
int bookingStatusToInt(BookingStatus status);
BookingStatus intToBookingStatus(int status);

class IHotelOperations {
public:
    virtual ~IHotelOperations() = default;
    virtual bool addCustomer(std::shared_ptr<Customer> customer) = 0;
    virtual bool addRoom(std::shared_ptr<Room> room) = 0;
    virtual std::shared_ptr<Booking> makeBooking(int customerId, int roomNumber,
                                                 const Date& checkIn, const Date& checkOut, int guests) = 0;
    virtual bool checkIn(int bookingId) = 0;
    virtual bool checkOut(int bookingId) = 0;
    virtual void displayAvailableRooms() const = 0;
    virtual void displayAllBookings() const = 0;
};

class HotelManagementSystem : public IHotelOperations {
private:
    std::string hotelName;
    std::map<int, std::shared_ptr<Customer>> customers;
    std::map<int, std::shared_ptr<Room>> rooms;
    std::map<int, std::shared_ptr<Booking>> bookings;
    std::map<int, std::shared_ptr<Bill>> bills;

    // Private methods for data persistence
    bool saveCustomersToFile() const;
    bool loadCustomersFromFile();
    bool saveRoomsToFile() const;
    bool loadRoomsFromFile();
    bool saveBookingsToFile() const;
    bool loadBookingsFromFile();
    bool saveBillsToFile() const;
    bool loadBillsFromFile();

    double getRoomPrice(RoomType type) const;
    void initializeRooms();
    std::shared_ptr<Customer> findCustomer(int customerId) const;
    std::shared_ptr<Room> findRoom(int roomNumber) const;
    std::shared_ptr<Booking> findBooking(int bookingId) const;

public:
    HotelManagementSystem(const std::string& name);
    
    // Public methods to manage data
    bool saveData();
    bool loadData();

    bool addCustomer(std::shared_ptr<Customer> customer) override;
    bool addRoom(std::shared_ptr<Room> room) override;
    std::shared_ptr<Booking> makeBooking(int customerId, int roomNumber,
                                         const Date& checkIn, const Date& checkOut, int guests) override;
    bool checkIn(int bookingId) override;
    bool checkOut(int bookingId) override;
    void displayAvailableRooms() const override;
    void displayAllBookings() const override;

    void displayAllCustomers() const;
    void displayRoomsByType(RoomType type) const;
    void searchCustomerByName(const std::string& name) const;
    void generateOccupancyReport() const;
    void payBill(int billId);

    std::string getHotelName() const;
};

#endif // HOTEL_MANAGEMENT_H
