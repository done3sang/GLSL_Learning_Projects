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

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyUniqueObject;
template<typename T>
class MyArray;

class MyData: public MyUniqueObject {
public:
    static MyData* create(void);
    static MyData* createWithLength(size_t length);
    static MyData* createWithData(char* data, size_t length);
    
    FORCEINLINE size_t length(void) const {
        return _data != nullptr ? _data->length(): 0;
    }
    FORCEINLINE size_t offset(void) const {
        return _data != nullptr ? _manipulator - _data->begin(): 0;
    }
    FORCEINLINE char* raw(void) { return _data != nullptr ? nullptr: _data->raw(); }
    FORCEINLINE char* rawEnd(void) { return _data != nullptr ? nullptr: _data->end(); }
    
    MyData& operator=(MyArray<char> *arr);
    
    void purge(void);
    
    void pop_front(size_t num);
    void pop_back(size_t num);
    
private:
    FORCEINLINE MyData(void):
    _data(nullptr),
    _manipulator(nullptr) {}
    MyData(size_t length);
    MyData(char* data, size_t length);
    virtual ~MyData(void);
    
    MyArray<char>* _data;
    char* _manipulator;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyData_hpp */
