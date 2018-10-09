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
#include <unordered_map>
#include "MyPrecompiled.hpp"

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MySingleton;
class MyErrorCallback;
class MyRenderer;
class MyWorld;
class MyVertexArrayObject;

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
    MyWorld* runningWorld(void) const { return _runningWorld; }
    void runWorld(MyWorld *world);
    
    // main loop
    void runMainLoop(void);
    
    // close
    void closeDirector(void);
    
    // fps
    float framesPerSecond(void) const { return _framesPerSecond; }
    
private:
    MyDirector(void):
    _errCode(0),
    _runningWorld(nullptr),
    _errorCallback(nullptr),
    _glfwWindow(nullptr),
    _framesPerSecond(0.0f) { initialize(); }
    ~MyDirector(void);
    
    int _errCode;
    std::string _errDesc;
    MyErrorCallback *_errorCallback;
    GLFWwindow *_glfwWindow;
    MyWorld *_runningWorld;
    std::unordered_map<int, std::string> _glErrorMap;
    
    // fps
    float _framesPerSecond;
    
    void initialize(void);
    void destroy(void);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyDirector_hpp */
