#include <iostream>
#include <exception>
#include <string>

using namespace std;

class InvalidAgeException : public exception
{
private:
    string message;

public:
    InvalidAgeException(int age)
    {
        message = "InvalidAgeException: Age value " + to_string(age) + " is outside the valid range (0-150).";
    }

    const char *what() const noexcept override
    {
        return message.c_str();
    }
};

class Person
{
private:
    int age;
    string name;

public:
    Person(const string &n) : name(n), age(0) {}

    void setAge(int a)
    {
        if (a < 0 || a > 150)
        {
            throw InvalidAgeException(a);
        }
        age = a;
        cout << name << "'s age set successfully to " << age << endl;
    }
};

int main()
{
    Person p("Alice");

    try
    {
        p.setAge(35);
        p.setAge(-5);
        p.setAge(200);
    }
    catch (const InvalidAgeException &e)
    {
        cerr << "Exception caught: " << e.what() << endl;
    }
    catch (const exception &e)
    {
        cerr << "Standard Exception caught: " << e.what() << endl;
    }

    return 0;
}