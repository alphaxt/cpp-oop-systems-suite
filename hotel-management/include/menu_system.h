#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H

#include "hotel_management.h"
#include <memory>
#include <string>

class MenuSystem {
private:
    std::shared_ptr<HotelManagementSystem> hotel;

    void clearScreen() const;
    void pause() const;
    int getIntInput(const std::string& prompt) const;
    double getDoubleInput(const std::string& prompt) const;
    std::string getStringInput(const std::string& prompt) const;
    Date getDateInput(const std::string& prompt) const;
    void addNewCustomer();
    void searchCustomer();
    void addNewBooking();
    void handleCheckIn();
    void handleCheckOut();
    void handleRoomTypeSearch();
    void handlePayBill();

public:
    MenuSystem(std::shared_ptr<HotelManagementSystem> h);
    void displayWelcome() const;
    void displayMainMenu() const;
    void customerMenu();
    void roomMenu();
    void bookingMenu();
    void reportsMenu();
    void billingMenu();
    void run();
};

#endif // MENU_SYSTEM_H