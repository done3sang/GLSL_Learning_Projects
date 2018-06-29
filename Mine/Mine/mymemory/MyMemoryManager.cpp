//
//  MyMemoryManager.cpp
//  Mine
//
//  Created by xy on 2018/6/27.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#include <memory>
#include "MyTemplate.hpp"
#include "MyObject.hpp"
#include "MyMemoryObject.hpp"
#include "MyMemoryBlock.hpp"
#include "MyStringUtil.hpp"
#include "MyMemoryManager.hpp"

MINE_NAMESPACE_BEGIN

MyMemoryManager* MyMemoryManager::sharedMemoryManager(void) {
    static MyMemoryManager sharedInstance;
    return &sharedInstance;
}

void MyMemoryManager::destroyObject(void* tObj) {
    if(isRaw()) {
        ::delete static_cast<char*>(tObj);
        return;
    }
    
    while(MyMemoryBlock* blockIter = _memoryBlockHead) {
        if(blockIter->containObject(tObj)) {
            blockIter->destroyObject(tObj);
        }
    }
}

void* MyMemoryManager::allocate(size_t sz, bool resident) {
    MINE_ASSERT2(sz > 0, "allocate 0 size memory!");
    if(isRaw()) {
        return ::operator new(sz);
    }
    
    MyMemoryBlock* prevBlock = nullptr;
    MyMemoryBlock* blockIter = _memoryBlockHead;
    while(blockIter) {
        prevBlock = blockIter;
        if(blockIter->isEnough(sz)) {
            break;
        }
        blockIter = blockIter->nextMemoryBlock();
    }
    
    if(nullptr == blockIter) {
        MyMemoryBlock *memoryBlock = createMemoryBlock("gameobject", sz * 16);
        prevBlock->nextMemoryBlock(memoryBlock);
        blockIter = memoryBlock;
    }
    return blockIter->allocate(sz, resident);
}

void MyMemoryManager::deallocate(void* p, bool guilty) {
    if(isRaw()) {
        ::delete static_cast<char*>(p);
    }
    
    MyMemoryBlock* blockIter = _memoryBlockHead;
    while(blockIter) {
        if(blockIter->containObject(p)) {
            blockIter->dealloate(p, guilty);
            return;
        }
        blockIter = blockIter->nextMemoryBlock();
    }
}

MyMemoryBlock* MyMemoryManager::createMemoryBlock(const char *blockName, size_t memorySize) {
    if(isRaw()) {
        return nullptr;
    }
    
    MyMemoryBlock* memoryBlock = MyMemoryBlock::blockWithSize(blockName, memorySize);
    if(memoryBlock) {
        appendMemoryBlock(memoryBlock);
    }
    
    return memoryBlock;
}

MyMemoryBlock* MyMemoryManager::memoryBlockByName(const char* blockName) {
    if(isRaw()) {
        return nullptr;
    }
    
    MyMemoryBlock* blockIter = _memoryBlockHead;
    while(blockIter) {
        if(MyStringUtil::equal_string(blockIter->blockName(), blockName)) {
            return blockIter;
        }
        blockIter = blockIter->nextMemoryBlock();
    }
    
    return nullptr;
}

void MyMemoryManager::appendMemoryBlock(MyMemoryBlock *memoryBlock) {
    if(isRaw()) {
        return;
    }
    
    MyMemoryBlock* prevBlock = nullptr;
    MyMemoryBlock* blockIter = _memoryBlockHead;
    while(blockIter) {
        MINE_ASSERT2(MyStringUtil::equal_string(blockIter->blockName(), memoryBlock->blockName()), "append already queued block");
        prevBlock = blockIter;
        blockIter = blockIter->nextMemoryBlock();
    }
    prevBlock->nextMemoryBlock(memoryBlock);
}

void MyMemoryManager::allocateMain(void) {
    _memoryBlockHead = MyMemoryBlock::blockWithSize("main", 64 << 20); // 64MB for test
    MINE_ASSERT2(nullptr != _memoryBlockHead, "cannot allocate stubborn memory");
}

void MyMemoryManager::purgeMemory(void) {
    if(isRaw()) {
        return;
    }
    
    MyMemoryBlock* nextIter;
    MyMemoryBlock* blockIter = _memoryBlockHead;
    while(blockIter) {
        nextIter = blockIter->nextMemoryBlock();
        blockIter->destroyBlock();
        blockIter = nextIter;
    }
}

MINE_NAMESPACE_END
