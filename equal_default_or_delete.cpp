#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 如果自定义了一个ctor，编译器不会再提供一个default ctor.
// 如果强制加上=default，就可以重新获取并使用default ctor.

class Zoo
{
public:
    Zoo(int a, int b) : i(a), j(b) {}
    Zoo(const Zoo &) = delete;
    Zoo(Zoo &&) = default;
    Zoo &operator=(const Zoo &) = default;
    Zoo &operator=(Zoo &&) = delete;
private:
    int i;
    int j;
};

class Foo
{
public:
    Foo(int i) : _i(i) {}
    Foo() = default;
    Foo(const Foo &x) : _i(x._i) {}
    //Foo(const Foo &) = default;
    //Foo(const Foo &) = delete;
    Foo & operator=(const Foo &x) {_i = x._i; return *this;}
    //Foo & operator=(const Foo &x) = default;
    //Foo & operator=(const Foo &x) = delete;
private:
    int _i;
};

//No-Copy and Private-Copy
struct NoCopy
{
    NoCopy() = default;
    NoCopy(const NoCopy &) = delete;
    NoCopy &operator=(const NoCopy &) = delete;
    ~NoCopy() = default;
};

struct Friend;
struct PrivateCopy
{
    friend struct Friend;
private:
    PrivateCopy(const PrivateCopy &) {};
    PrivateCopy &operator=(const PrivateCopy &) {}
public:
    PrivateCopy() = default;
    ~PrivateCopy() {};
};

struct Friend
{
    //friend struct PrivateCopy;
    void assign(const Friend& f){ pc = f.pc; };
    PrivateCopy pc;
};

//void Fun1() = default; //“= default”只能出现在默认构造函数、复制/移动构造函数、复制/移动赋值运算符和析构函数中
void Fun2() = delete;

int main(void)
{
    NoCopy nc1;
    //NoCopy nc2 = nc1; //无法引用 函数 "NoCopy::NoCopy(const NoCopy &)" (已声明 所在行数:42) -- 它是已删除的函数
    NoCopy nc3;
    //nc3 = nc1; //无法引用 函数 "NoCopy::operator=(const NoCopy &)" (已声明 所在行数:43) -- 它是已删除的函数

    PrivateCopy pc1;
    //PrivateCopy pc2 = pc1; //"PrivateCopy::PrivateCopy(const PrivateCopy &)" (已声明 所在行数:50) 不可访问
    PrivateCopy pc3; //"PrivateCopy &PrivateCopy::operator=(const PrivateCopy &)" (已声明 所在行数:51) 不可访问
    //pc3 = pc1;

    Friend f1;
    Friend f2;
    f1.assign(f2);
    return 0;
}