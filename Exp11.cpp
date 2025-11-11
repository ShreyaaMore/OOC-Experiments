#include <iostream>
#include <string>

using namespace std;


class Employee {
private:
    int no;
    string name;

public:
    
    virtual void inputData() = 0; 
    virtual void displaySalary() const = 0; 

    
    void inputBaseData() {
        cout << "Enter employee number: ";
        cin >> no;
        cout << "Enter employee name: ";
        cin.ignore(); 
        getline(cin, name);
    }
    
    void displayBaseData() const {
        cout << "Employee Number is " << no << endl;
        cout << "Employee Name is " << name << endl;
    }
    
    
    virtual ~Employee() {}
};


class SalariedEmployee : public Employee {
private:
    double monthlySalary;

public:
    void inputData() override {
        cout << "\n[Salaried Employee]" << endl;
        inputBaseData();
        cout << "Enter employee monthly salary: ";
        cin >> monthlySalary;
    }

    void displaySalary() const override {
        cout << "\n[Salaried Employee]" << endl;
        displayBaseData();
        cout << "Final Salary: Rs." << monthlySalary << endl;
    }
};


class HourlyEmployee : public Employee {
private:
    double hours;
    double rate;

public:
    void inputData() override {
        cout << "\n[Hourly Employee]" << endl;
        inputBaseData();
        cout << "Enter hours worked: ";
        cin >> hours;
        cout << "Enter hourly rate: ";
        cin >> rate;
    }

    void displaySalary() const override {
        double totalSalary = rate * hours;
        cout << "\n[Hourly Employee]" << endl;
        displayBaseData();
        cout << "Hours: " << hours << endl;
        cout << "Hourly rate: " << rate << endl;
        cout << "Final Salary: Rs." << totalSalary << endl;
    }
};


class CommissionedEmployee : public Employee {
private:
    double baseSalary; 
    int overtime; 

public:
    void inputData() override {
        cout << "\n[Commissioned Employee]" << endl;
        inputBaseData();
        cout << "Enter base salary: ";
        cin >> baseSalary;
        cout << "Enter overtime hours: ";
        cin >> overtime;
    }

    void displaySalary() const override {
        
        double totalSalary = baseSalary + (overtime * 15.0); 
        cout << "\n[Commissioned Employee]" << endl;
        displayBaseData();
        cout << "Base Salary: Rs." << baseSalary << endl;
        cout << "Overtime Factor: " << overtime << endl;
        cout << "Final Salary (Base + Overtime): Rs." << totalSalary << endl;
    }
};


int main() {
    Employee* employees[3];

    employees[0] = new SalariedEmployee();
    employees[1] = new HourlyEmployee();
    employees[2] = new CommissionedEmployee();

    for (int i = 0; i < 3; i++) {
        employees[i]->inputData(); 
        cout << endl;
    }

    for (int i = 0; i < 3; i++) {
        employees[i]->displaySalary(); 
    }

    for (int i = 0; i < 3; i++) {
        delete employees[i];
    }

    return 0;
}