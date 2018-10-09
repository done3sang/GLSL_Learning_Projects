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

// for MyObject only accept MyObject*
template<class T>
class MyArray: public MyObject {
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    
    static_assert(!std::is_pointer<T>::value || (!std::is_pointer<typename std::remove_pointer<T>::type>::value && !std::is_base_of<MyObject, typename std::remove_pointer<T>::type>::value), "Error MyArray<T>: Not SUPPORT pointer-to-pointer and MyObject*");
    
    static MyArray* array(void);
    static MyArray* arrayWithCapacity(size_t capacity);
    static MyArray* arrayWithRaw(const T* dataArr, size_t length);
    static MyArray* arrayWithArray(const MyArray& arr);
    
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
    MyArray(size_t capacity = 0);
    MyArray(const T* dataArr, size_t length);
    MyArray(const MyArray& arr);
    ~MyArray(void);
    
    void checkCapacity(size_t num = 1);
    void expand(size_t newCapacity);
    
private:
    T* _data;
    size_t _length;
    size_t _capacity;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#include "MyArray.inl"

#endif /* MyArray_hpp */
