//
//  MyRenderer.cpp
//  MyGLSL
//
//  Created by xy on 01/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyObject.hpp"
#include "MyBufferObject.hpp"
#include "MyActorComponent.hpp"
#include "MyModelComponent.hpp"
#include "MyRenderer.hpp"

MINE_NAMESPACE_BEGIN

MyRenderer* MyRenderer::create(const std::string &name) {
    MyRenderer *mr = new MyRenderer(name);
    mr->objectName(name);
    
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

void MyRenderer::renderModel(const MyModelComponent *model) {
    MINE_ASSERT2(model, "ERROR = MyRenderer::renderModel, model null");
    /*
    if(model->modelElemented()) {
        model->modelElementBuffer()->bindBuffer();
        glDrawElements(model->renderMode(), model->renderCount(), GL_UNSIGNED_INT, nullptr);
    } else {
        glDrawArrays(model->renderMode(), model->renderStart(), model->renderCount());
    }
     */
}

MINE_NAMESPACE_END
