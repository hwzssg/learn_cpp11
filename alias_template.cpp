#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <time.h>

#include <chrono>

//Alais Template (template typedef)

using namespace std;


// template<typename Container, typename T>
// void test_moveable(Container cntr, T elem)
// {
//     typename Container<T> c; //error: expected nested-name-specifier before ‘Container’
//     for (long i = 0; i < 102400u; ++i)
//     {
//         c.insert(c.end(), T());
//     }
//     Container<T> c1(c);
//     Container<T> c2(std::move(c));
//     c1.swap(c2);
// }

template<typename T>
void output_static_data(const T&obj)
{
    std::cout << obj << std::endl; 
}

//use function template + iterator + traits
template<typename Container>
void test_moveable(Container c)
{
    typedef typename iterator_traits<typename Container::iterator>::value_type ValType; 
    for (long i = 0; i < 1024; ++i)
    {
        c.insert(c.end(), ValType(1));
    }
    output_static_data(*(c.begin()));
    Container c1(c);
    Container c2(std::move(c));
    c1.swap(c2);
}

//template template paramter 模板模板参数
template<typename T, template<class> class Container>
//template<typename T, template<class T> class Container>
class XCls
{
private:
    Container<T> c;
public:
    XCls()
    {
        for(long i = 0; i < 10240000; ++i)
        {
            c.insert(c.end(), T());
        }

        output_static_data(T());
        std::cout << typeid(c).name() << std::endl;
        std::chrono::time_point<std::chrono::high_resolution_clock> p0 = std::chrono::high_resolution_clock::now();
        Container<T> c1(c);
        std::chrono::time_point<std::chrono::high_resolution_clock> p1 = std::chrono::high_resolution_clock::now();
        cout << "stitch high_resolution_clock time:" << (float)std::chrono::duration_cast<std::chrono::microseconds>(p1 - p0).count() / 1000 << "ms" << endl;

        std::chrono::time_point<std::chrono::high_resolution_clock> p2 = std::chrono::high_resolution_clock::now();
        Container<T> c2(std::move(c));
        std::chrono::time_point<std::chrono::high_resolution_clock> p3 = std::chrono::high_resolution_clock::now();
        cout << "stitch high_resolution_clock time:" << (float)std::chrono::duration_cast<std::chrono::microseconds>(p1 - p0).count() / 1000 << "ms" << endl;       
        
        std::chrono::time_point<std::chrono::high_resolution_clock> p4 = std::chrono::high_resolution_clock::now();
        c1.swap(c2);
        std::chrono::time_point<std::chrono::high_resolution_clock> p5 = std::chrono::high_resolution_clock::now();
        cout << "stitch high_resolution_clock time:" << (float)std::chrono::duration_cast<std::chrono::microseconds>(p1 - p0).count() / 1000 << "ms" << endl; 
        
    }
};

template <typename T>
using Vec = std::vector<T, std::allocator<T>>;

template <typename T>
using Lst = std::list<T, std::allocator<T>>;

template <typename T>
using Deq = std::deque<T, std::allocator<T>>;


int main(void)
{
    Vec<int> coll;
    std::vector<int, std::allocator<int>> coll1;

    test_moveable(vector<int>());
 
    //XCls<int, vector> cl; //类模板 "std::vector" 与 模板 template 参数 "Container" 不兼容 ,vector模板定义如下
    // template<typename _Tp, typename _Alloc = std::allocator<_Tp> >
    // class vector : protected _Vector_base<_Tp, _Alloc>

    XCls<string, Vec> c1; // good
    XCls<string, Lst> c2; // good
    XCls<string, Deq> c3; // good

    return 0;
}