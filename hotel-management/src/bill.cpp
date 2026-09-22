#include "bill.h"
#include <iostream>
#include <iomanip>

// Definition of the static member variable must be in the .cpp file.
int Bill::nextBillId = 0;

Bill::Bill(int bId, double roomCh, double serviceCh)
    : billId(++nextBillId), bookingId(bId), roomCharges(roomCh),
      serviceCharges(serviceCh), isPaid(false), billDate() {
    calculateTotal();
}

void Bill::calculateTotal() {
    double subtotal = roomCharges + serviceCharges;
    tax = subtotal * 0.12; // 12% tax
    totalAmount = subtotal + tax;
}

int Bill::getBillId() const { return billId; }
int Bill::getBookingId() const { return bookingId; }
double Bill::getTotalAmount() const { return totalAmount; }
bool Bill::getIsPaid() const { return isPaid; }

void Bill::addServiceCharge(double charge) {
    serviceCharges += charge;
    calculateTotal();
}

void Bill::markAsPaid() { isPaid = true; }

void Bill::displayBill() const {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "              HOTEL BILL" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Bill ID: " << billId << std::endl;
    std::cout << "Booking ID: " << bookingId << std::endl;
    std::cout << "Date: " << billDate.toString() << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Room Charges:    $" << std::fixed << std::setprecision(2) << roomCharges << std::endl;
    std::cout << "Service Charges: $" << std::fixed << std::setprecision(2) << serviceCharges << std::endl;
    std::cout << "Tax (12%):       $" << std::fixed << std::setprecision(2) << tax << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Total Amount:    $" << std::fixed << std::setprecision(2) << totalAmount << std::endl;
    std::cout << "Status: " << (isPaid ? "PAID" : "UNPAID") << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}
