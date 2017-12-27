//
//  MyAutoreleasePool.cpp
//  MyGLSL
//
//  Created by xy on 01/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifdef DEBUG
#include <cassert>
#endif

#include "MyRef.hpp"
#include "MyTemplate.hpp"
#include "MyAutoreleasePool.hpp"

MINE_NAMESPACE_BEGIN

MyAutoreleasePool* MyAutoreleasePool::_sharedAutorelasePool = nullptr;

MyAutoreleasePool* MyAutoreleasePool::sharedAutoreleasePool(void) {
    if(!_sharedAutorelasePool) {
        _sharedAutorelasePool = new MyAutoreleasePool;
    }
    
    return _sharedAutorelasePool;
}

void MyAutoreleasePool::closeAutoreleasePool(void) {
    if(_sharedAutorelasePool) {
        delete _sharedAutorelasePool;
        _sharedAutorelasePool = nullptr;
    }
}

bool MyAutoreleasePool::contains(const MyRef *object) const {
#ifdef DEBUG
    assert(object && "MyAutoreleasePool::contains should be non-null");
#endif
    
    for(const auto &ref: _objectArray) {
        if(ref == object) {
            return true;
        }
    }
    
    return false;
}

void MyAutoreleasePool::addObject(MyRef *object) {
    assert(object && "MyAutoreleasePool::addObject should be non-null");
    
    if(!contains(object)) {
        _objectArray.push_back(object);
    }
}

void MyAutoreleasePool::clearPool(void) {
    auto iter = _objectArray.begin();
    auto riter = _objectArray.end();
    int releaseCount(0);
    
    while(iter != riter) {
        if(1 == (*iter)->refCount()) {
            (*iter)->release();
            --riter;
            std::swap(*iter, *riter);
            
            ++releaseCount;
        } else {
            ++iter;
        }
    }
    
    if(_objectArray.end() != riter) {
        _objectArray.erase(riter, _objectArray.end());
    }
}

void MyAutoreleasePool::purgePool(void) {
    for(const auto &obj: _objectArray) {
        obj->release();
    }

    _objectArray.clear();
}

MINE_NAMESPACE_END
