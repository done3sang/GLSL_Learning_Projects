//
//  BaseScene.cpp
//  MyGLSLTest
//
//  Created by xy on 05/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "BaseScene.hpp"

static const std::string vertexShaderSource = "#version 400\n"
"in vec3 vertexPosition;\n"
"in vec3 vertexColor;\n"
"out vec3 outColor;\n"
"uniform mat4 modelViewProjectionMatrix = mat4(1.0);\n"
"void main() {\n"
"outColor = vertexColor;\n"
"gl_Position = modelViewProjectionMatrix * vec4(vertexPosition, 1.0);\n"
"}\n";

static const std::string fragmentShaderSource = "#version 400\n"
"in vec3 outColor;\n"
"out vec4 fragColor;\n"
"void main() {\n"
"fragColor = vec4(outColor, 1.0);\n"
"}\n";

BaseScene* BaseScene::create(void) {
    BaseScene *obj =  new BaseScene;
    obj->refName("BaseScene");
    
    return obj;
}

bool BaseScene::initialize(void) {
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
        
        MyBufferObject *positionBuffer = MyBufferObject::createWithBufferType(MyBufferObject::kBufferArray);
        positionBuffer->bufferData(9 * sizeof(float), positionData);
        
        MyBufferObject *colorBuffer = MyBufferObject::createWithBufferType(MyBufferObject::kBufferArray);
        colorBuffer->bufferData(9 * sizeof(float), colorData);
        
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

void BaseScene::update(float deltaTime) {
    _rotationMatrix = glm::rotate(glm::mat4(1.0f), _rotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));
    _rotationAngle += glm::radians(1.0f);
}

void BaseScene::render(void) {
    _myProgram->useProgram();
    _myProgram->uniformMatrix4("modelViewProjectionMatrix", _rotationMatrix);
    
    _myVertexArray->bindVertexArray();
    _myRenderer->drawArrays(MyRenderer::kRenderPrimitiveTriangles, 0, 3);
}

