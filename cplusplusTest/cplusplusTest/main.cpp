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
#include <tuple>
#include <regex>
#include <random>

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

template<class _Tp>
int mycompare(const _Tp&, const _Tp&) {
    std::cout << "mycompare general template\n";
    return 0;
}

template<>
int mycompare(const char* const&, const char* const&) {
    std::cout << "mycompare template specialization const char*\n";
    return 1;
}

template<size_t M, size_t N>
int mycompare(const char (&)[M], const char (&)[N]) {
    std::cout << "mycompare template size_t\n";
    return 1;
}

int mycompare(const char* const&, const char* const&) {
    std::cout << "mycompare const char*\n";
    return 2;
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
    
    const char *pstr1 = "ho";
    const char *pstr2 = "mon";
    mycompare("hi", "mon");
    mycompare(pstr1, pstr2);
    
    // tuple
    std::tuple<size_t, size_t, size_t> threed;
    std::tuple<size_t, size_t, size_t> threee{1, 2, 3};
    std::tuple<int, int, int> threef(1, 2, 3);
    std::tuple<int, int, int> threeg = {1, 2, 3};
    auto threeh = std::make_tuple("what", 3, 20.0);
    auto book = std::get<0>(threeh);
    auto cnt = std::get<1>(threeh);
    auto price = std::get<2>(threeh);
    bool bb = threeg == threee;
    
    // throw uncaught
    //throw std::overflow_error("overflow");
    
    // bitset
    std::bitset<16> bits;
    //std::cin >> bits;
    std::cout << "bits = " << bits << std::endl;
    
    // regex
    std::string pattern("[^c]ei");
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    std::regex reg(pattern);
    std::smatch regRet;
    std::string test_str("receipt freind theif receive");
    if(std::regex_search(test_str, regRet, reg)) {
        std::cout << regRet.str() << std::endl;
    }
    for(std::sregex_iterator iit(test_str.cbegin(), test_str.cend(), reg), end_iit; iit != end_iit; ++iit) {
        std::cout << iit->str() << " ";
    }
    std::cout << std::endl;
    reg.assign("[[:alnum:]]+\\.(cpp|cxx|cc)$", std::regex::icase);
    std::string filename;
    /*while(std::cin >> filename) {
        if(std::regex_search(filename, regRet, reg)) {
            std::cout << regRet.str() << std::endl;
        }
    }*/
    std::regex reg1("([[:alnum:]]+)\\.(cpp|cxx|cc)$", std::regex::icase);
    std::cmatch regRet1;
    if(std::regex_search("myfile.cc", regRet1, reg1)) {
        std::cout << regRet1.str(2) << std::endl;
    }
    reg1.assign("(\\d{3})([-. ]?)(\\d{4})([-. ])(\\d{3})");
    if(std::regex_search("532-3345-345", regRet1, reg1)) {
        for(auto i = 0; i != regRet1.size(); ++i) {
            std::cout << regRet1.str(i) << " ";
        }
    }
    std::cout << std::endl;
    std::string fmt("$1.$3.$5");
    std::string number("532-3345-345");
    std::cout << std::regex_replace(number, reg1, fmt) << std::endl;
    std::string test_str2("morgan (201) 555-2368 862-555-0123\
                          drew (973)555.0105\
                          lee (609) 555-0132 2015550175 800.555-0000");
    std::regex reg2("(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})");
    std::string fmt2("$2.$5.$7 ");
    std::cout << std::regex_replace(test_str2, reg2, fmt2, std::regex_constants::format_no_copy) << std::endl;
    
    //random
    std::default_random_engine re;
    std::uniform_int_distribution<int> uid(0, 9);
    std::uniform_real_distribution<float> fid(0, 1);
    std::cout << "\nmin = " << re.min() << ", max = " << re.max() << std::endl;
    std::cout << "min = " << uid.min() << ", max = " << uid.max() << std::endl;
    for(int i = 0; i != 10; ++i) {
        std::cout << uid(re) << " " << fid(re) << " ";
    }
    std::normal_distribution<float> nd(4, 1.5);
    std::vector<unsigned> vnd(9);
    re.seed(time(0));
    for(size_t i = 0; i != 200; ++i) {
        unsigned v = static_cast<unsigned>(std::lround(nd(re)));
        if(v < vnd.size()) {
            ++vnd[v];
        }
    }
    for(size_t j = 0; j != vnd.size(); ++j) {
        std::cout << j << ": " << std::string(vnd[j], '*') << "\n";
    }
    std::bernoulli_distribution bd;
    
    // io
    std::cout << std::showbase;
    std::cout << "default: " << 20 << " " << 1024 << std::endl;
    std::cout << "in octal: " << std::oct << 20 << " " << 1024 << std::endl;
    std::cout << "in hex: " << std::hex << 20 << " " << 1024 << std::endl;
    std::cout << std::noshowbase;
    std::cout << "Precision = " << std::cout.precision() << ", Value = " << std::sqrtf(2.0) << std::endl;
    std::cout.precision(9);
    std::cout << "Precision = " << std::cout.precision() << ", Value = " << std::sqrtf(2.0) << std::endl;
    
    std::cout << "Hello World!\n";
    return 0;
}
