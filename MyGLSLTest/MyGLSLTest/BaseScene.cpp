//
//  BaseScene.cpp
//  MyGLSLTest
//
//  Created by xy on 05/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <iostream>
#include "BaseScene.hpp"

BaseScene* BaseScene::create(void) {
    BaseScene *obj =  new BaseScene;
    obj->objectName("BaseScene");
    
    return obj;
}

BaseScene::~BaseScene(void) {
    if(_positionBuffer) {
        _positionBuffer->release();
    }
    
    if(_colorBuffer) {
        _colorBuffer->release();
    }
    
    if(_myProgram) {
        _myProgram->release();
    }
    
    if(_myVertexArray) {
        _myVertexArray->release();
    }
    
    if(_myRenderer) {
        _myRenderer->release();
    }
}

bool BaseScene::initialize(void) {
    MyDirector *sharedDirector = MyDirector::sharedDirector();
    
    _myRenderer = MyRenderer::create("normal");
    _myRenderer->retain();
    _myRenderer->clearBufferBit(MyRenderer::kBufferBitColor | MyRenderer::kBufferBitDepth);
    sharedDirector->mainRenderer(_myRenderer);
    
    _myProgram = MyShadingManager::sharedShadingManager()->programByName("basic");
    _myProgram->retain();
    
    float positionData[] = {
        -0.8f, -0.8f, 0.0f,
        0.8f, -0.8f, 0.0f,
        0.0f, 0.8f, 0.0f
    };
    float colorData[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
    
    _positionBuffer = MyBufferObject::createWithBufferType(MyBufferObject::kBufferArray);
    _positionBuffer->addRef();
    _positionBuffer->bufferData(9 * sizeof(float), positionData);
    
    _colorBuffer = MyBufferObject::createWithBufferType(MyBufferObject::kBufferArray);
    _colorBuffer->addRef();
    _colorBuffer->bufferData(9 * sizeof(float), colorData);
    
    if(!sharedDirector->checkError()) {
        std::cout << "OpenGL Error(" << sharedDirector->errCode() << ") = " <<
        sharedDirector->errDesc() << "\n";
        
        sharedDirector->closeDirector();
        return false;
    }
    
    _myVertexArray = MyVertexArrayObject::create();
    _myVertexArray->vertexAttribPoint(*_positionBuffer, MyProgram::kAttribPosition, 3, 0);
    _myVertexArray->vertexAttribPoint(*_colorBuffer, MyProgram::kAttribColor, 3, 0);
    _myVertexArray->addRef();
    sharedDirector->mainVertexArrayObject(_myVertexArray);
    
    if(!sharedDirector->checkError()) {
        std::cout << "OpenGL Error(" << sharedDirector->errCode() << ") = " <<
        sharedDirector->errDesc() << "\n";
        
        sharedDirector->closeDirector();
        return false;
    }
    
    _rotationAngle = 0.0f;
    identityMatrix(_rotationMatrix);
    
    return true;
}

void BaseScene::update(float deltaTime) {
    MyTransformation::rotateMatrixByAxisZ(_rotationMatrix, MyMathUtil::degreeToRadius(1.0f));
}

void BaseScene::render(void) {
    _myProgram->useProgram();
    _myProgram->uniformMatrix4("modelViewProjectionMatrix", _rotationMatrix);
    
    _myVertexArray->bindVertexArray();
    _myRenderer->drawArrays(MyRenderer::kRenderPrimitiveTriangles, 0, 3);
}
