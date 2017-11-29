//
//  MyVertexArrayObject.cpp
//  MyGLSL
//
//  Created by xy on 29/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyTemplate.hpp"
#include "MyBufferObject.hpp"
#include "MyVertexArrayObject.hpp"

MINE_NAMESPACE_BEGIN

MyVertexArrayObject::~MyVertexArrayObject(void) {
    deleteVertexArray();
}

void MyVertexArrayObject::deleteVertexArray(void) {
    if(!valid()) {
        return;
    }
    
    glDeleteVertexArrays(1, &_vertexArrayId);
    _vertexArrayId = 0;
}

void MyVertexArrayObject::bindVertexArray(void) {
    if(_runningVertexArrayObject && operator==(*_runningVertexArrayObject)) {
        return;
    }
    
    if(!valid()) {
        glGenVertexArrays(1, &_vertexArrayId);
    }
    
    glBindVertexArray(_vertexArrayId);
    _runningVertexArrayObject = this;
}

void MyVertexArrayObject::enableVertexAttribArray(int attrib) {
    bindVertexArray();
    glEnableVertexAttribArray(attrib);
}

void MyVertexArrayObject::vertexAttribPoint(MyBufferObject &bufferObject,
                                            int attrib, int size, int stride) const {
    bufferObject.bindBuffer();
    glVertexAttribPointer(attrib, size, GL_FLOAT, GL_FALSE, stride, nullptr);
}

MINE_NAMESPACE_END
