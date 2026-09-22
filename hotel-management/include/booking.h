#ifndef BOOKING_H
#define BOOKING_H

#include "enums.h"
#include "date.h"

class Booking {
    friend class HotelManagementSystem;
private:
    static int nextBookingId;
    int bookingId;
    int customerId;
    int roomNumber;
    Date checkInDate;
    Date checkOutDate;
    BookingStatus status;
    double totalAmount;
    int numberOfGuests;
    
public:
    Booking(int custId, int roomNum, const Date& checkIn,
            const Date& checkOut, double amount, int guests);

    int getBookingId() const;
    int getCustomerId() const;
    int getRoomNumber() const;
    Date getCheckInDate() const;
    Date getCheckOutDate() const;
    BookingStatus getStatus() const;
    double getTotalAmount() const;
    int getNumberOfGuests() const;

    void setStatus(BookingStatus s);
    void setTotalAmount(double amount);

    std::string getStatusString() const;
    void displayInfo() const;
    int calculateNights() const;
};

#endif // BOOKING_H
