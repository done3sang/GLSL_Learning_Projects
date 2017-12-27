//
//  MyRenderer.cpp
//  MyGLSL
//
//  Created by xy on 01/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyRef.hpp"
#include "MyTemplate.hpp"
#include "MyRenderer.hpp"

MINE_NAMESPACE_BEGIN

MyRenderer* MyRenderer::create(const std::string &name) {
    MyRenderer *mr = new MyRenderer(name);
    mr->refName(name);
    
    return mr;
}

MyRenderer::MyRenderer(const std::string &name):
_rendererName(name),
_bufferBits(kBufferBitColor | kBufferBitDepth) {
    initialize();
}

void MyRenderer::initialize(void) {
    clearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void MyRenderer::clearColor(float red, float green, float blue, float alpha) {
    glClearColor(red, green, blue, alpha);
}

void MyRenderer::clearBufferBit(int bufferBits) {
    _bufferBits = bufferBits;
}

void MyRenderer::viewport(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
}

void MyRenderer::prepareRender(void) {
    glClear(_bufferBits);
}

void MyRenderer::drawArrays(int mode, int first, int count) {
    glDrawArrays(mode, first, count);
}

MINE_NAMESPACE_END
