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
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyUniqueObject;
class MyBufferObject;
class MyObject;
class MyModelComponent;

class MyVertexArrayObject: public MySingletonObject {
public:
    static MyVertexArrayObject* sharedVertexArrayObject(void);
    static void close(void);
    
    bool operator==(const MyVertexArrayObject& another) const {
        return 0 != _vertexArrayId && _vertexArrayId == another._vertexArrayId;
    }
    
    bool operator!=(const MyVertexArrayObject& another) const {
        return !operator==(another);
    }
    
    void bind(void) const;
    void enableVertexAttribArray(int attrib) const;
    
    void vertexAttribPoint(const MyBufferObject &bufferObject,
                           int attrib, int size, int stride, int offset = 0) const;
    
    void bindModel(const MyModelComponent *model) const;
    
public:
    static const MyVertexArrayObject* current(void);
    
private:
    MyVertexArrayObject(void);
    virtual ~MyVertexArrayObject(void);
    
    void purge(void);
    
private:
    GLuint _vertexArrayId;
    
    static MyVertexArrayObject *_sharedVertexArrayObject;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyVertexArrayObject_hpp */
