#include <iostream>

using namespace std;

int area(int s);           
int area(int l, int b);    
float area(float r);       
float area(float bs, float ht); 

int area(int s) {
    return (s * s);
}

int area(int l, int b) {
    return (l * b);
}

float area(float r) {
    return (3.14 * r * r);
}

float area(float bs, float ht) {
    return ((bs * ht) / 2.0); 
}


int main() {
    int s, l, b;
    float r, bs, ht;

    cout << "Enter side of a square: ";
    cin >> s;
    cout << "Enter length and breadth of rectangle: ";
    cin >> l >> b;
    cout << "Enter radius of circle: ";
    cin >> r;
    cout << "Enter base and height of triangle: ";
    cin >> bs >> ht;

    cout << "\n--- Results ---" << endl;
    
    cout << "Area of square is " << area(s) << endl;
    cout << "Area of rectangle is " << area(l, b) << endl;
    cout << "Area of circle is " << area(r) << endl;
    cout << "Area of triangle is " << area(bs, ht) << endl;

    return 0;
}