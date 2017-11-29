//
//  MyVertexArrayObject.hpp
//  MyGLSL
//
//  Created by xy on 29/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyVertexArrayObject_hpp
#define MyVertexArrayObject_hpp

#include <vector>
#include <GLFW/glfw3.h>
#include "Precompiled.h"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyUnique;
class MyBufferObject;

class MyVertexArrayObject: public MyUnique {
public:
    MyVertexArrayObject(void) {}
    ~MyVertexArrayObject(void);
    
    bool operator==(const MyVertexArrayObject& another) const {
        return 0 != _vertexArrayId && _vertexArrayId == another._vertexArrayId;
    }
    
    bool operator!=(const MyVertexArrayObject& another) const {
        return !operator==(another);
    }
    
    bool valid(void) const { return 0 != _vertexArrayId; }
    
    void bindVertexArray(void);
    void enableVertexAttribArray(int attrib);
    
    void vertexAttribPoint(MyBufferObject &bufferObject,
                           int attrib, int size, int stride) const;
    
    void deleteVertexArray(void);
    
public:
    static MyVertexArrayObject* runningVertexArrayObject(void);
    
private:
    GLuint _vertexArrayId;
    
    static MyVertexArrayObject *_runningVertexArrayObject;
};

MINE_NAMESPACE_END

#endif /* MyVertexArrayObject_hpp */
