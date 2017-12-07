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

bool UniformScene::initialize(void) {
    MyDirector *sharedDirector = MyDirector::sharedDirector();
    sharedDirector->resizeWindow(800, 800);
    sharedDirector->windowTitle("Uniform Block");
    
    _myRenderer = MyRenderer::create("normal");
    _myRenderer->clearBufferBit(MyRenderer::kBufferBitColor | MyRenderer::kBufferBitDepth);
    sharedDirector->mainRenderer(_myRenderer);
    
    MyShader *vertexShader = MyShader::createWithShaderType("uniformblock_vert", MyShader::kShaderTypeVertex);
    if(!MyErrorDesc::successed(vertexShader->loadFromFile("./Shader/uniformblock.vert"))) {
        std::cout << "Error occurs in shader: " << vertexShader->shaderLog() << "\n";
        
        sharedDirector->closeDirector();
        return false;
    }
    
    MyShader *fragmentShader = MyShader::createWithShaderType("uniformblock_frag", MyShader::kShaderTypeFragment);
    if(!MyErrorDesc::successed(fragmentShader->loadFromFile("./Shader/uniformblock.frag"))) {
        std::cout << "Error occurs in shader: " << fragmentShader->shaderLog() << "\n";
        
        sharedDirector->closeDirector();
        return false;
    }
    
    _myProgram = MyProgram::create("uniformblock");
    _myProgram->attachShader(vertexShader);
    _myProgram->attachShader(fragmentShader);
    if(!MyErrorDesc::successed(_myProgram->linkPorgram())) {
        std::cout << "Error occurs in program: " << _myProgram->programLog() << "\n";
        
        sharedDirector->closeDirector();
        return false;
    }
    
    if(!sharedDirector->checkError()) {
        std::cout << "OpenGL Error(" << sharedDirector->errCode() << ") = " <<
        sharedDirector->errDesc() << "\n";
        
        sharedDirector->closeDirector();
        return false;
    }
    
    float vertexData[] = {
        -0.8f, -0.8f, 0.0f, 0.0f, 0.0f,
        0.8f, -0.8f, 0.0f, 1.0f, 0.0f,
        -0.8f, 0.8f, 0.0f, 0.0f, 1.0f,
        0.8f, -0.8f, 0.0f, 1.0f, 0.0f,
        0.8f, 0.8f, 0.0f, 1.0f, 1.0f,
        -0.8f, 0.8f, 0.0f, 0.0f, 1.0f
    };
    
    MyBufferObject *vertexBuffer = MyBufferObject::createWithBufferType(MyBufferObject::kBufferArray);
    vertexBuffer->bufferData(30 * sizeof(float), vertexData);
    
    if(!sharedDirector->checkError()) {
        std::cout << "OpenGL Error(" << sharedDirector->errCode() << ") = " <<
        sharedDirector->errDesc() << "\n";
        
        sharedDirector->closeDirector();
        return false;
    }
    
    _myVertexArray = MyVertexArrayObject::create();
    _myVertexArray->vertexAttribPoint(*vertexBuffer, MyProgram::kAttribPosition, 3, 5 * sizeof(float));
    _myVertexArray->vertexAttribPoint(*vertexBuffer, MyProgram::kAttribTexCoord0, 2, 5 * sizeof(float), 3 * sizeof(float));
    
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

