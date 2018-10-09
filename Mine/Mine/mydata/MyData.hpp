//
//  MyData.hpp
//  Mine
//
//  Created by xy on 2018/6/19.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MyData_hpp
#define MyData_hpp

#include "MyPrecompiled.hpp"
#include "MyArray.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyUniqueObject;

template<typename T>
class MyData: public MyUniqueObject {
public:
    static MyData* data(void);
    static MyData* dataWithLength(size_t length);
    static MyData* dataWithRaw(const T* data, size_t length);
    
    FORCEINLINE size_t size(void) const {
        return _data != nullptr ? _data->length() * sizeof(T): 0;
    }
    FORCEINLINE size_t length(void) const {
        return _data != nullptr ? _data->length(): 0;
    }
    FORCEINLINE size_t offset(void) const {
        return _data != nullptr ? _manipulator - _data->begin(): 0;
    }
    FORCEINLINE T* raw(void) { return _data != nullptr ?  _data->raw(): nullptr; }
    FORCEINLINE const T* raw(void) const { return _data != nullptr ? _data->raw(): nullptr; }
    FORCEINLINE T* rawEnd(void) { return _data != nullptr ? _data->end(): nullptr; }
    FORCEINLINE const T* rawEnd(void) const { return _data != nullptr ? _data->end(): nullptr; }
    
    FORCEINLINE T& operator[](size_t i) {
        return _data->operator[](i);
    }
    FORCEINLINE const T& operator[](size_t i) const {
        return _data->operator[](i);
    }
    
    MyData& operator=(MyArray<T>& arr);
    
    void purge(void);
    
    void pop_front(size_t num);
    void pop_back(size_t num);
    
    void push_back(const T &value);
    
private:
    FORCEINLINE MyData(void):
    _data(nullptr),
    _manipulator(nullptr) {}
    MyData(size_t length);
    MyData(const T* data, size_t length);
    virtual ~MyData(void);
    
    MyArray<T>* _data;
    T* _manipulator;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#include "MyData.inl"

#endif /* MyData_hpp */
