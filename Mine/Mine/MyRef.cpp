//
//  MyRef.cpp
//  MyGLSL
//
//  Created by xy on 01/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <cassert>
#include "MyRef.hpp"
#include "MyTemplate.hpp"
#include "MyAutoreleasePool.hpp"

#ifdef DEBUG
#include <iostream>
static int refObjectCount(0);
#endif

MINE_NAMESPACE_BEGIN

MyRef::MyRef(void):
_refCount(1) {
#ifdef DEBUG
    std::cout << "MyRef::MyRef = " << ++refObjectCount << ",  " << _refName << "\n";
#endif
    autorelease();
}

MyRef::MyRef(const MyRef& another):
_refCount(1) {
    autorelease();
}

void MyRef::release(void) {
    assert(_refCount > 0 && "Reference count should be greater than 0");
#ifdef DEBUG
    std::cout << "MyRef::release = " << _refCount << ", " << _refName << "\n";
#endif
    if(0 == --_refCount) {
#ifdef DEBUG
        std::cout << "MyRef::delete = " << --refObjectCount << ", " << _refName << "\n";
#endif
        delete this;
    }
}

void MyRef::autorelease(void) {
    MyAutoreleasePool *pool = MyAutoreleasePool::sharedAutoreleasePool();
    
    pool->addObject(this);
}

MINE_NAMESPACE_END
