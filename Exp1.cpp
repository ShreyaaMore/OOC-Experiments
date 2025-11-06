#include <iostream>

using namespace std;

class Student {
private:
    char name[30];  
    int rollNo;
    float marks;

public:
   
    void inputDetails() {
        cout << "Enter student name: ";
        cin >> name;
        cout << "Enter roll number: ";
        cin >> rollNo;
        cout << "Enter marks: ";
        cin >> marks;
    }

    void displayDetails() {
        cout << "Student Name: " << name << endl;
        cout << "Roll Number: " << rollNo << endl;
        cout << "Marks: " << marks << endl;
    }
};

int main() {
    Student studentObj;

    studentObj.inputDetails();

    cout << "\nStudent Details:\n";
    studentObj.displayDetails();

    return 0;
}
