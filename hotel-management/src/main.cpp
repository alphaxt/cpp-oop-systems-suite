#include "hotel_management.h"
#include "menu_system.h"
#include <iostream>
#include <memory>

int main() {
    // Create a shared pointer to the HotelManagementSystem instance
    std::shared_ptr<HotelManagementSystem> hotel =
        std::make_shared<HotelManagementSystem>("The Grand Hotel");

    // Load data from files at the start of the program
    hotel->loadData();

    // Create a MenuSystem instance and pass the hotel object to it
    MenuSystem menu(hotel);

    // Start the menu loop
    menu.run();

    // Save data to files before exiting the program
    hotel->saveData();

    return 0;
}
