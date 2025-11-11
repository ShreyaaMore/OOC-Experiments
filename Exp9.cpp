#include <iostream>

using namespace std;

class Complex
{
private:
    int real, imag;

public:
    Complex(int r = 0, int i = 0) : real(r), imag(i) {}

    friend ostream &operator<<(ostream &out, const Complex &c);
    friend istream &operator>>(istream &in, Complex &c);
};

ostream &operator<<(ostream &out, const Complex &c)
{
    out << c.real;

    if (c.imag >= 0)
    {
        out << "+i" << c.imag;
    }
    else
    {
        out << "-i" << -c.imag;
    }
    return out;
}

istream &operator>>(istream &in, Complex &c)
{
    cout << "Enter Real Part: ";
    in >> c.real;
    cout << "Enter Imaginary Part: ";
    in >> c.imag;
    return in;
}

int main()
{
    Complex c1;
    
    cin >> c1;
    cout << "\nThe complex object is: ";
    cout << c1 << endl;

    return 0;
}