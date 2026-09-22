#include "Hospital.h"

/* ================= PERSON ================= */
Person::Person(string name, int age) {
    this->name = name;
    this->age = age;
}

string Person::getName() {
    return name;
}

/* ============== DOCTOR =============== */
Doctor::Doctor(string name, int age, string specialization)
    : Person(name, age) {
    this->specialization = specialization;
    available = true;
}

int Doctor::consultationFee() {
    return 1000;
}

bool Doctor::isAvailable() {
    return available;
}

void Doctor::setAvailable(bool status) {
    available = status;
}

void Doctor::display() {
    cout << "Doctor: " << name
        << " | Specialization: " << specialization
        << " | Fee: " << consultationFee()
        << " | Status: " << (available ? "Available" : "Busy") << endl;
}

/* ============== SPECIALIST DOCTORS ============= */
SpecialistDoctor::SpecialistDoctor(string name, int age, string specialization)
    : Doctor(name, age, specialization) {
}

int SpecialistDoctor::consultationFee() {
    return 2500;
}

// another doctor type

DifferentDoctor::DifferentDoctor(string name, int age, string specialization)
    : Doctor(name, age, specialization) {
}

int DifferentDoctor::consultationFee() {
    return 5000;
}

/* ================= PATIENT ================= */
Patient::Patient(int patientID, string name, int age)
    : Person(name, age) {
    this->patientID = patientID;
}

int Patient::getID() {
    return patientID;
}

/* ============= APPOINTMENT ============= */
Appointment::Appointment() {
    doctor = nullptr;
}

void Appointment::setAppointment(Patient p, Doctor* d, string dt, string tm) {
    patient = p;
    doctor = d;
    date = dt;
    time = tm;
}

void Appointment::show() {
    if (doctor != nullptr) {
        cout << "Patient: " << patient.getName()
            << " | Doctor: " << doctor->getName()
            << " | Date: " << date
            << " | Time: " << time
            << " | Fee: " << doctor->consultationFee()
            << endl;
    }
}

Doctor* Appointment::getDoctor() {
    return doctor;
}
