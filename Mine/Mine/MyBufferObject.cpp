//
//  MyBufferObject.cpp
//  MyGLSL
//
//  Created by xy on 29/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <cassert>
#include "MyTemplate.hpp"
#include "MyRef.hpp"
#include "MyBufferObject.hpp"

MINE_NAMESPACE_BEGIN

MyBufferObject* MyBufferObject::_runningBufferObject = nullptr;

MyBufferObject::~MyBufferObject(void) {
    deleteBuffer();
}

MyBufferObject* MyBufferObject::createWithBufferType(int bufferType) {
    MyBufferObject *obj = new MyBufferObject(bufferType);
    obj->refName("MyBufferObject");
    
    return obj;
}

bool MyBufferObject::validate(void) const {
    return glIsBuffer(_bufferId);
}

void MyBufferObject::deleteBuffer(void) {
    if(!valid()) {
        return;
    }
    
    glDeleteBuffers(1, &_bufferId);
    _bufferId = 0;
}

void MyBufferObject::bindBuffer(void) {
    if(_runningBufferObject && operator==(*_runningBufferObject)) {
        return;
    }
    
    if(!valid()) {
        glGenBuffers(1, &_bufferId);
    }
    
    glBindBuffer(_bufferType, _bufferId);
}

void MyBufferObject::bufferData(size_t bufferSize, const void *data, int usage) {
    bindBuffer();
    _bufferUsage = usage;
    glBufferData(_bufferType, bufferSize, data, usage);
}

void MyBufferObject::bufferSubData(size_t bufferOffset, size_t bufferSize, const void *data) {
    assert(kBufferUsageDynamicDraw == _bufferUsage && "Buffer sub data should be operated on dynamic buffer");
    
    bindBuffer();
    glBufferSubData(_bufferType, bufferOffset, bufferSize, data);
}

MINE_NAMESPACE_END
