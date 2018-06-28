//
//  MyMemoryBlock.hpp
//  Mine
//
//  Created by xy on 2018/6/26.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MyMemoryBlock_hpp
#define MyMemoryBlock_hpp

#include <cstddef>
#include "MyPrecompiled.hpp"
#include "MyMemoryObject.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyUnique;
class MyObject;

class MyMemoryBlock final: public MyUnique {
public:
    static MyMemoryBlock* blockWithSize(const char* blockName, size_t memorySize);
    
public:
    template<typename T, typename... Args>
    T* createGameObject(Args&&... args, bool resident = false);
    void destroyGameObject(MyObject* gameObject);
    void recycleObject(MyMemoryObject* memoryObject, MyMemoryObject* nextMemoryObject);
    
    template<typename T>
    MyMemoryObject* memoryObjectByGameObject(T* gameObject, MyMemoryObject** nextMemoryObject = nullptr) const;
    
    template<typename T>
    bool containGameObject(T* gameObject) const {
        void* ptr = static_cast<void*>(gameObject);
        return _memoryAddress < ptr && ptr <= _memoryAddress + _memorySize;
    }
    
    void destroyBlock(void);
    
    FORCEINLINE const char* blockName(void) const { return _blockName; }
    FORCEINLINE size_t memorySize(void) const { return _memorySize; }
    
    FORCEINLINE bool isEmpty(void) const { return _memoryObjectHead == nullptr && _memoryObjectTail == nullptr; }
    FORCEINLINE bool isFull(void) const { return _blockTailManipulator <= _blockHeadManipulator; }
    FORCEINLINE size_t availableSize(void) const { return _blockTailManipulator - _blockHeadManipulator; }
    FORCEINLINE bool isEnough(size_t objectSize) const { return availableSize() >= objectSize; }
    
    FORCEINLINE MyMemoryBlock* nextMemoryBlock(void) const { return _nextMemoryBlock; }
    FORCEINLINE void nextMemoryBlock(MyMemoryBlock* nextBlock) { _nextMemoryBlock = nextBlock; }
    
    void* allocate(size_t sz, bool resident = false);
    void dealloate(void* p);
    
private:
    explicit
    FORCEINLINE MyMemoryBlock(const char* blockName, char* memoryAddress, size_t memorySize):
    _blockName(blockName),
    _memoryAddress(memoryAddress),
    _memorySize(memorySize),
    _blockHeadManipulator(memoryAddress + sizeof(MyMemoryBlock)),
    _blockTailManipulator(memoryAddress + memorySize),
    _memoryObjectHead(nullptr),
    _memoryObjectTail(nullptr),
    _nextMemoryBlock(nullptr) {}
    FORCEINLINE ~MyMemoryBlock(void) {}
    
    const char* _blockName;
    char* _memoryAddress;
    size_t _memorySize;
    char* _blockHeadManipulator; // for temporary object
    char* _blockTailManipulator; // for resident object
    MyMemoryObject* _memoryObjectHead;
    MyMemoryObject* _memoryObjectTail;
    MyMemoryBlock* _nextMemoryBlock;
};

// template has to be done in header file for complier to know the full definition to instantiate
template<typename T, typename... Args>
T* MyMemoryBlock::createGameObject(Args&&... args, bool resident) {
    if(availableSize() < sizeof(T)) {
        return nullptr;
    }
    
    size_t objectSize = sizeof(MyMemoryObject);
    size_t memorySize = sizeof(T) + objectSize;
    char* memoryAddress = resident ? (_blockTailManipulator - memorySize): _blockHeadManipulator;
    MyMemoryObject* memoryObject = new(memoryAddress) MyMemoryObject(memoryAddress, memorySize);
    T* tObject = ::new(memoryAddress + objectSize) T(args...);
    
    memoryObject->gameObject(tObject);
    if(resident) {
        _blockTailManipulator = memoryAddress;
    } else {
        _blockHeadManipulator = memoryAddress + memorySize;
    }
    
    MyMemoryObject* &memoryObjectManiplator = resident ? _memoryObjectTail: _memoryObjectHead;
    memoryObject->previousObject(memoryObjectManiplator);
    memoryObjectManiplator = memoryObject;
    
    return tObject;
}

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyMemoryBlock_hpp */
