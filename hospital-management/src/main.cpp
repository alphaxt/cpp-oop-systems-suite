#include "Hospital.h"

int main() {
    Doctor* doctors[7];
    Patient patients[10];
    Appointment appointments[10];

    int doctorCount = 0, patientCount = 0, appointmentCount = 0;

    doctors[doctorCount++] = new Doctor("Dr. Muhammad Danish", 20, "General");
    doctors[doctorCount++] = new Doctor("Dr. Mansoor Ali", 21, "General");
    doctors[doctorCount++] = new DifferentDoctor("Dr. Ayesha Khan", 28, "Surgeon");
    doctors[doctorCount++] = new DifferentDoctor("Dr. Hamza Ali", 32, "Orthopedic");
    doctors[doctorCount++] = new DifferentDoctor("Dr. Atir Raza", 35, "Dermatologist");
    doctors[doctorCount++] = new SpecialistDoctor("Dr. Abdul Haseeb", 23, "Neurologist");
    doctors[doctorCount++] = new SpecialistDoctor("Dr. Khadija", 30, "Cardiologist");

    int choice;
    int patientID = 1;

    do {
        cout << "\n===== Hospital Appointment System =====\n";
        cout << "1. View Doctors\n";
        cout << "2. Add Patient\n";
        cout << "3. Book Appointment\n";
        cout << "4. Cancel Appointment\n";
        cout << "5. View Appointment History\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            for (int i = 0; i < doctorCount; i++)
                doctors[i]->display();
        }

        else if (choice == 2) {
            string name;
            int age;

            cout << "Enter patient name: ";
            cin.ignore();
            getline(cin, name);

            cout << "Enter age: ";
            cin >> age;

            patients[patientCount++] = Patient(patientID++, name, age);
            cout << "Patient added successfully.\n";
        }

        else if (choice == 3) {
            if (patientCount == 0) continue;

            for (int i = 0; i < patientCount; i++)
                cout << i << ". " << patients[i].getName() << endl;

            int pIndex;
            cin >> pIndex;

            for (int i = 0; i < doctorCount; i++) {
                cout << i << ". ";
                doctors[i]->display();
            }

            int dIndex;
            cin >> dIndex;

            if (!doctors[dIndex]->isAvailable()) continue;

            string date, time;
            cout << "Enter date: ";
            cin >> date;
            cout << "Enter time: ";
            cin >> time;

            appointments[appointmentCount++].setAppointment(
                patients[pIndex], doctors[dIndex], date, time);

            doctors[dIndex]->setAvailable(false);
            cout << "Appointment booked.\n";
        }

    } while (choice != 6);

    for (int i = 0; i < doctorCount; i++)
        delete doctors[i];

    cout << "System exited.\n";
    return 0;
}
