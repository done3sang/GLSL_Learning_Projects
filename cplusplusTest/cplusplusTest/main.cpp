//
//  main.cpp
//  cplusplusTest
//
//  Created by xy on 07/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <string>
#include <iostream>
#include <type_traits>

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
    
    return 0;
}
