//
//  UniformScene.cpp
//  MyGLSLTest
//
//  Created by xy on 05/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "UniformScene.hpp"

UniformScene* UniformScene::create(void) {
    UniformScene *obj = new UniformScene;
    obj->refName("UniformScene");
    
    return obj;
}

bool UniformScene::initialize(void) {
    MyGLSL *sharedGLSL = MyGLSL::sharedGLSL();
    
    _myRenderer = MyRenderer::sharedRenderer();
    _myRenderer->clearBufferBit(MyRenderer::kBufferBitColor | MyRenderer::kBufferBitDepth);
    sharedGLSL->mainRenderer(_myRenderer);
    
    MyShader *vertexShader = MyShader::createWithShaderType(MyShader::kShaderTypeVertex);
    if(!MyErrorDesc::successed(vertexShader->loadFromSource(vertexShaderSource))) {
        std::cout << "Error occurs in shader: " << vertexShader->shaderLog() << "\n";
        
        sharedGLSL->closeGLSL();
        return false;
    }
    
    MyShader *fragmentShader = MyShader::createWithShaderType(MyShader::kShaderTypeFragment);
    if(!MyErrorDesc::successed(fragmentShader->loadFromSource(fragmentShaderSource))) {
        std::cout << "Error occurs in shader: " << fragmentShader->shaderLog() << "\n";
        
        sharedGLSL->closeGLSL();
        return false;
    }
    
    _myProgram = MyProgram::create();
    _myProgram->attachShader(*vertexShader);
    _myProgram->attachShader(*fragmentShader);
    if(!MyErrorDesc::successed(_myProgram->linkPorgram())) {
        std::cout << "Error occurs in program: " << _myProgram->programLog() << "\n";
        
        sharedGLSL->closeGLSL();
        return false;
    }
    
    if(!sharedGLSL->checkOpenGLError()) {
        std::cout << "OpenGL Error(" << sharedGLSL->errCode() << ") = " <<
        sharedGLSL->errDesc() << "\n";
        
        sharedGLSL->closeGLSL();
        return false;
    }
    
    float vertexData[] = {
        -0.8f, -0.8f, 0.0f,
        0.8f, -0.8f, 0.0f,
        0.0f, 0.8f, 0.0f
    };
    
    MyBufferObject *positionBuffer = MyBufferObject::createWithBufferType(MyBufferObject::kBufferArray);
    positionBuffer->bufferData(9 * sizeof(float), positionData);
    
    if(!sharedGLSL->checkOpenGLError()) {
        std::cout << "OpenGL Error(" << sharedGLSL->errCode() << ") = " <<
        sharedGLSL->errDesc() << "\n";
        
        sharedGLSL->closeGLSL();
        return false;
    }
    
    _myVertexArray = MyVertexArrayObject::create();
    _myVertexArray->vertexAttribPoint(*positionBuffer, MyProgram::kAttribPosition, 3, 0);
    _myVertexArray->vertexAttribPoint(*colorBuffer, MyProgram::kAttribColor, 3, 0);
    
    if(!sharedGLSL->checkOpenGLError()) {
        std::cout << "OpenGL Error(" << sharedGLSL->errCode() << ") = " <<
        sharedGLSL->errDesc() << "\n";
        
        sharedGLSL->closeGLSL();
        return false;
    }
    
    _rotationAngle = 0.0f;
    return true;
}
