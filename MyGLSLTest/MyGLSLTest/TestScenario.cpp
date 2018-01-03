//
//  TestScenario.cpp
//  MyGLSLTest
//
//  Created by xy on 27/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <iostream>
#include "TestScenario.hpp"

TestScenario* TestScenario::create(void) {
    TestScenario *scenario = new TestScenario();
    scenario->refName("TestScenario");
    return scenario;
}

bool TestScenario::initialize(void) {
    MyDirector *sharedDirector = MyDirector::sharedDirector();
    MyRenderer *renderer = MyRenderer::create("Normal");
    renderer->clearBufferBit(MyRenderer::kBufferBitColor | MyRenderer::kBufferBitDepth);
    sharedDirector->mainRenderer(renderer);
    MyVertexArrayObject *vao = MyVertexArrayObject::create();
    sharedDirector->mainVertexArrayObject(vao);
    
    /*
    MyActor *actor = MyActor::createWithName("triangle");
    MyModelComponent *model = MyModelComponent::create();
    std::vector<float> modelData{
        -0.8f, -0.8f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.8f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.8f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    if(!model->loadVertexData(modelData, "position[3]_color[3]")) {
        return false;
    }
    actor->addComponent(model);
    attachActor(actor);
    */
    MyActor *actor = MyActor::createWithName("torus");
    if(MyModelComponent *model = MyModelGenerator::generateTorus(.4f, .6f, 8, 8)) {
        actor->addComponent(model);
    } else {
        return false;
    }
    attachActor(actor);
    MyPointLight *light = MyPointLight::create();
    attachActor(light);
    
    return true;
}
