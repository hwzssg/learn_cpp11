#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
exp.
for (decl : coll)
{
    statement;
}
---->
for (auto _pos = coll.begin(), _end = coll.end(); _pos != end; ++_pos)
{
    decl = *_pos;
    statement;
}
or
// both begin() and end() are global 
for (auto _pos = begin(coll), _end = end(coll); _pos != end; ++_pos)
{
    decl = *_pos;
    statement;
}
*/
class C
{
public:
    //explicit C(const string &s) :str(s) {}; //error
    C(const string &s) :str(s) {};  //ok
    void print() const { cout << str << endl;}
    string str;
};

// auto & 和 auto 比较，auto指针赋值，如果单个对象赋值超过指针长度，使用auto &效率高


int main(void)
{
    for (int i : {2, 3, 4, 20, 8, 29})
    {
        cout << i << " ";
    }
    cout << endl;
    vector<double> vec {1, 2, 3, 4};
    for (auto elem : vec)
    {
        cout << elem << " ";
    }
    cout << endl;
    for (auto &elem : vec)
    {
        elem *= 3;
    }
    std::cout << "vec after multi 3" << std::endl;
    for (auto elem : vec)
    {
        cout << elem << " ";
    }
    cout << endl;

    vector<string> v_s;
    v_s.push_back("admin");
    v_s.push_back("root");
    for (const  C &c : v_s)
    {
        c.print();
    }
    return 0;
}