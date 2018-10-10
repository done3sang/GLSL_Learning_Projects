//
//  MineWorld.cpp
//  MyGLSLTest
//
//  Created by xy on 2018/10/10.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#include "MineWorld.hpp"

MineWorld* MineWorld::world(void) {
    MineWorld *world = new MineWorld;
    world->objectName("MineWorld");
    return world;
}

bool MineWorld::initialize(void) {
    MyActor *actor = MyActor::actorWithName("triangle");
    MyModelComponent *model = MyModelGenerator::generateSimpleTriangle(.9f);
    MyMaterial *material = MyMaterial::material();
    
    material->shadingProgram(MyShadingManager::sharedShadingManager()->programByName("basic"));
    material->baseTexture(MyTexture2D::textureWithColor(MyFVector4(1.0f, 1.0f, 1.0f, 1.0f)));
    model->material(material);
    actor->addComponent(model);
    attachActor(actor);
    
    _triangleActor = actor;
    return true;
}

void MineWorld::update(float deltaTime) {
    _triangleActor->transform()->rotateByAxisZ(deltaTime);
}
