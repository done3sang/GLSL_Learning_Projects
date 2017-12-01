//
//  MyRenderer.hpp
//  MyGLSL
//
//  Created by xy on 01/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyRenderer_hpp
#define MyRenderer_hpp

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include "Precompiled.h"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MySingleton;
class MyRef;

class MyRenderer: public MySingleton, public MyRef {
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
    void drawArrays(int primType, int first, int count);
    
private:
    MyRenderer(void);
    ~MyRenderer(void) {}
    
    int _bufferBits;
    
    static MyRenderer *_sharedRenderer;
    
    void initialize(void);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyRenderer_hpp */
