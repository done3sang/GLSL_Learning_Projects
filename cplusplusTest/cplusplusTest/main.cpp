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
#include <numeric>
#include <list>

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

template<class _T>
struct has_func_struct {
    template<typename _U, void(_U::*)()> struct SFINAE {};
    
    template<class _U> static char test(SFINAE<_U, &_U::func>*);
    template<class _U> static int test(...);
    
    static const bool value = sizeof(test<_T>(0)) == 1;
};

template<class _T>
struct has_func_test:
public std::integral_constant<bool, has_func_struct<_T>::value> {
    
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
private:
    void func(int) {}
    
public:
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
    
    void func(void) {}
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

template<class... Args>
void variadicFunc(Args &&...params) {
    std::vector<int> ivec;
    ivec.emplace_back(100);
   // std::cout << params;... << std::endl;
}

template<class _T>
struct is_pointer_type: public std::false_type {};

template<class _T>
struct is_pointer_type<_T*>: public std::true_type {};

int int_sum(int a, int b) {
    return a + b;
}

class myfoo {
public:
    std::string str;
    myfoo(const std::string &s): str(s) {}
    myfoo(const char *s): str(s) {}
    myfoo(std::string &&s): str(s) {}
    myfoo& operator=(const myfoo &a) & {
        str = a.str;
        return *this;
    }
    
    myfoo& retFoo() {
        return *this;
    }
    myfoo retVal() {
        return *this;
    }
    
    myfoo take() &&;
    //myfoo take() const;
    myfoo take() const &;
    
    myfoo take(int);
    myfoo take(int) const;
};

class SmallInt {
public:
    SmallInt(int v = 0): val(v) {}
    operator int() const { return static_cast<int>(val); }
    
private:
    std::size_t val;
    
    friend SmallInt operator+(const SmallInt &a, const SmallInt &b) {
        return SmallInt(static_cast<int>(a.val + b.val));
    }
};

template<class _Type> class Bar {
    friend _Type;
    int _value = 1;
    
public:
    constexpr int value(void) const { return _value; }
};

template<class _T>
class Blob {
public:
    template<class _It>
    Blob(_It b, _It e);
    
private:
    std::shared_ptr<std::vector<_T>> _data;
};

template<class _T>
template<class _It>
Blob<_T>::Blob(_It b, _It e):
_data(std::make_shared<std::vector<_T>>(b, e)) {}

template<class _Tp>
void rrfunc(_Tp&&) {}

// reserve type info
template<class _Func, class _Tp1, class _Tp2>
void flip1(_Func f, _Tp1 t1, _Tp2 t2) {
    f(t2, t1);
}

template<class _Func, class _Tp1, class _Tp2>
void flip2(_Func f, _Tp1 &&t1, _Tp2 &&t2) {
    f(t2, t1);
}

template<class _Callable, class _Tp1, class _Tp2>
void flip3(_Callable f, _Tp1 &&t1, _Tp2 &&t2) {
    f(std::forward<_Tp2>(t2), std::forward<_Tp1>(t1));
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
    } catch(...) {
        std::cout << "the exception catched by default" << std::endl;
    }
    
    // namespace&overload
    nsprint(1);
    nsprint('w');
    
    // constexpr
    constexpr int myfoox = new_sz();
    
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
    //cd.seth(true);
    
    // substitution failuare is not an error
    std::cout << "SFINAE delegate= " << has_func_test<delegate>::value << std::endl;
    std::cout << "SFINAE xy= " << has_func_test<xy>::value << std::endl;
    std::cout << "SFINAE yy= " << has_func_test<yy>::value << std::endl;
    
    std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>> what;
    
    std::vector<int> vi = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto it = vi.begin();
    while(it != vi.end()) {
        if(*it % 2) {
            it = vi.insert(it, *it);
            it += 2;
        } else {
            it = vi.erase(it);
        }
    }
    vi.shrink_to_fit();
    
    int value = 100;
    std::string vvstr(std::to_string(value));
    
    std::cout << "is_pointer(&value) = " << is_pointer_type<int>::value << std::endl;
    std::cout << "is_pointer(&value) = " << is_pointer_type<int*>::value << std::endl;
    std::cout << "is_pointer(&value) = " << is_pointer_type<decltype((value))>::value << std::endl;
    
    std::cout << "sum = " << std::accumulate(vi.begin(), vi.end(), value) << std::endl;
    
    auto iter = std::back_inserter(vi);
    for(auto index = vi.size(); index < 20; ++index) {
        std::cout << "iter, size = " << std::addressof(iter) << ", " << vi.size() << std::endl;
        *iter = static_cast<int>(index);
    }
    
    int arr[] = {0, 2, 4, 5};
    std::begin(arr);
    
    // std::algorithm
    std::vector<std::string> strv = {"the", "quick", "red", "fox", "jump", "over", "the", "red", "turtle"};
    std::sort(strv.begin(), strv.end());
    strv.erase(std::unique(strv.begin(), strv.end()), strv.end());
    
    auto shorter = [](const std::string &str1, const std::string &str2) -> bool {
        return str1.length() < str2.length();
    };
    
    // bind
    auto bindFunc = std::bind(int_sum, std::placeholders::_1, 100);
    std::cout << "value = " << bindFunc(1) << std::endl;
    
    // iterator
    std::ostream_iterator<int> outer_iter(std::cout, " ");
    for(auto vv: vi) {
        //*outer_iter = vv;
    }
    std::copy(vi.cbegin(), vi.cend(), outer_iter);
    std::cout << std::endl;
    
    // class
    class dest {
    public:
        std::string mystr;
        std::string *pstr;
        dest(void): mystr("2hat"), pstr(&mystr) {}
        ~dest(void) { std::cout << "dest over" << std::endl; pstr->~basic_string(); /*pstr = nullptr;*/ }
    };
        
    class recur {
    public:
        int val;
        int arr[4];
        std::string str;
        dest d;
        ~recur(void) noexcept { str.~basic_string(); d.~dest(); }
        
        void print(void) {
            std::cout << "val, arr = " << val << ", (" << arr << ", " << arr[0] << ", " << arr[1] << ", " << arr[2]
            << ", " << arr[3] << std::endl;
        }
    };
    
    recur rr;
    rr.val = 10;
    rr.arr[0] = rr.arr[1] = rr.arr[2] = rr.arr[3] = 100;
    
    recur rrr(rr);
    rr.print();
    rrr.print();
    
    // rvalue
    int &&rr1 = 42;
    int &&rr2 = std::move(rr1);
    int &&rr3 = static_cast<int&&>(rr2);
    rr2 = static_cast<int&&>(rr2);
    
    class rvalue {
    public:
        std::string *str;
        rvalue(void): str(new std::string("what")) {}
        rvalue(const rvalue& another) {
            str = new std::string(*another.str);
            std::cout << "const rvaule&\n";
        }
        rvalue(rvalue &&r) {
            std::cout << "const rvaule&&\n";
            str = r.str;
            r.str = nullptr;
        }
        ~rvalue(void) {
            std::cout << str << "\n";
            if(str) {
                std::cout << *str << "\n";
                delete str;
            }
        }
        
        rvalue& operator=(const rvalue &another) {
            std::cout << "=(const rvaule&)\n";
            std::string *p = new std::string(*another.str);
            delete str;
            str = p;
            return *this;
        }
        rvalue& operator=(rvalue &&another) {
            std::cout << "=(const rvaule&&)\n";
            if(this != &another) {
                str = another.str;
                another.str = nullptr;
            }
            return *this;
        }
    };
    
    rvalue r1, r2;
    rvalue r3(r1);
    rvalue r4(std::move(r1));
    
    r2 = r3;
    r4 = std::move(r2);
    
    myfoo f1("what"), f2("are");
    f1 = f2;
    f1.retFoo() = f2;
    //f1.retVal() = f2;
    f2 = f1.retVal();
    
    // operator type
    class ClassB;
    class ClassA {
    public:
        int value = 1;
        ClassA(void) = default;
        ClassA(int v): value(v) {}
        ClassA(const ClassB&) { std::cout << "ClassA::ClassA(const ClassB&)\n"; }
        
        // circular pointer
        // .operator->().value = 100; --> OK
        ClassA& operator->(void) {
            return *this;
        }
        //ClassA* operator->(void) {
        //    return this;
        //}
        int& operator*(void) {
            return value;
        }
        
        explicit operator bool(void) const {
            return value;
        }
    };
    class ClassB {
    public:
        ClassB(int) {}
        ClassB(double) {}
        ClassB(void) = default;
        
        operator ClassA() const {
            std::cout << "ClassB::operator ClassA()\n";
            return ClassA();
        }
        
        static ClassA func(const ClassA &a) {
            return ClassA();
        }
        static ClassA func1(const ClassA &b) {
            return ClassA();
        }
        static ClassB func1(const ClassB &b) {
            return ClassB();
        }

        static void func(long) {}
        
        operator int() const;
        operator double() const;
    };
    ClassA ca;
    ClassB cb;
    //ca = cb;
    //ca = ClassB::func(cb);
    ca = static_cast<ClassA>(cb); // doubt: not ambiguous ?
    ca = ClassB::func(static_cast<ClassA>(cb)); // doubt: not ambiguous ?
    //ca->value = 10;
    //ca->->->->value = 1;
    ca.operator->().value = 100;
    //ca << 1;
    if(ca) {
        std::cout << "overn\n";
    }
    //ClassB::func(cb);
    long lg = 1;
    //ClassB cb1(lg);
    short s = 10;
    ClassB cb2(s);
    int itt = 1;
    ClassB cb3(itt);
    //ClassB::func1(10);
    //ClassB::func1(s):
    //ClassB::func1(itt);
    //ClassB::func1(lg);
    SmallInt s1, s2;
    SmallInt s3(s1 + s2);
    // int i = s3 + 1;
    int i = s3.operator int() + 10;
    i = s3 + SmallInt(10);
    
    // oop
    // class Base final
    class Base {
    public:
        int size(void) { return 1; }
        virtual int max_size(void) { return 10; }
        ~Base(void) { std::cout << "~Base\n"; }
        
        virtual int capacity(void) final { return 1; }
        virtual int length(void) { return 1; }
    };
    class Derived final: public Base {
    public:
        int size(int) { return 2; }
        int max_size(void) override { return 20; }
        ~Derived(void) { std::cout << "~Derived\n"; }
        //int capacity(void) { return 2; }
        
        //int length(void) override { return 2; }
        int length(int) { return 2;}
        using Base::length;
        
        rvalue rr;
    };
    Derived dd;
    Base &bb = dd;
    bb.size();
    //dd.size();
    dd.Base::size();
    dd.Base::length();
    dd.length();
    std::cout << bb.size() << " " << bb.max_size() << std::endl;
    
    // template
    Bar<int> ib;
    int ia[] = {0, 1, 2, 3, 4, 5};
    std::vector<short> vs = {0, 1, 2, 3, 4};
    std::list<const char*> sl = {"now", "is", "true"};
    Blob<int> bl1(std::begin(ia), std::end(ia));
    Blob<long> bl2(vs.cbegin(), vs.cend());
    Blob<std::string> bl3(sl.cbegin(), sl.cend());
    std::remove_reference<int&>::type rri;
    std::remove_reference_t<int&> rrt;
    rrfunc(ia[0]);
    rrfunc(itt);
    int ttx(1), tty(100);
    auto callable = [](int v1, int &v2) -> void {
        std::cout << v1 << " " << ++v2 << std::endl;
    };
    auto callable2 = [](int &&v1, int v2) ->void {
        std::cout << v1 << " " << v2 << std::endl;
    };
    flip1(callable, ttx, 23);
    flip2(callable, tty, 23);
    flip3(callable2, ttx, 2);
    
    std::cout << "Hello World!\n";
    return 0;
}
