//
//  MyString.hpp
//  Mine
//
//  Created by xy on 2018/10/9.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MyString_hpp
#define MyString_hpp

#include <cstddef>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyObject;
class MyArray;

template<class T>
class MyString: public MyObject {
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    
    static_assert(std::is_scalar<T>::value, "Error MyString<T>: Only SUPPORT scalar type");
    
    static MyString* string(void);
    static MyString* stringWithCapacity(size_t capacity);
    static MyString* stringWithRaw(const T* rawData, size_t length);
    
private:
    MyString(void);
    
private:
    T* _data;
    size_t length;
    size_t _capacity;
    
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#include "MyString.inl"

#endif /* MyString_hpp */
