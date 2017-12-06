//
//  MyBufferObject.hpp
//  MyGLSL
//
//  Created by xy on 29/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyBufferObject_hpp
#define MyBufferObject_hpp

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include "Precompiled.h"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyUnique;
class MyRef;

class MyBufferObject: public MyUnique, public MyRef {
public:
    static const int kBufferArray = GL_ARRAY_BUFFER;
    static const int kBufferElementArray = GL_ELEMENT_ARRAY_BUFFER;
    static const int kBufferUniform = GL_UNIFORM_BUFFER;
    
    static const int kBufferUsageStaticDraw = GL_STATIC_DRAW;
    static const int kBufferUsageDynamicDraw = GL_DYNAMIC_DRAW;
    
public:
    explicit
    MyBufferObject(int bufferType = GL_ARRAY_BUFFER): _bufferType(bufferType),
        _bufferId(0), _bufferUsage(kBufferUsageStaticDraw) {}
    ~MyBufferObject(void);
    
    static MyBufferObject* createWithBufferType(int bufferType = GL_ARRAY_BUFFER);
    
    bool valid(void) const { return 0 != _bufferId; }
    bool validate(void) const;
    
    bool operator==(const MyBufferObject& another) const {
        return 0 != _bufferId && _bufferId == another.bufferId();
    }
    
    bool operator!=(const MyBufferObject& another) const {
        return !operator==(another);
    }
    
    int bufferType(void) const { return _bufferType; }
    int bufferUsage(void) const { return _bufferUsage; }
    GLuint bufferId(void) const { return _bufferId; }
    
    void bindBuffer(void);
    void bufferData(int bufferSize, const void *data, int usage = kBufferUsageStaticDraw);
    void bufferSubData(int bufferOffset, int bufferSize, const void *data);
    void deleteBuffer(void);
    
    static MyBufferObject* runningBufferObject(void) { return _runningBufferObject; }
    
private:
    int _bufferType;
    GLuint _bufferId;
    int _bufferUsage;
    
    static MyBufferObject *_runningBufferObject;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyBufferObject_hpp */
