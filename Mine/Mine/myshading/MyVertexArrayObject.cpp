//
//  MyVertexArrayObject.cpp
//  MyGLSL
//
//  Created by xy on 29/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyTemplate.hpp"
#include "MyObject.hpp"
#include "MyBufferObject.hpp"
#include "MyProgram.hpp"
#include "MyActorComponent.hpp"
#include "MyActor.hpp"
#include "MyVertex.hpp"
#include "MyModelComponent.hpp"
#include "MyVertexArrayObject.hpp"

MINE_NAMESPACE_BEGIN

MyVertexArrayObject* MyVertexArrayObject::_sharedVertexArrayObject = nullptr;

MyVertexArrayObject* MyVertexArrayObject::sharedVertexArrayObject(void) {
    if(nullptr == _sharedVertexArrayObject) {
        _sharedVertexArrayObject = new MyVertexArrayObject;
        _sharedVertexArrayObject->objectName("MyVertexArrayObject");
    }
    
    return _sharedVertexArrayObject;
}

MyVertexArrayObject::MyVertexArrayObject(void) {
    glGenVertexArrays(1, &_vertexArrayId);
}

MyVertexArrayObject::~MyVertexArrayObject(void) {
    purge();
}

void MyVertexArrayObject::purge(void) {
    glDeleteVertexArrays(1, &_vertexArrayId);
    _vertexArrayId = 0;
}

void MyVertexArrayObject::bind(void) const {
    glBindVertexArray(_vertexArrayId);
}

void MyVertexArrayObject::enableVertexAttribArray(int attrib) const {
    bind();
    glEnableVertexAttribArray(attrib);
}

void MyVertexArrayObject::vertexAttribPoint(const MyBufferObject &bufferObject,
                                            int attrib, int size, int stride, int offset) const {
    bind();
    glEnableVertexAttribArray(attrib);
    bufferObject.bind();
    glVertexAttribPointer(attrib, size, GL_FLOAT, GL_FALSE, stride, (GLubyte*)NULL + offset);
}

void MyVertexArrayObject::bindModel(const MyModelComponent *model) const {
    const MyVertex *vertex = model->vertex();
    const MyBufferObject &vertexBuf = *(model->vertexBuffer());
    
    for(auto &iter: vertex->attributeMap()) {
        vertexAttribPoint(vertexBuf, iter.attrib, iter.size, vertex->stride(), iter.offset);
    }
}

MINE_NAMESPACE_END
