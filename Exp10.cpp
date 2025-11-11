#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.14159;

class Shape
{
public:
    virtual double calculateArea() const = 0;
    virtual double calculatePerimeter() const = 0;

    virtual ~Shape() {}
};

class Circle : public Shape
{
private:
    double radius;

public:
    Circle(double rad) : radius(rad) {}

    double calculateArea() const override
    {
        return PI * pow(radius, 2);
    }

    double calculatePerimeter() const override
    {
        return 2 * PI * radius;
    }
};

class Rectangle : public Shape
{
private:
    double length;
    double width;

public:
    Rectangle(double len, double wid) : length(len), width(wid) {}

    double calculateArea() const override
    {
        return length * width;
    }

    double calculatePerimeter() const override
    {
        return 2 * (length + width);
    }
};

class Triangle : public Shape
{
private:
    double side1, side2, side3;

public:
    Triangle(double s1, double s2, double s3) : side1(s1), side2(s2), side3(s3) {}

    double calculateArea() const override
    {
        double s = (side1 + side2 + side3) / 2.0;

        if (s <= side1 || s <= side2 || s <= side3)
            return 0.0;
        return sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }

    double calculatePerimeter() const override
    {
        return side1 + side2 + side3;
    }
};

int main()
{
    Shape *shapes[3];

    shapes[0] = new Circle(7.0);
    shapes[1] = new Rectangle(4.2, 8.0);
    shapes[2] = new Triangle(4.0, 4.0, 3.2);

    for (int i = 0; i < 3; ++i)
    {
        cout << "\nShape " << i + 1 << ":" << endl;
        cout << "Area: " << shapes[i]->calculateArea() << endl;
        cout << "Perimeter: " << shapes[i]->calculatePerimeter() << endl;
    }

    for (int i = 0; i < 3; ++i)
    {
        delete shapes[i];
    }

    return 0;
}