//
//  MyRenderer.hpp
//  MyGLSL
//
//  Created by xy on 01/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyRenderer_hpp
#define MyRenderer_hpp

#include <string>
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MySingletonObject;
class MyModelComponent;
class MyActor;
class MyBufferObject;

class MyRenderer: public MySingletonObject {
public:
    static MyRenderer* sharedRenderer(void);
    
    static const int kBufferBitColor = GL_COLOR_BUFFER_BIT;
    static const int kBufferBitDepth = GL_DEPTH_BUFFER_BIT;
    
    static const int kRenderPrimitiveTriangles = GL_TRIANGLES;
    static const int kRenderPrimitiveTriangleStrip = GL_TRIANGLE_STRIP;
    
public:
    void clearColor(float red, float green, float blue, float alpha);
    void clearBufferBit(int bufferBits);
    void viewport(int, int ,int, int);
    
    void prepareRender(void);
    void drawArrays(int mode, int first, int count);
    void drawElements(const MyBufferObject *elementBuf, int mode, int count);
    
    // model
    void renderActor(const MyActor *actor);
    void renderModel(const MyModelComponent *model);
    
private:
    explicit
    MyRenderer(void);
    virtual FORCEINLINE ~MyRenderer(void) {}
    
    int _bufferBits;
    
    static MyRenderer *_sharedRenderer;
    
    void initialize(void);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyRenderer_hpp */
