//
//  MyArray.hpp
//  Mine
//
//  Created by xy on 2018/6/28.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MyArray_hpp
#define MyArray_hpp

#include <cstddef>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyObject;

template<typename T, bool O = true>
class MyArray: public MyObject {
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    
    MyArray(size_t length = 0);
    MyArray(const T* dataArr, size_t length);
    MyArray(const MyArray& other);
    MyArray(const MyArray&& other);
    ~MyArray(void);
    
    FORCEINLINE size_t length(void) const { return _length; }
    FORCEINLINE size_t capacity(void) const { return _capacity; }
    FORCEINLINE T* raw(void) { return _data; }
    
    iterator begin(void);
    iterator end(void);
    
    const_iterator begin(void) const;
    const_iterator end(void) const;
    
    T& operator[](size_t i);
    const T& operator[](size_t i) const;
    
    T& operator=(const MyArray& other);
    
    void push_back(const T& value);
    void pop_back(size_t num = 1);
    void pop_front(size_t num = 1);
    
    template<typename ...Args>
    void emplace_back(Args&&... args);
    
    void clear(void);
    void shrink(size_t newLength);
    
    void write(const T* dataArr, size_t length);
    
private:
    T* _data;
    size_t _length;
    size_t _capacity;
    
    void checkCapacity(size_t num = 1);
    void expand(size_t newCapacity);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#include "MyArray.inl"

#endif /* MyArray_hpp */
