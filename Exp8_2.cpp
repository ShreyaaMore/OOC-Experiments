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
    cout << "Initial Distance: " << d1.feet << "' " << d1.inch << "''";
    -d1;

    return 0;
}
