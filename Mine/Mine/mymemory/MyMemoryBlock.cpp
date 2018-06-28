//
//  MyMemoryBlock.cpp
//  Mine
//
//  Created by xy on 2018/6/26.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#include "MyObject.hpp"
#include "MyTemplate.hpp"
#include "MyMemoryObject.hpp"
#include "MyMathUtil.hpp"
#include "MyErrorDesc.hpp"
#include "MyMemoryBlock.hpp"

MINE_NAMESPACE_BEGIN

MyMemoryBlock* MyMemoryBlock::blockWithSize(const char* blockName, size_t memorySize) {
    MINE_ASSERT2(memorySize > 0, "Error: MyMemoryBlock::blockWithSize, invalid size");
    
    size_t blockSize = sizeof(MyMemoryBlock);
    memorySize = MyMathUtil::align4(memorySize + blockSize);
    char* memoryAddress = new char[memorySize];
    
    if(nullptr == memoryAddress) {
        return nullptr;
    }
    
    return new(memoryAddress) MyMemoryBlock(blockName, memoryAddress, memorySize);
}

void MyMemoryBlock::destroyGameObject(MyObject* gameObject) {
    MyMemoryObject* nextMemoryObject = nullptr;
    MyMemoryObject* memoryObject = memoryObjectByGameObject(gameObject, &nextMemoryObject);
    
    recycleObject(memoryObject, nextMemoryObject);
}

void* MyMemoryBlock::allocate(size_t sz, bool resident) {
    if(availableSize() < sz) {
        return nullptr;
    }
    
    size_t objectSize = sizeof(MyMemoryObject);
    size_t memorySize = sz + objectSize;
    char* memoryAddress = resident ? (_blockTailManipulator - memorySize): _blockHeadManipulator;
    MyMemoryObject* memoryObject = new(memoryAddress) MyMemoryObject(memoryAddress, memorySize);
    void* objectAddress = memoryAddress + objectSize;
    
    memoryObject->gameObject(objectAddress);
    if(resident) {
        _blockTailManipulator = memoryAddress;
    } else {
        _blockHeadManipulator += memorySize;
    }
    
    MyMemoryObject* &memoryObjectManiplator = resident ? _memoryObjectTail: _memoryObjectHead;
    memoryObject->previousObject(memoryObjectManiplator);
    memoryObjectManiplator = memoryObject;
    
    return objectAddress;
}

void MyMemoryBlock::dealloate(void *p) {
    destroyGameObject(static_cast<MyObject*>(p));
}

void MyMemoryBlock::recycleObject(MyMemoryObject *memoryObject, MyMemoryObject* nextMemoryObject) {
    if(nullptr == memoryObject) {
        return;
    }
    
    if(nextMemoryObject) {
        nextMemoryObject->previousObject(memoryObject->previousObject());
    } else {
        MyMemoryObject *prevObj = memoryObject->previousObject();
        char* curr = reinterpret_cast<char*>(memoryObject);
        if(curr + memoryObject->memorySize() == _blockHeadManipulator) {
            _blockHeadManipulator = prevObj != nullptr ? reinterpret_cast<char*>(prevObj) + prevObj->memorySize(): curr - memoryObject->memorySize();
            _memoryObjectHead = prevObj;
        } else {
            _blockTailManipulator = prevObj != nullptr ? reinterpret_cast<char*>(prevObj): curr + memoryObject->memorySize();
            _memoryObjectTail = prevObj;
        }
    }
}

template<typename T>
MyMemoryObject* MyMemoryBlock::memoryObjectByGameObject(T* gameObject, MyMemoryObject** nextMemoryObject) const {
    MyMemoryObject* prev;
    MyMemoryObject* memoryArr[] = {_memoryObjectHead, _memoryObjectTail};
    bool found = false;
    
    for(MyMemoryObject* curr: memoryArr) {
        prev = nullptr;
        while(curr && !(found = curr->gameObject() == gameObject)) {
            prev = curr;
            curr = curr->previousObject();
        }
        
        if(found) {
            if(nextMemoryObject) {
                *nextMemoryObject = prev;
            }
            return curr;
        }
    }
    
    MINE_ASSERT2(false, "gameObject not found");
    return nullptr;
}

void MyMemoryBlock::destroyBlock(void) {
    MINE_ASSERT2(isEmpty(), "Error = MyMemoryBlock::destroyBlock, block not purged");
    
    delete[] _memoryAddress;
}

MINE_NAMESPACE_END
