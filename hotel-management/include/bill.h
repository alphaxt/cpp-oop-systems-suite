#ifndef BILL_H
#define BILL_H

#include "date.h"
#include <string>

class Bill {
    friend class HotelManagementSystem;
private:
    static int nextBillId;
    int billId;
    int bookingId;
    double roomCharges;
    double serviceCharges;
    double tax;
    double totalAmount;
    bool isPaid;
    Date billDate;

    void calculateTotal();

public:
    Bill(int bId, double roomCh, double serviceCh = 0.0);

    int getBillId() const;
    int getBookingId() const;
    double getTotalAmount() const;
    bool getIsPaid() const;

    void addServiceCharge(double charge);
    void markAsPaid();

    void displayBill() const;
};

#endif // BILL_H
