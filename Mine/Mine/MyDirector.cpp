//
//  MyDirector.cpp
//  MyGLSL
//
//  Created by xy on 05/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyTemplate.hpp"
#include "MyErrorDesc.hpp"
#include "MyRenderer.hpp"
#include "MyAutoreleasePool.hpp"
#include "MyScenario.hpp"
#include "MyFileUtil.hpp"
#include "MyShadingManager.hpp"
#include "MyTimerManager.hpp"
#include "MyDirector.hpp"

MINE_NAMESPACE_BEGIN

static void myWindowErrorCallback(int errCode, const char *errDesc) {
    MyErrorCallback *errCallback = MyDirector::sharedDirector()->errorCallback();
    
    if(errCallback) {
        errCallback->disposeError(errCode, errDesc);
    }
}

static void myWindowResizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

MyDirector* MyDirector::_sharedDirector = nullptr;

MyDirector* MyDirector::sharedDirector(void) {
    if(!_sharedDirector) {
        _sharedDirector = new MyDirector;
        _sharedDirector->initialize();
    }
    
    return _sharedDirector;
}

void MyDirector::closeDirector(void) {
    if(_sharedDirector) {
        delete _sharedDirector;
        _sharedDirector = nullptr;
    }
}

MyDirector::~MyDirector(void) {
    destroy();
}

void MyDirector::destroy(void) {
    if(_errorCallback) {
        _errorCallback->release();
        _errorCallback = nullptr;
    }
    if(_runningScenario) {
        _runningScenario->release();
        _runningScenario = nullptr;
    }
    if(_mainRenderer) {
        _mainRenderer->release();
        _mainRenderer = nullptr;
    }
    
    MyFileUtil::closeFileUtil();
    MyErrorDesc::closeErrorDesc();
    MyTimerManager::closeTimerManager();
    MyShadingManager::sharedShadingManager()->closeShadingManager();
    MyAutoreleasePool::closeAutoreleasePool();
    
    if(_glfwWindow) {
        glfwDestroyWindow(_glfwWindow);
        _glfwWindow = nullptr;
    }
    
    glfwTerminate();
}

bool MyDirector::checkError(void) {
    GLenum err = glGetError();
    
    _errCode = err;
    if(GL_NO_ERROR != err) {
        _errDesc = _glErrorMap[err];
    } else {
        _errDesc.clear();
    }
    
    return GL_NO_ERROR == err;
}

void MyDirector::errorCallback(MyErrorCallback *errCallback) {
    if(_errorCallback) {
        _errorCallback->release();
    }
    if(errCallback) {
        errCallback->addRef();
    }
    
    _errorCallback = errCallback;
}

void MyDirector::mainRenderer(MyRenderer *renderer) {
    if(_mainRenderer) {
        _mainRenderer->release();
    }
    if(renderer) {
        renderer->addRef();
    }
    
    _mainRenderer = renderer;
}

void MyDirector::runningScenario(MyScenario *scenario) {
    if(_runningScenario) {
        _runningScenario->release();
    }
    if(scenario) {
        scenario->addRef();
    }
    
    _runningScenario = scenario;
}

void MyDirector::runMainLoop(void) {
    MyTimerManager *timerMgr = MyTimerManager::sharedTimerManager();
    double fpstime(0.0f);
    double frames(0.0f);
    
    timerMgr->beginTiming();
    
    fpstime = timerMgr->currentTime();
    while(!windowShouldClose()) {
        timerMgr->beginTick();
        
        if(_mainRenderer) {
            _mainRenderer->prepareRender();
        }
        
        if(_runningScenario) {
            _runningScenario->update(static_cast<float>(timerMgr->tickTime()));
            _runningScenario->render();
        }
        
        if(_glfwWindow) {
            glfwSwapBuffers(_glfwWindow);
        }
        
        glfwPollEvents();
        
        timerMgr->endTick();
        
        ++frames;
        if(60.0 <= frames) {
            fpstime = timerMgr->currentTime() - fpstime;
            _framesPerSecond = frames/fpstime;
            fpstime = timerMgr->currentTime();
            frames = 0.0f;
            
            MyAutoreleasePool::sharedAutoreleasePool()->clearPool();
        }
    }
    
    timerMgr->stopTiming();
}

void MyDirector::initialize(void) {
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

bool MyDirector::createWindow(int width, int height, const std::string &title) {
    GLFWwindow *window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    
    if(!window) {
        return false;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, myWindowResizeCallback);
    _glfwWindow = window;
    
    // initializing in valid opengl context
    MyShadingManager::sharedShadingManager()->loadShaderConfig("./Shader/shader.xml");
    
    return true;
}

void MyDirector::resizeWindow(int width, int height) {
    if(_glfwWindow) {
        glfwSetWindowSize(_glfwWindow, width, height);
    }
}

void MyDirector::windowTitle(const std::string &title) {
    if(_glfwWindow) {
        glfwSetWindowTitle(_glfwWindow, title.c_str());
    }
}

bool MyDirector::windowShouldClose(void) const {
    return _glfwWindow && glfwWindowShouldClose(_glfwWindow);
}

MINE_NAMESPACE_END
