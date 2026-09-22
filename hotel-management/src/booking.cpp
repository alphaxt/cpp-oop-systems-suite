#include "booking.h"
#include <iostream>
#include <iomanip>

// Definition of the static member variable must be in the .cpp file.
int Booking::nextBookingId = 0;

Booking::Booking(int custId, int roomNum, const Date& checkIn,
                 const Date& checkOut, double amount, int guests)
    : bookingId(++nextBookingId), customerId(custId), roomNumber(roomNum),
      checkInDate(checkIn), checkOutDate(checkOut),
      status(BookingStatus::CONFIRMED), totalAmount(amount), numberOfGuests(guests) {}

int Booking::getBookingId() const { return bookingId; }
int Booking::getCustomerId() const { return customerId; }
int Booking::getRoomNumber() const { return roomNumber; }
Date Booking::getCheckInDate() const { return checkInDate; }
Date Booking::getCheckOutDate() const { return checkOutDate; }
BookingStatus Booking::getStatus() const { return status; }
double Booking::getTotalAmount() const { return totalAmount; }
int Booking::getNumberOfGuests() const { return numberOfGuests; }

void Booking::setStatus(BookingStatus s) { status = s; }
void Booking::setTotalAmount(double amount) { totalAmount = amount; }

std::string Booking::getStatusString() const {
    switch (status) {
        case BookingStatus::CONFIRMED: return "Confirmed";
        case BookingStatus::CHECKED_IN: return "Checked In";
        case BookingStatus::CHECKED_OUT: return "Checked Out";
        case BookingStatus::CANCELLED: return "Cancelled";
        default: return "Unknown";
    }
}

void Booking::displayInfo() const {
    std::cout << "Booking ID: " << bookingId << std::endl;
    std::cout << "Customer ID: " << customerId << std::endl;
    std::cout << "Room Number: " << roomNumber << std::endl;
    std::cout << "Check-in Date: " << checkInDate.toString() << std::endl;
    std::cout << "Check-out Date: " << checkOutDate.toString() << std::endl;
    std::cout << "Status: " << getStatusString() << std::endl;
    std::cout << "Number of Guests: " << numberOfGuests << std::endl;
    std::cout << "Total Amount: $" << std::fixed << std::setprecision(2) << totalAmount << std::endl;
}

int Booking::calculateNights() const {
    return checkInDate.getDaysDifference(checkOutDate);
}
