//
//  MyGLSL.cpp
//  MyGLSL
//
//  Created by xy on 27/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyRef.hpp"
#include "MyErrorDesc.hpp"
#include "MyTemplate.hpp"
#include "MyRenderer.hpp"
#include "MyAutoreleasePool.hpp"
#include "MyRef.hpp"
#include "MyScene.hpp"
#include "MyGLSL.hpp"

MINE_NAMESPACE_BEGIN

static void myWindowErrorCallback(int errCode, const char *errDesc) {
    MyErrorCallback *errCallback = MyGLSL::sharedGLSL()->windowErrorCallback();
    
    if(errCallback) {
        errCallback->disposeError(errCode, errDesc);
    }
}

static void myWindowResizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

MyGLSL* MyGLSL::_shardeGLSL = nullptr;

MyGLSL* MyGLSL::sharedGLSL(void) {
    if(nullptr == _shardeGLSL) {
        _shardeGLSL = new MyGLSL;
        _shardeGLSL->initialize();
    }
    
    return _shardeGLSL;
}

MyGLSL::~MyGLSL(void) {
    destroy();
}

void MyGLSL::destroy(void) {
    MyAutoreleasePool::deleteAutoreleasePool();
    
    if(_glfwWindow) {
        glfwDestroyWindow(_glfwWindow);
        _glfwWindow = nullptr;
    }
    
    glfwTerminate();
}

bool MyGLSL::checkOpenGLError() {
    GLenum err = glGetError();
    
    _errCode = err;
    if(GL_NO_ERROR != err) {
        _errDesc = _glErrorMap[err];
    } else {
        _errDesc.clear();
    }
    
    return GL_NO_ERROR == err;
}

void MyGLSL::closeGLSL(void) {
    if(_shardeGLSL) {
        delete _shardeGLSL;
        _shardeGLSL = nullptr;
    }
}

void MyGLSL::runMainLoop(void) {
    while(!windowShouldClose()) {
        if(_mainRenderer) {
            _mainRenderer->prepareRender();
        }
        
        if(_mainFunc) {
            _mainFunc->update(0.016f);
            _mainFunc->render();
        }
        
        if(_glfwWindow) {
            glfwSwapBuffers(_glfwWindow);
        }
        
        glfwPollEvents();
    }
}

void MyGLSL::initialize(void) {
    MyAutoreleasePool::sharedAutoreleasePool();
    
    glfwSetErrorCallback(myWindowErrorCallback);
    if(!glfwInit()) {
        return;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    
    _glErrorMap[GL_INVALID_ENUM] = "Invalid enum";
    _glErrorMap[GL_INVALID_VALUE] = "Invalid value";
    _glErrorMap[GL_INVALID_OPERATION] = "Invalid operation";
    _glErrorMap[GL_OUT_OF_MEMORY] = "Out of memory";
    _glErrorMap[GL_NO_ERROR] = "No error";
}

bool MyGLSL::createWindow(int width, int height, const std::string &title) {
    GLFWwindow *window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    
    if(!window) {
        return false;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, myWindowResizeCallback);
    _glfwWindow = window;
    
    return true;
}

bool MyGLSL::windowShouldClose(void) const {
    return _glfwWindow && glfwWindowShouldClose(_glfwWindow);
}

MINE_NAMESPACE_END
