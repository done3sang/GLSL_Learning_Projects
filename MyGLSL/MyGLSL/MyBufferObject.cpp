//
//  MyBufferObject.cpp
//  MyGLSL
//
//  Created by xy on 29/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

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

void MyBufferObject::bufferData(int bufferSize, const void *buffer, int usage) {
    bindBuffer();
    glBufferData(_bufferType, bufferSize, buffer, usage);
}

MINE_NAMESPACE_END
