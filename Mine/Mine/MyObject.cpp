//
//  MyObject.cpp
//  MyGLSL
//
//  Created by xy on 01/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyTemplate.hpp"
#include "MyAutoreleasePool.hpp"
#include "MyMemoryManager.hpp"
#include "MyObject.hpp"

#ifdef MINE_ARC_DEBUG
#include <iostream>
static int refObjectCount(0);
#endif

MINE_NAMESPACE_BEGIN

MyObject::MyObject(void):
_refCount(1) {
#ifdef MINE_ARC_DEBUG
    std::cout << "MyRef::MyRef = " << ++refObjectCount << ",  " << _objectName << "\n";
#endif
    autorelease();
}

MyObject::MyObject(const MyObject&):
_refCount(1) {
    autorelease();
}

void MyObject::release(void) {
    MINE_ASSERT(!_objectName.empty());
    MINE_ASSERT2(_refCount > 0, "Reference count should be greater than 0");
#ifdef MINE_ARC_DEBUG
    std::cout << "MyRef::release = " << _refCount << ", " << _objectName << "\n";
#endif
    if(0 == --_refCount) {
#ifdef MINE_ARC_DEBUG
        std::cout << "MyRef::delete = " << --refObjectCount << ", " << _objectName << "\n";
#endif
        delete this;
    }
}

void MyObject::autorelease(void) {
    MyAutoreleasePool::sharedAutoreleasePool()->addObject(this);
}

void* MyObject::operator new(size_t sz) {
    return MyMemoryManager::sharedMemoryManager()->allocate(sz);
}

void MyObject::operator delete(void* p) {
    MyMemoryManager::sharedMemoryManager()->deallocate(p);
}

void* MySingletonObject::operator new(size_t sz) {
    return MyMemoryManager::sharedMemoryManager()->allocate(sz, true);
}

//MySingletonObject::~MySingletonObject(void) {
//    release();
//}

MINE_NAMESPACE_END
