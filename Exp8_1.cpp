#include <iostream>

using namespace std;

class Distance
{
public:
    int feet, inch;

    Distance() : feet(0), inch(0) {}

    Distance(int f, int i) : feet(f), inch(i) {}

    void operator-()
    {
        feet--;
        inch--;
        cout << "\nFeet & Inches: " << feet << "' " << inch << "''" << endl;
    }

    Distance operator+(const Distance &d2) const
    {

        Distance d3;
        d3.feet = this->feet + d2.feet;
        d3.inch = this->inch + d2.inch;

        if (d3.inch >= 12)
        {
            d3.feet += d3.inch / 12;
            d3.inch %= 12;
        }

        return d3;
    }
};

int main()
{
    Distance d1(8, 9);
    Distance d2(10, 5);
    Distance d3;

    cout << "Distance 1: " << d1.feet << "' " << d1.inch << "''" << endl;
    cout << "Distance 2: " << d2.feet << "' " << d2.inch << "''" << endl;

    d3 = d1 + d2;

    cout << "Total Distance (D1 + D2): " << d3.feet << "' " << d3.inch << "''" << endl;

    return 0;
}
