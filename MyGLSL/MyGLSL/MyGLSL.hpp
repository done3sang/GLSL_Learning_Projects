//
//  MyGLSL.hpp
//  MyGLSL
//
//  Created by xy on 27/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyGLSL_
#define MyGLSL_

#include <string>
#include <map>
#include "Precompiled.h"

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MySingleton;
class MyUnique;
class MyRef;
class MyErrorCallback;
class MyRenderer;
class MyScene;

class MyGLSL: public MySingleton {
public:
    static MyGLSL* sharedGLSL(void);
    
    // error relative
    bool checkOpenGLError();
    int errCode(void) const { return _errCode; }
    const std::string& errDesc(void) const { return _errDesc; }
    
    // window relative
    MyErrorCallback* windowErrorCallback(void) const {
        return _windowErrorCallback;
    }
    void windowErrorCallback(MyErrorCallback &windowErrCallback) {
        _windowErrorCallback = &windowErrCallback;
    }
    bool createWindow(int width, int height, const std::string &title);
    bool windowShouldClose(void) const;
    
    // main relative
    MyScene* mainFunc(void) const { return _mainFunc; }
    void mainFunc(MyScene *mainFunc) { _mainFunc = mainFunc; }
    
    // renderer relative
    MyRenderer* mainRenderer(void) const { return _mainRenderer; }
    void mainRenderer(MyRenderer *renderer)  { _mainRenderer = renderer; }
    
    void runMainLoop(void);
    void closeGLSL(void);
    
private:
    MyGLSL(void): _errCode(0),
        _windowErrorCallback(nullptr), _glfwWindow(nullptr) {}
    ~MyGLSL(void);
    
    int _errCode;
    std::string _errDesc;
    MyErrorCallback *_windowErrorCallback;
    GLFWwindow *_glfwWindow;
    MyScene *_mainFunc;
    MyRenderer *_mainRenderer;
    std::map<int, std::string> _glErrorMap;
    
    static MyGLSL *_shardeGLSL;
    
    void initialize(void);
    void destroy(void);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif
