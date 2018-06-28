//
//  MyMemoryObject.hpp
//  Mine
//
//  Created by xy on 2018/6/26.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MyMemoryObject_hpp
#define MyMemoryObject_hpp

#include <cstdlib>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyUnique;

class MyMemoryObject: public MyUnique {
public:
    MyMemoryObject(char* memoryAddress, size_t memorySize):
    _memoryAddress(memoryAddress),
    _memorySize(memorySize),
    _gameObject(nullptr),
    _previousObject(nullptr)
    {}
    ~MyMemoryObject(void) {}
    
    FORCEINLINE void* gameObject(void) const { return _gameObject; }
    FORCEINLINE void gameObject(void* gameObject) { _gameObject = gameObject; }
    
    FORCEINLINE MyMemoryObject* previousObject(void) const { return _previousObject; }
    FORCEINLINE void previousObject(MyMemoryObject* memoryObject) { _previousObject = memoryObject; }
    
    FORCEINLINE char* memoryAddress(void) const { return _memoryAddress; }
    FORCEINLINE size_t memorySize(void) const { return _memorySize; }
    
private:
    char* _memoryAddress;
    size_t _memorySize;
    void* _gameObject;
    MyMemoryObject* _previousObject;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyMemoryObject_hpp */
