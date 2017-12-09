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

MINE_NAMESPACE_BEGIN

MyRef::MyRef(void):
_refCount(1) {
    autorelease();
}

MyRef::MyRef(const MyRef& another):
_refCount(1) {
    autorelease();
}

void MyRef::release(void) {
    assert(_refCount > 0 && "Reference count should be greater than 0");    
    if(0 == --_refCount) {
        delete this;
    }
}

void MyRef::autorelease(void) {
    MyAutoreleasePool *pool = MyAutoreleasePool::sharedAutoreleasePool();
    
    pool->addObject(this);
}

MINE_NAMESPACE_END
