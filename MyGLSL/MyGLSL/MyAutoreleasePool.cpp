//
//  MyAutoreleasePool.cpp
//  MyGLSL
//
//  Created by xy on 01/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyRef.hpp"
#include "MyTemplate.hpp"
#include "MyAutoreleasePool.hpp"

MINE_NAMESPACE_BEGIN

MyAutoreleasePool* MyAutoreleasePool::_sharedAutorelasePool = nullptr;

MyAutoreleasePool* MyAutoreleasePool::sharedAutoreleasePool(void) {
    if(nullptr == _sharedAutorelasePool) {
        _sharedAutorelasePool = new MyAutoreleasePool;
    }
    
    return _sharedAutorelasePool;
}

void MyAutoreleasePool::deleteAutoreleasePool(void) {
    if(_sharedAutorelasePool) {
        delete _sharedAutorelasePool;
        _sharedAutorelasePool = nullptr;
    }
}

bool MyAutoreleasePool::contains(const MyRef *object) const {
    for(const auto &ref: _objectArray) {
        if(ref == object) {
            return true;
        }
    }
    
    return false;
}

void MyAutoreleasePool::addObject(MyRef *object) {
    if(!contains(object)) {
        _objectArray.push_back(object);
    }
}

void MyAutoreleasePool::clear(void) {
    for(const auto &obj: _objectArray) {
        obj->release();
    }
    
    _objectArray.clear();
}

MINE_NAMESPACE_END
