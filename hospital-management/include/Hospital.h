#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <iostream>
#include <string>

using namespace std;

/* ================= BASE CLASS ================= */
class Person {
protected:
    string name;
    int age;

public:
    Person(string name = "", int age = 0);
    string getName();
};

/* ================= DOCTOR CLASS ================= */
class Doctor : public Person {
protected:
    string specialization;
    bool available;

public:
    Doctor(string name = "", int age = 0, string specialization = "");
    virtual ~Doctor() = default;
    virtual int consultationFee();
    bool isAvailable();
    void setAvailable(bool status);
    virtual void display();
};

/* ================= SPECIALIST DOCTORS ================= */
class SpecialistDoctor : public Doctor {
public:
    SpecialistDoctor(string name = "", int age = 0, string specialization = "");
    int consultationFee() override;
};

class DifferentDoctor : public Doctor {
public:
    DifferentDoctor(string name = "", int age = 0, string specialization = "");
    int consultationFee() override;
};

/* ================= PATIENT CLASS ================= */
class Patient : public Person {
private:
    int patientID;

public:
    Patient(int patientID = 0, string name = "", int age = 0);
    int getID();
};

/* ================= APPOINTMENT CLASS ================= */
class Appointment {
private:
    Patient patient;
    Doctor* doctor;
    string date;
    string time;

public:
    Appointment();
    void setAppointment(Patient p, Doctor* d, string dt, string tm);
    void show();
    Doctor* getDoctor();
};

#endif

