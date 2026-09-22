#pragma once 
#include <string>

using namespace std; 

// ================= STUDENT CLASS =================
class Student {
public:
    int rollNo;
    string name;
    float cgpa;

    string department;
    int semester;
    string contactNo;

    Student() {}

    Student(int r, string n, float c, string dept, int sem, string contact) {
        rollNo = r;
        name = n;
        cgpa = c;
        department = dept;
        semester = sem;
        contactNo = contact;
    }
};

// ================= LINKED LIST NODE =================
class Node {
public:
    Student data;
    Node* next;

    Node(Student s) {
        data = s;
        next = nullptr; 
    }
};
