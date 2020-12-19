#include <iostream>
#include <functional>
#include <string>


void print()
{

}

template<typename T, typename... Types>
void print(T &arg1, Types&&... args)
{
    std::cout << sizeof...(args) << std::endl;
    std::cout << arg1 << std::endl;
    print(std::forward<Types>(args)...);
}

template<typename T>
inline void hash_combine(size_t &seed, const T& val)
{
    seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<typename T>
inline void hash_val(size_t &seed, const T&val)
{
    hash_combine(seed, val);
}

template<typename T, typename... Types>
inline void hash_val(size_t &seed, const T& val, Types... args)
{
    hash_combine(seed, val);
    hash_val(seed, args...);
}

template<typename... Types>
inline size_t hash_val(Types... args)
{
    size_t seed = 0;
    hash_val(seed, args...);
    return seed;
}

template<typename... Values> class Tuple;
template<> class Tuple<> {};
template<typename Head, typename... Tail>
class Tuple<Head, Tail...>
    : private Tuple<Tail...>
{
    typedef Tuple<Tail...> inherited;
public:
    Tuple() {}
    Tuple(Head h, Tail... t): m_head(h), inherited(t...){}
    Head head() {return m_head;}
    inherited& tail() {return *this; };
protected:
    Head m_head;
};



int main(void)
{
    int a = 10;
    int b = 15;
    int c = 20;
    print(a, b, c, a, b, c);
    std::cout << hash_val(a, b, c) << std::endl;

    Tuple<int, float, std::string> t(41, 3.3, "hello");
    std::cout << t.head() << std::endl;
    std::cout << t.tail().head() << std::endl;
    std::cout << t.tail().tail().head() << std::endl;
    
    return 0;
}


