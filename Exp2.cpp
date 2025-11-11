#include <iostream>

using namespace std;

class Complex {
    public:
        int real;      
        int imaginary; 

        Complex() {
            real = 0;
            imaginary = 0;
        }

        Complex(int r, int i) {
            real = r;
            imaginary = i;
        }

        Complex addComplexNumber(Complex C1, Complex C2) {
            Complex res; 
            res.real = C1.real + C2.real;
            res.imaginary = C1.imaginary + C2.imaginary;
            return res;
        }

        Complex subtractComplexNumber(Complex C1, Complex C2) {
            Complex res; 
            res.real = C1.real - C2.real;
            res.imaginary = C1.imaginary - C2.imaginary;
            return res;
        }
        
        void display() const {
            cout << real << " + i" << imaginary;
        }
};

int main() {
    
    Complex C1(4, 5);
    Complex C2(8, 9);
    Complex C_sum;

    cout << "Complex number 1 : "; C1.display(); cout << endl;
    cout << "Complex number 2 : "; C2.display(); cout << endl;

    C_sum = C_sum.addComplexNumber(C1, C2);

    cout << "Sum of complex numbers : ";
    C_sum.display();
    cout << endl << endl;
    
    Complex C4(15, 12);
    Complex C5(5, 7);
    Complex C_diff;
    
    cout << "Complex number 4 : "; C4.display(); cout << endl;
    cout << "Complex number 5 : "; C5.display(); cout << endl;
    
    C_diff = C_diff.subtractComplexNumber(C4, C5);
    
    cout << "Difference (C4 - C5) : ";
    C_diff.display();
    cout << endl;

    return 0;
}