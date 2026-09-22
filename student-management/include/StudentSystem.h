#pragma once
#include "Student.h" 
#include <stack>
#include <queue>
#include <vector>

using namespace std;

class StudentSystem {
private:
    Node* head;
    stack<Student> deletedStack;
    queue<Student> registrationQueue;

public:
    StudentSystem(); 

    void addStudent(int roll, string name, float cgpa, string dept, int sem, string contact);
    void displayStudents();
    void searchStudent(int roll);
    void deleteStudent(int roll);
    void undoDelete();
    void addToQueue(int roll, string name, float cgpa, string dept, int sem, string contact);
    void processQueue();
    void sortStudents();
};
