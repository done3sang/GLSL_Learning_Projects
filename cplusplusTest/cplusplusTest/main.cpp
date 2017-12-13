//
//  main.cpp
//  cplusplusTest
//
//  Created by xy on 07/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <string>
#include <iostream>
#include <vector>
#include <type_traits>
#include <stdexcept>

template<typename _T>
struct has_func {
    template<typename _U, void(_U::*)()> struct SFINAE {};
    
    template<typename _U> static char check(SFINAE<_U, &_U::foo>*);
    template<typename _U> static int check(...);
    
    static const bool value = sizeof(check<_T>(0)) == sizeof(char);
};

template<typename _T>
struct has_var_value {
    template<typename _U> static char check(decltype(_U::value) val);
    template<typename _U> static int check(...);
    
    static const bool value = sizeof(check<_T>(0)) == sizeof(char);
};

template<typename _T>
struct has_var_str {
    template<typename _U> static char check(decltype(_U::str) val);
    template<typename _U> static int check(...);
    
    static const bool value = sizeof(check<_T>(0)) == sizeof(char);
};

#define has_member(memName) \
template<typename _T>\
struct has_member_##memName {\
template<typename _U> static char check(decltype(&_U::hoo) val);\
template<typename _U> static int check(...);\
\
static const bool value = sizeof(check<_T>(0)) == sizeof(char);\
};\

has_member(foo)
has_member(poo)
has_member(hoo)

struct MyStruct {
    void foo() {}
    int hoo(int w, int h) { return 0; }
    std::string str;
};

struct TestStruct {
    static void poo() {}
    char value;
    int hoo;
};

template<typename _T>
void xx(void) {
    
}

void ooxx(void) {
    
}

int test(int v) {
    return ++v;
}

template<int value>
int test1(void) {
    return value + 1;
}

int fact(int val) {
    return val > 1 ? fact(val - 1) * val : 1;
}

namespace ns1 {
    void nsprint(int val) {
        std::cout << "print1 = " << val << std::endl;
    }
}

namespace ns2 {
    void nsprint(char c) {
        std::cout << "print2 = " << c << std::endl;
    }
}

using namespace ns1;
using namespace ns2;

constexpr int new_sz(void) { return 45; }

std::string::size_type lesslen(const std::string &str1, const std::string &str2) {
    return str1.length() < str2.length() ? str1.length() : str2.length();
}

std::string::size_type largelen(const std::string &str1, const std::string &str2) {
    return str1.length() > str2.length() ? str1.length() : str2.length();
}

decltype(lesslen)* comparefunc(const std::string&) {
    return lesslen;
}

void xyf();
struct xy {
    friend void xyf() {}
    xy() { xyf(); }
    void g();
    void h();
};

void xy::g() { xyf(); }
void xy::h() { xyf(); }

class yy {
    int x;
    int y;
    
public:
    yy(int v = 100): y(v), x(y) {}
    ~yy(void) = default;
};

class delegate {
public:
    int x;
    int y;
    int z;
    
    delegate(int x, int y, int z): x(x), y(y), z(z) {}
    delegate(int v): delegate(v, v, v) {}
};

class ConstDebug {
public:
    constexpr ConstDebug(bool b = true): h(b), o(b), t(b) {}
    constexpr ConstDebug(bool th, bool to, bool tt): h(th), o(to), t(tt) {}
    
    constexpr bool any() { return h || o || t; }
    void seth(bool b) { h = b;}
    void seto(bool b) { o = b;}
    void sett(bool b) { t = b;}
    
private:
    bool h;
    bool o;
    bool t;
};

int main(int argc, const char * argv[]) {
    static_assert(has_func<MyStruct>::value, "true");
    //static_assert(has_func<TestStruct>::value, "false");
    static_assert(has_var_value<TestStruct>::value, "true");
    //static_assert(has_var_value<MyStruct>::value, "false");
    //static_assert(has_var_str<TestStruct>::value, "true");
    static_assert(has_var_str<MyStruct>::value, "false");
    static_assert(has_member_hoo<TestStruct>::value, "true");
    static_assert(has_member_hoo<MyStruct>::value, "false");
    static_assert(has_member_poo<TestStruct>::value, "true");
    
    char str[] = "Hello C++ 11, New Language";
    //std::for_each(str, str + sizeof(str), [&upcase](char c) { if(isupper(c)) ++upcase; });
    auto func = [](const std::string &str) {
        int count(0);
        for(auto ch: str) {
            if(isupper(ch))
                ++count;
        }
        return count;
    };
    std::function<int()> iv = [](void) { return 100; };
    std::cout << "Uppercase = " << func(str) << std::endl;
    std::cout << std::is_function<decltype(ooxx)>::value << std::endl;
    std::cout << std::is_function<decltype(TestStruct::poo)>::value << std::endl;
    
    test1<10>();
    //constexpr int cv(test1<10>());
    std::vector<std::vector<std::string>> strvec;
    
    const char vstr[] = "what are you doing";
    for(auto &ch: vstr) {
        std::cout << ch << std::endl;
    }
    
    // reference
    int vx = 10;
    static_cast<void>(vx = 20), static_cast<void>(30), 40;
    std::cout << "value = " << vx << std::endl;
    
    int  &rfv = vx;
    int vy = 20;
    rfv = 100;
    rfv = vy;
    std::cout << "value = " << vx << vy << std::endl;
    
    // exception
    std::string str1, str2;
    /*while(std::cin >> str1 >> str2) {
        try {
            if(str1 != str2) {
                throw std::runtime_error("Not equal");
            }
            std::cout << "Equal\n";
        } catch(std::runtime_error &e) {
            std::cerr << e.what() << "\nTry Again? Enter y or n" << std::endl;
            char c;
            std::cin >> c;
            if(!std::cin || 'n' == c) {
                break;
            }
        }
    }*/
    
    // mutable parameter
    std::initializer_list<std::string> ls;
    
    // recursive
    try {
        std::cout << "fact(100) = " << fact(1000)  << std::endl;
    } catch (std::underflow_error &e) {
        std::cout << "underflow = " << e.what() << std::endl;
    } catch(std::overflow_error &e) {
        std::cout << "overflow = " <<  e.what() << std::endl;
    } catch(std::exception &e) {
        std::cout <<  e.what() << std::endl;
    }
    
    // namespace&overload
    nsprint(1);
    nsprint('w');
    
    // constexpr
    constexpr int myfoo = new_sz();
    
    // precompiled
    std::cout << "func = " << __func__ << "\n";
    std::cout << "file = " << __FILE__ << "\n";
    std::cout << "line = " << __LINE__ << "\n";
    std::cout << "time = " << __TIME__ << "\n";
    std::cout << "date = " << __DATE__ << "\n";
    
    // delegating constructor
    delegate del(10);
    std::cout << "del = " << del.x << ", " << del.y << ", " << del.z << std::endl;
    
    // constexpr constructor
    constexpr ConstDebug cd(false);
    cd.seth(true);
    
    return 0;
}
