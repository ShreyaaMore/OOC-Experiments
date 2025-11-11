#include <iostream>

using namespace std;

class Construct
{
public:
    float area;

    Construct()
    {
        area = 0;
    }

    Construct(int a, int b)
    {
        area = a * b;
    }

    void disp()
    {
        cout << area << endl;
    }
};

int main(){
    Construct o;
    Construct o2(5, 10);

    cout << "Area of object o: ";
    o.disp();
    cout << "Area of object o2: ";
    o2.disp();

    cout << "\nEnd of main function. Destructors called now." << endl;

}