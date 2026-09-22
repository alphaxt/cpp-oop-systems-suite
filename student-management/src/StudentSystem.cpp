#include "StudentSystem.h"
#include <iostream>
#include <algorithm>

using namespace std; 

StudentSystem::StudentSystem() {
    head = nullptr;
}

void StudentSystem::addStudent(int roll, string name, float cgpa, string dept, int sem, string contact) {
    Student s(roll, name, cgpa, dept, sem, contact);
    Node* newNode = new Node(s);

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    cout << "\nStudent Added Successfully!\n";
}

void StudentSystem::displayStudents() {
    if (head == nullptr) {
        cout << "\nNo Students Found!\n";
        return;
    }

    Node* temp = head;
    cout << "\n===== STUDENT RECORDS =====\n\n";

    while (temp != nullptr) {
        cout << "Roll No    : " << temp->data.rollNo << endl;
        cout << "Name       : " << temp->data.name << endl;
        cout << "Department : " << temp->data.department << endl;
        cout << "Semester   : " << temp->data.semester << endl;
        cout << "CGPA       : " << temp->data.cgpa << endl;
        cout << "Contact    : " << temp->data.contactNo << endl;
        cout << "--------------------------\n";
        temp = temp->next;
    }
}

void StudentSystem::searchStudent(int roll) {
    if (head == nullptr) {
        cout << "\nList is Empty!\n";
        return;
    }
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data.rollNo == roll) {
            cout << "\nStudent Found!\n";
            cout << "Roll No    : " << temp->data.rollNo << endl;
            cout << "Name       : " << temp->data.name << endl;
            cout << "Department : " << temp->data.department << endl;
            cout << "Semester   : " << temp->data.semester << endl;
            cout << "CGPA       : " << temp->data.cgpa << endl;
            cout << "Contact    : " << temp->data.contactNo << endl;
            cout << "-------------------------\n";
            return; 
        }
        temp = temp->next;
    }
    cout << "\nStudent Not Found!\n";
}

void StudentSystem::deleteStudent(int roll) {
    if (head == nullptr) {
        cout << "\nList is Empty!\n";
        return;
    }
    if (head->data.rollNo == roll) {
        deletedStack.push(head->data);
        Node* temp = head;
        head = head->next;
        delete temp;
        cout << "\nStudent Deleted!\n";
        return;
    }

    Node* current = head;
    while (current->next != nullptr && current->next->data.rollNo != roll) {
        current = current->next;
    }

    if (current->next == nullptr) {
        cout << "\nStudent Not Found!\n";
        return;
    }

    deletedStack.push(current->next->data);
    Node* temp = current->next;
    current->next = temp->next;
    delete temp;
    cout << "\nStudent Deleted Successfully!\n";
}

void StudentSystem::undoDelete() {
    if (deletedStack.empty()) {
        cout << "\nNo Deleted Student Found!\n";
        return;
    }
    Student s = deletedStack.top();
    deletedStack.pop();
    addStudent(s.rollNo, s.name, s.cgpa, s.department, s.semester, s.contactNo);
    cout << "\nDeleted Student Restored!\n";
}

void StudentSystem::addToQueue(int roll, string name, float cgpa, string dept, int sem, string contact) {
    Student s(roll, name, cgpa, dept, sem, contact);
    registrationQueue.push(s);
    cout << "\nStudent Added To Registration Queue!\n";
}

void StudentSystem::processQueue() {
    if (registrationQueue.empty()) {
        cout << "\nQueue is Empty!\n";
        return;
    }
    Student s = registrationQueue.front();
    registrationQueue.pop();
    addStudent(s.rollNo, s.name, s.cgpa, s.department, s.semester, s.contactNo);
    cout << "\nRegistration Processed!\n";
}

void StudentSystem::sortStudents() {
    vector<Student> students;
    Node* temp = head;
    while (temp != nullptr) {
        students.push_back(temp->data);
        temp = temp->next;
    }

    for (size_t i = 0; i < students.size() - 1; i++) {
        for (size_t j = 0; j < students.size() - i - 1; j++) {
            if (students[j].rollNo > students[j + 1].rollNo) {
                swap(students[j], students[j + 1]);
            }
        }
    }

    cout << "\n===== SORTED STUDENTS =====\n\n";
    for (size_t i = 0; i < students.size(); i++) {
        cout << "Roll No    : " << students[i].rollNo << endl;
        cout << "Name       : " << students[i].name << endl;
        cout << "Department : " << students[i].department << endl;
        cout << "Semester   : " << students[i].semester << endl;
        cout << "CGPA       : " << students[i].cgpa << endl;
        cout << "Contact    : " << students[i].contactNo << endl;
        cout << "--------------------------\n";
    }
}
