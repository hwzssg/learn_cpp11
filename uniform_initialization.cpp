#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <algorithm>


void print(std::initializer_list<int> vals)
{
    for(auto p = vals.begin(); p != vals.end(); ++p)
    {
        std::cout << *p << " ";
    }
    std::cout << std::endl;
}

class P
{
public:
    P(int a, int b)
    {
        std::cout << "P(int a, int b) called" << std::endl;
        std::cout << a << " " << b << std::endl;
    }

    P(std::initializer_list<int> vals)
    {
        std::cout << "P(std::initializer_list<int> vals) called" << std::endl;
        for (auto i : vals)
        {
            std::cout << i << std::endl;
        } 
    }
};

using namespace std;

int main(void)
{
    int value[] {1, 2, 3}; //initializer_list<T>
    std::cout << value[0] << std::endl;
    std::cout << value[1] << std::endl;
    std::cout << value[2] << std::endl;

    vector<int> v {1, 2, 3}; //initializer_list<T>
    vector<int> v1 = {1, 2, 3};
    vector<int> v2({1, 2, 3});
    vector<int> v3;
    v3 = {1, 2, 3};
    v3.insert(v3.begin() + 2, {4, 5, 6, 7});
    for (auto i : v3)
    {
        std::cout << i;
    }
    std::cout << std::endl;

    int i;
    int j{}; //zero
    int *p;
    int *q{}; //nullptr
    std::cout << "i = " << i << std::endl;
    std::cout << "j = " << j << std::endl;
    std::cout << "p = " << p << std::endl;
    std::cout << "q = " << q << std::endl;
    
    int x1(5.1);
    int x2 = 5.2;
    //int x3{5.3}; //error : narrowing 不允许窄化操作
    //int x4 = {5.4}; //error : narrowing 不允许窄化操作   
    print({1, 2, 3, 4, 5, 6});

    P p1(77, 5);
    P p2{77, 5};
    P p3{77, 5, 22};
    P p4 = {77, 5};

    std::cout << std::max({string("Ace"), string("Stacy"), string("Sabrina")}) << std::endl;


    return 0;
}