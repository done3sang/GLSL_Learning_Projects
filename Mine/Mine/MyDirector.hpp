//
//  MyDirector.hpp
//  MyGLSL
//
//  Created by xy on 05/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyDirector_hpp
#define MyDirector_hpp

#include <string>
#include <map>
#include "MyPrecompiled.hpp"

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MySingleton;
class MyErrorCallback;
class MyRenderer;
class MyScene;

class MyDirector final: public MySingleton {
public:
    static MyDirector* sharedDirector(void);
    
    // error relative
    bool checkError(void);
    int errCode(void) const { return _errCode; }
    const std::string& errDesc(void) const { return _errDesc; }
    
    // window relative
    MyErrorCallback* errorCallback(void) const {
        return _errorCallback;
    }
    void errorCallback(MyErrorCallback *errCallback);
    
    bool createWindow(int width, int height, const std::string &title);
    void resizeWindow(int width, int height);
    void windowTitle(const std::string &title);
    bool windowShouldClose(void) const;
    
    // main relative
    MyScene* runningScene(void) const { return _runningScene; }
    void runningScene(MyScene *scene);
    
    // renderer relative
    MyRenderer* mainRenderer(void) const { return _mainRenderer; }
    void mainRenderer(MyRenderer *renderer);
    
    // main loop
    void runMainLoop(void);
    
    // close
    void closeDirector(void);
    
    // fps
    float framesPerSecond(void) const { return _framesPerSecond; }
    
private:
    MyDirector(void): _errCode(0),
        _mainRenderer(nullptr), _runningScene(nullptr),
        _errorCallback(nullptr), _glfwWindow(nullptr), _framesPerSecond(0.0f) {}
    ~MyDirector(void);
    
    int _errCode;
    std::string _errDesc;
    MyErrorCallback *_errorCallback;
    GLFWwindow *_glfwWindow;
    MyScene *_runningScene;
    MyRenderer *_mainRenderer;
    std::map<int, std::string> _glErrorMap;
    
    // fps
    float _framesPerSecond;
    
    static MyDirector* _sharedDirector;
    
    void initialize(void);
    void destroy(void);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyDirector_hpp */
