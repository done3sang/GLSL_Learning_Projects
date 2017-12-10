//
//  UniformScene.cpp
//  MyGLSLTest
//
//  Created by xy on 05/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <iostream>
#include "UniformScene.hpp"

UniformScene* UniformScene::create(void) {
    UniformScene *obj = new UniformScene;
    obj->refName("UniformScene");
    
    return obj;
}

void UniformScene::destroy(void) {
    if(_myRenderer) {
        _myRenderer->release();
        _myRenderer = nullptr;
    }
    if(_myProgram) {
        _myProgram->release();
        _myProgram = nullptr;
    }
    if(_myVertexBuffer) {
        _myVertexBuffer->release();
        _myVertexBuffer = nullptr;
    }
    if(_myVertexArray) {
        _myVertexArray->release();
        _myVertexArray = nullptr;
    }
}

bool UniformScene::initialize(void) {
    MyDirector *sharedDirector = MyDirector::sharedDirector();
    sharedDirector->resizeWindow(800, 800);
    sharedDirector->windowTitle("Uniform Block");
    
    _myRenderer = MyRenderer::create("normal");
    _myRenderer->addRef();
    _myRenderer->clearBufferBit(MyRenderer::kBufferBitColor | MyRenderer::kBufferBitDepth);
    sharedDirector->mainRenderer(_myRenderer);
    
    _myProgram = MyShadingManager::sharedShadingManager()->programByName("uniformblock");
    _myProgram->addRef();
    
    float vertexData[] = {
        -0.8f, -0.8f, 0.0f, 0.0f, 0.0f,
        0.8f, -0.8f, 0.0f, 1.0f, 0.0f,
        -0.8f, 0.8f, 0.0f, 0.0f, 1.0f,
        0.8f, -0.8f, 0.0f, 1.0f, 0.0f,
        0.8f, 0.8f, 0.0f, 1.0f, 1.0f,
        -0.8f, 0.8f, 0.0f, 0.0f, 1.0f
    };
    
    _myVertexBuffer = MyBufferObject::createWithBufferType(MyBufferObject::kBufferArray);
    _myVertexBuffer->addRef();
    _myVertexBuffer->bufferData(30 * sizeof(float), vertexData);
    
    if(!sharedDirector->checkError()) {
        std::cout << "OpenGL Error(" << sharedDirector->errCode() << ") = " <<
        sharedDirector->errDesc() << "\n";
        
        sharedDirector->closeDirector();
        return false;
    }
    
    _myVertexArray = MyVertexArrayObject::create();
    _myVertexArray->addRef();
    _myVertexArray->vertexAttribPoint(*_myVertexBuffer, MyProgram::kAttribPosition, 3, 5 * sizeof(float));
    _myVertexArray->vertexAttribPoint(*_myVertexBuffer, MyProgram::kAttribTexCoord0, 2, 5 * sizeof(float), 3 * sizeof(float));
    
    if(!sharedDirector->checkError()) {
        std::cout << "OpenGL Error(" << sharedDirector->errCode() << ") = " <<
        sharedDirector->errDesc() << "\n";
        
        sharedDirector->closeDirector();
        return false;
    }
    
    float innerColor[4] = {1.0f, 1.0f, 0.75f, 1.0f};
    float outerColor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    float innerRadius(0.25f);
    float outerRadius(0.45f);
    
    _myProgram->uniformBlockIndex("BlobSetting", "BlobSetting.innerColor", sizeof(innerColor), innerColor);
    _myProgram->uniformBlockIndex("BlobSetting", "BlobSetting.outerColor", sizeof(outerColor), outerColor);
    _myProgram->uniformBlockIndex("BlobSetting", "BlobSetting.innerRadius", sizeof(innerRadius), &innerRadius);
    _myProgram->uniformBlockIndex("BlobSetting", "BlobSetting.outerRadius", sizeof(outerRadius), &outerRadius);
    
    if(!sharedDirector->checkError()) {
        std::cout << "OpenGL Error(" << sharedDirector->errCode() << ") = " <<
        sharedDirector->errDesc() << "\n";
        
        sharedDirector->closeDirector();
        return false;
    }
    
    return true;
}

void UniformScene::update(float deltaTime) {
}

void UniformScene::render(void) {
    _myProgram->useProgram();
    
    _myVertexArray->bindVertexArray();
    _myRenderer->drawArrays(MyRenderer::kRenderPrimitiveTriangles, 0, 6);
}

