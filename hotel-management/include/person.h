#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

class Person {
    friend class HotelManagementSystem;
protected:
    std::string name;
    std::string phone;
    std::string email;
    static int nextId;
    int id;

public:
    Person(const std::string& n, const std::string& p, const std::string& e);
    virtual ~Person() = default;

    int getId() const;
    std::string getName() const;
    std::string getPhone() const;
    std::string getEmail() const;

    void setName(const std::string& n);
    void setPhone(const std::string& p);
    void setEmail(const std::string& e);

    virtual void displayInfo() const = 0;
};

class Customer : public Person {
private:
    std::string address;
    std::string idProof;

public:
    Customer(const std::string& name, const std::string& phone,
             const std::string& email, const std::string& addr,
             const std::string& proof);

    std::string getAddress() const;
    std::string getIdProof() const;

    void setAddress(const std::string& addr);
    void setIdProof(const std::string& proof);

    void displayInfo() const override;
};

#endif // PERSON_H
