#include "person.h"
#include <iostream>

// Definition of the static member variable must be in the .cpp file.
int Person::nextId = 0;

Person::Person(const std::string& n, const std::string& p, const std::string& e)
    : name(n), phone(p), email(e), id(++nextId) {}

int Person::getId() const { return id; }
std::string Person::getName() const { return name; }
std::string Person::getPhone() const { return phone; }
std::string Person::getEmail() const { return email; }

void Person::setName(const std::string& n) { name = n; }
void Person::setPhone(const std::string& p) { phone = p; }
void Person::setEmail(const std::string& e) { email = e; }

Customer::Customer(const std::string& name, const std::string& phone,
                   const std::string& email, const std::string& addr,
                   const std::string& proof)
    : Person(name, phone, email), address(addr), idProof(proof) {}

std::string Customer::getAddress() const { return address; }
std::string Customer::getIdProof() const { return idProof; }

void Customer::setAddress(const std::string& addr) { address = addr; }
void Customer::setIdProof(const std::string& proof) { idProof = proof; }

void Customer::displayInfo() const {
    std::cout << "Customer ID: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Phone: " << phone << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Address: " << address << std::endl;
    std::cout << "ID Proof: " << idProof << std::endl;
}
