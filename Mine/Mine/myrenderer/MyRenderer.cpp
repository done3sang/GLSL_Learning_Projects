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
#include "MyActor.hpp"
#include "MyModelComponent.hpp"
#include "MyVertexArrayObject.hpp"
#include "MyProgram.hpp"
#include "MyMaterial.hpp"
#include "MyRenderer.hpp"

MINE_NAMESPACE_BEGIN

MyRenderer* MyRenderer::_sharedRenderer = nullptr;

MyRenderer* MyRenderer::sharedRenderer(void) {
    if(nullptr == _sharedRenderer) {
        _sharedRenderer = new MyRenderer();
        _sharedRenderer->objectName("MyRenderer");
    }
    
    return _sharedRenderer;
}

void MyRenderer::close(void) {
    RELEASE_OBJECT(_sharedRenderer);
}

MyRenderer::MyRenderer(void):
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

void MyRenderer::drawElements(int mode, int count) {
    glDrawElements(mode, count, GL_UNSIGNED_INT, nullptr);
}

void MyRenderer::renderActor(const MyActor *actor) {
    MyModelComponent *model = dynamic_cast<MyModelComponent*>(actor->componentByType(MyActorComponent::kComponentTypeModel));
    MyVertexArrayObject *vertexArrayObj = MyVertexArrayObject::sharedVertexArrayObject();
    vertexArrayObj->bindModel(model);
    MyMaterial *material = model->material();
    MyProgram *program = material->shadingProgram();
    program->bindActor(actor->transform(), material);
    if(model->elementBuffer()) {
        drawElements(model->primitive(), model->renderCount());
    } else {
        drawArrays(model->primitive(), model->renderStart(), model->renderCount());
    }
}

MINE_NAMESPACE_END
