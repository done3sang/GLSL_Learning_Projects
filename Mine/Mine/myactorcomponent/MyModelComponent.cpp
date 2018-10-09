//
//  MyModelComponent.cpp
//  MyGLSL
//
//  Created by xy on 12/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyObject.hpp"
#include "MyActorComponent.hpp"
#include "MyArray.hpp"
#include "MyData.hpp"
#include "MyFileManager.hpp"
#include "MyBufferObject.hpp"
#include "MyProgram.hpp"
#include "MyMaterial.hpp"
#include "MyShadingManager.hpp"
#include "MyVertex.hpp"
#include "MyVertexManager.hpp"
#include "MyModelComponent.hpp"

MINE_NAMESPACE_BEGIN

const int MyModelComponent::kModelPrimitivePoint = GL_POINTS;
const int MyModelComponent::kModelPrimitiveLine = GL_LINES;
const int MyModelComponent::kModelPrimitiveTriangles = GL_TRIANGLES;
const int MyModelComponent::kModelPrimitiveTriangleStrip = GL_TRIANGLE_STRIP;
const int MyModelComponent::kModelPrimitiveTriangleFan = GL_TRIANGLE_FAN;

MyModelComponent* MyModelComponent::model(void) {
    MyModelComponent *model = new MyModelComponent();
    model->objectName("MyModelComponent");
    return model;
}

MyModelComponent* MyModelComponent::modelWithContentsOfFile(const char *path) {
    MyModelComponent *model = new MyModelComponent();
    model->objectName("MyModelComponent");
    model->initWithContentsOfFile(path);
    return model;
}

MyModelComponent* MyModelComponent::modelWithData(int primitive,
                                                  const MyData<float> *vertexData,
                                                  const char *vertexFormat,
                                                  const MyData<unsigned int> *elementData) {
    MyModelComponent *model = new MyModelComponent();
    model->objectName("MyModelComponent");
    model->initWithData(primitive, vertexData, vertexFormat, elementData);
    return model;
}

MyModelComponent::~MyModelComponent(void) {
    purge();
}

void MyModelComponent::purge(void) {
    RELEASE_OBJECT(_vertexBuffer);
    RELEASE_OBJECT(_elementBuffer);
    RELEASE_OBJECT(_material);
}

bool MyModelComponent::loadWithContentsOfFile(const char *path) {
    purge();
    return initWithContentsOfFile(path);
}

bool MyModelComponent::loadWithData(int primitive,
                                    const MyData<float> *vertexData,
                                    const char *vertexFormat,
                                    const MyData<unsigned int> *elementData) {
    purge();
    return initWithData(primitive, vertexData, vertexFormat, elementData);
}

bool MyModelComponent::initWithContentsOfFile(const char *path) {
    return false;
}

bool MyModelComponent::initWithData(int primitive,
                                    const MyData<float> *vertexData,
                                    const char *vertexFormat,
                                    const MyData<unsigned int> *elementData) {
    MINE_ASSERT2(vertexData && vertexFormat, "Error MyModelComponent::initWithData, parameter null");
    MyVertex* vertex = MyVertex::vertexWithFormat(vertexFormat);
    if(!vertex->ready()) {
        return false;
    }
    
    MyBufferObject *vertexBuf = MyBufferObject::createWithBufferType(MyBufferObject::kBufferArray);
    vertexBuf->bufferData(vertexData->size(), vertexData->raw());
    
    MyBufferObject *elementBuf = nullptr;
    if(elementData) {
        elementBuf = MyBufferObject::createWithBufferType(MyBufferObject::kBufferElementArray);
        elementBuf->bufferData(elementData->size(), elementData->raw());
    }
    
    _renderStart = 0;
    _renderCount = static_cast<int>(vertexData->size())/vertex->strideSize();
    
    ASSIGN_OBJECT(_vertex, vertex);
    ASSIGN_OBJECT(_vertexBuffer, vertexBuf);
    ASSIGN_OBJECT(_elementBuffer, elementBuf);
    
    return true;
}

void MyModelComponent::material(MyMaterial *newMat) {
    ASSIGN_OBJECT(_material, newMat);
}

MINE_NAMESPACE_END
