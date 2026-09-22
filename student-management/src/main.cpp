#include <iostream>
#include <string>
#include "StudentSystem.h" 

using namespace std;

int main() {
    StudentSystem system;
    int choice;

    do {
        cout << "\n========== STUDENT MANAGEMENT SYSTEM ==========\n";
        cout << "\n1. Add Student";
        cout << "\n2. Display Students";
        cout << "\n3. Search Student";
        cout << "\n4. Delete Student";
        cout << "\n5. Undo Delete";
        cout << "\n6. Add Student To Registration Queue";
        cout << "\n7. Process Registration Queue";
        cout << "\n8. Sort Students";
        cout << "\n9. Exit";
        cout << "\n\nEnter Choice : ";

        cin >> choice;

        if (choice == 1) {
            int roll, sem;
            string name, dept, contact;
            float cgpa;

            cout << "\nEnter Roll No : ";
            cin >> roll;
            cin.ignore();

            cout << "Enter Name : ";
            getline(cin, name);

            cout << "Enter CGPA : ";
            cin >> cgpa;
            cin.ignore();

            cout << "Enter Department : ";
            getline(cin, dept);

            cout << "Enter Semester : ";
            cin >> sem;
            cin.ignore();

            cout << "Enter Contact No : ";
            getline(cin, contact);

            system.addStudent(roll, name, cgpa, dept, sem, contact);
        }
        else if (choice == 2) {
            system.displayStudents();
        }
        else if (choice == 3) {
            int roll;
            cout << "\nEnter Roll No To Search : ";
            cin >> roll;
            system.searchStudent(roll);
        }
        else if (choice == 4) {
            int roll;
            cout << "\nEnter Roll No To Delete : ";
            cin >> roll;
            system.deleteStudent(roll);
        }
        else if (choice == 5) {
            system.undoDelete();
        }
        else if (choice == 6) {
            int roll, sem;
            string name, dept, contact;
            float cgpa;

            cout << "\nEnter Roll No : ";
            cin >> roll;
            cin.ignore();

            cout << "Enter Name : ";
            getline(cin, name);

            cout << "Enter CGPA : ";
            cin >> cgpa;
            cin.ignore();

            cout << "Enter Department : ";
            getline(cin, dept);

            cout << "Enter Semester : ";
            cin >> sem;
            cin.ignore();

            cout << "Enter Contact No : ";
            getline(cin, contact);

            system.addToQueue(roll, name, cgpa, dept, sem, contact);
        }
        else if (choice == 7) {
            system.processQueue();
        }
        else if (choice == 8) {
            system.sortStudents();
        }
        else if (choice == 9) {
            cout << "\nProgram Ended!\n";
        }
        else {
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 9);

    return 0;
}
