//
//  TestWorld.cpp
//  MyGLSLTest
//
//  Created by xy on 27/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <iostream>
#include "TestWorld.hpp"

TestWorld* TestWorld::create(void) {
    TestWorld *world = new TestWorld();
    world->objectName("TestWorld");
    return world;
}

bool TestWorld::initialize(void) {
    MyDirector *sharedDirector = MyDirector::sharedDirector();
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
    MyActor *actor = MyActor::actorWithName("torus");
    if(MyModelComponent *model = MyModelGenerator::generateTorus(.4f, .6f, 8, 8)) {
        actor->addComponent(model);
    } else {
        return false;
    }
    attachActor(actor);
    MyPointLight *light = MyPointLight::pointWithName();
    attachActor(light);
    
    return true;
}
