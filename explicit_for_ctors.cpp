#include <iostream>
#include <string>
using namespace std;


// before c++11 explicit for ctors taking one argument
//exp.
struct Complex
{
    int real, imag;

    Complex(int re, int im = 0) : real(re), imag(im) { }
    //explicit Complex(int re, int im = 0) : real(re), imag(im) { }

    Complex operator+(const Complex & x)
    {
        return Complex((real + x.real), (imag + x.imag));
    }
    void info()
    {
        std::cout << real << " " << imag << std::endl;
    }
};
//c++11 explicit for ctors taking more than one argument
class P
{
public:
    P(int a, int b)
    {
        std::cout << "P(int a, int b) called\n";
    }
    //P(initializer_list<int>)
    //{
     //   std::cout << "P(initializer_list<int> called\n";
    //}
    explicit P(int a, int b, int c)
    {
        std::cout << "explicit P(int a, int b, int c)\n";
    }
};

void fp(const P&) {}

int main(void)
{
    Complex c1(12, 5);
    Complex c2 = c1 + 5;
    c2.info();

    P p0(1, 2);
    P p1 {1, 2};
    P p2 = {1, 2};
    //P p3 = {1, 2, 3}; // error: converting to ‘P’ from initializer list would use explicit constructor ‘P::P(int, int, int)’
    P p4(1, 2, 3);

    //fp({1, 2, 3});
    fp({1, 2});

    return 0;
}