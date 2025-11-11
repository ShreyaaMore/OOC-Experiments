#include <iostream>
#include <exception>
#include <string>

using namespace std;

double safe_division(int a, int b)
{
    if (b == 0)
    {
        throw "Division by zero condition!";
    }
    return (double)a / b;
}

int main()
{

    int x = 50;
    int y = 0;
    double z = 0;

    try
    {
        z = safe_division(x, y);
        cout << "Result: " << z << endl;
    }
    catch (const char *msg)
    {
        cerr << "Exception caught: " << msg << endl;
    }

    return 0;
}