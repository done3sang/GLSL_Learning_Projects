//
//  MyVertexArrayObject.cpp
//  MyGLSL
//
//  Created by xy on 29/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyTemplate.hpp"
#include "MyRef.hpp"
#include "MyBufferObject.hpp"
#include "MyVertexArrayObject.hpp"
#include "MyProgram.hpp"

MINE_NAMESPACE_BEGIN

MyVertexArrayObject* MyVertexArrayObject::_runningVertexArrayObject = nullptr;

MyVertexArrayObject* MyVertexArrayObject::runningVertexArrayObject(void) {
    return _runningVertexArrayObject;
}

MyVertexArrayObject::~MyVertexArrayObject(void) {
    deleteVertexArray();
}

MyVertexArrayObject* MyVertexArrayObject::create(void) {
    MyVertexArrayObject *obj = new MyVertexArrayObject;
    obj->refName("MyVertexArrayObject");
    
    return obj;
}

bool MyVertexArrayObject::validate(void) const {
    return glIsVertexArray(_vertexArrayId);
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
        
        //glEnableVertexAttribArray(MyProgram::kAttribPosition);
        //glEnableVertexAttribArray(MyProgram::kAttribColor);
        //glEnableVertexAttribArray(MyProgram::kAttribTexCoord0);
        //glEnableVertexAttribArray(MyProgram::kAttribNormal);
        //glEnableVertexAttribArray(MyProgram::kAttribTangent);
    }
    
    glBindVertexArray(_vertexArrayId);
    _runningVertexArrayObject = this;
}

void MyVertexArrayObject::enableVertexAttribArray(int attrib) {
    bindVertexArray();
    glEnableVertexAttribArray(attrib);
}

void MyVertexArrayObject::vertexAttribPoint(MyBufferObject &bufferObject,
                                            int attrib, int size, int stride) {
    bindVertexArray();
    glEnableVertexAttribArray(attrib);
    bufferObject.bindBuffer();
    glVertexAttribPointer(attrib, size, GL_FLOAT, GL_FALSE, stride, nullptr);
}

MINE_NAMESPACE_END
