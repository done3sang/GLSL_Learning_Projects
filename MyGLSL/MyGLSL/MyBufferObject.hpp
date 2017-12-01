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
    
    static const int kBufferUsageStaticDraw = GL_STATIC_DRAW;
    
public:
    explicit
    MyBufferObject(int bufferType = GL_ARRAY_BUFFER): _bufferType(bufferType),
        _bufferId(0), _bufferUsage(kBufferUsageStaticDraw) {}
    ~MyBufferObject(void);
    
    static MyBufferObject* createWithBufferType(int bufferType = GL_ARRAY_BUFFER);
    
    bool valid(void) const { return 0 != _bufferId; }
    
    bool operator==(const MyBufferObject& another) const {
        return 0 != _bufferId && _bufferId == another.bufferId();
    }
    
    bool operator!=(const MyBufferObject& another) const {
        return !operator==(another);
    }
    
    int bufferType(void) const { return _bufferType; }
    int bufferUsage(void) const { return _bufferUsage; }
    
    void bindBuffer(void);
    void bufferData(int bufferSize, const void *buffer, int usage = kBufferUsageStaticDraw);
    
    void deleteBuffer(void);
    
    static MyBufferObject *runningBufferObject(void);
    
private:
    int _bufferType;
    GLuint _bufferId;
    int _bufferUsage;
    
    static MyBufferObject *_runningBufferObject;
    
    GLuint bufferId(void) const { return _bufferId; }
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyBufferObject_hpp */
