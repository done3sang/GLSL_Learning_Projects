//
//  MyMemoryManager.hpp
//  Mine
//
//  Created by xy on 2018/6/27.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MyMemoryManager_hpp
#define MyMemoryManager_hpp

#include <cstddef>
#include "MyPrecompiled.hpp"
#include "MyMemoryBlock.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MySingleton;
class MyObject;

class MyMemoryManager final: public MySingleton {
public:
    static MyMemoryManager* sharedMemoryManager(void);
    
public:
    MyMemoryBlock* createMemoryBlock(const char* blockName, size_t memorySize);
    MyMemoryBlock* memoryBlockByName(const char* blockName);
    
    template<typename T, typename... Args>
    T* createGameObject(Args&&... args, bool resident = false);
    void destroyGameObject(MyObject* gameObject);
    
    void* allocate(size_t sz, bool resident = false);
    void deallocate(void* p);
    
    FORCEINLINE bool isRaw(void) const { return nullptr == _memoryBlockHead; }
    
private:
    MyMemoryManager(void) { allocateMain(); }
    ~MyMemoryManager(void) { purgeMemory(); }
    
    MyMemoryBlock* _memoryBlockHead;
    
    void allocateMain(void);
    void purgeMemory(void);
    void appendMemoryBlock(MyMemoryBlock* memoryBlock);
};

// template has to be done in header file for complier to know the full definition to instantiate
template<typename T, typename... Args>
T* MyMemoryManager::createGameObject(Args&&... args, bool resident) {
    if(isRaw()) {
        return new T(args...);
    }
    
    MyMemoryBlock* prevBlock = nullptr;
    MyMemoryBlock* blockIter = _memoryBlockHead;
    size_t objectSize = sizeof(T);
    while(blockIter) {
        prevBlock = blockIter;
        if(blockIter->isEnough(objectSize)) {
            break;
        }
        blockIter = blockIter->nextMemoryBlock();
    }
    
    if(nullptr == blockIter) {
        MyMemoryBlock *memoryBlock = createMemoryBlock("gameobject", objectSize * 16);
        prevBlock->nextMemoryBlock(memoryBlock);
        blockIter = memoryBlock;
    }
    return blockIter->createGameObject<T>(args...);
}

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyMemoryManager_hpp */
