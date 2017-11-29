//
//  MyBufferObject.cpp
//  MyGLSL
//
//  Created by xy on 29/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyTemplate.hpp"
#include "MyBufferObject.hpp"

MINE_NAMESPACE_BEGIN

MyBufferObject::~MyBufferObject(void) {
    deleteBuffer();
}

void MyBufferObject::deleteBuffer(void) {
    if(!valid()) {
        return;
    }
    
    glDeleteBuffers(1, &_bufferId);
    _bufferId = 0;
}

void MyBufferObject::bindBuffer(void) {
    if(!valid()) {
        glGenBuffers(1, &_bufferId);
    }
    
    glBindBuffer(_bufferType, _bufferId);
    _runningBufferObject = this;
}

void MyBufferObject::bufferData(int bufferSize, const void *buffer, int usage) {
    if(!_runningBufferObject || operator!=(*_runningBufferObject)) {
        bindBuffer();
    }
    
    glBufferData(_bufferType, bufferSize, buffer, usage);
}

MINE_NAMESPACE_END
