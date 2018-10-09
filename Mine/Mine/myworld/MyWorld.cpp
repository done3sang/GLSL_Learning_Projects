//
//  MyWorld.cpp
//  Mine
//
//  Created by xy on 25/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyObject.hpp"
#include "MyActorComponent.hpp"
#include "MyActor.hpp"
#include "MyModelComponent.hpp"
#include "MyVertexArrayObject.hpp"
#include "MyRenderer.hpp"
#include "MyWorld.hpp"

MINE_NAMESPACE_BEGIN

void MyWorld::destroy(void) {
    for(auto &iter: _updateActorMap) {
        detachActorUpdated(iter.second, false);
    }
    for(auto &iter: _renderActorMap) {
        detachActorRendered(iter.second, false);
    }
    for(auto &iter: _worldActorMap) {
       detachActor(iter.second, false);
    }
    _updateActorMap.clear();
    _renderActorMap.clear();
    _worldActorMap.clear();
}

void MyWorld::update(float deltaTime) {
    for(auto &iter: _updateActorMap) {
        iter.second->update(deltaTime);
    }
}

void MyWorld::render(void) {
    MyRenderer *renderer = MyRenderer::sharedRenderer();
    for(auto &iter: _renderActorMap) {
        renderer->renderActor(iter.second);
    }
}

bool MyWorld::isActorAttached(MyActor *actor) const {
    return actor && _worldActorMap.end() != _worldActorMap.find(actor->actorId());
}

void MyWorld::attachActor(MyActor *actor) {
    MINE_ASSERT2(actor, "ERROR = MyWorld::attachActor, actor be nullptr");
    if(isActorAttached(actor)) {
        return;
    }
    
    MyActorComponent *model = actor->componentByType(MyActorComponent::kComponentTypeModel);
    if(model && model->componentEnabled()) {
        attachActorRendered(actor);
    }
    
    actor->addRef();
    _worldActorMap[actor->actorId()] =  actor;
}

void MyWorld::detachActor(MyActor *actor, bool erased) {
    assert(actor && "ERROR = MyWorld::detachActor, actor be nullptr");
    if(!isActorAttached(actor)) {
        return;
    }
    
    MyActorComponent *model = actor->componentByType(MyActorComponent::kComponentTypeModel);
    if(model && model->componentEnabled()) {
        detachActorRendered(actor);
    }
    detachActorUpdated(actor);
    
    actor->release();
    if(erased) {
        _worldActorMap.erase(actor->actorId());
    }
}

bool MyWorld::isActorUpdated(MyActor *actor) const {
    return actor && _updateActorMap.end() != _updateActorMap.find(actor->actorId());
}

void MyWorld::attachActorUpdated(MyActor *actor) {
    assert(actor && "ERROR = MyWorld::attachActorUpdated, actor be nullptr");
    if(isActorUpdated(actor)) {
        return;
    }
    
    _updateActorMap[actor->actorId()] = actor;
}

void MyWorld::detachActorUpdated(MyActor *actor, bool erased) {
    assert(actor && "ERROR = MyWorld::detachActorUpdated, actor be nullptr");
    if(!isActorUpdated(actor)) {
        return;
    }
    
    if(erased) {
        _updateActorMap.erase(actor->actorId());
    }
}

bool MyWorld::isActorRendered(MyActor *actor) const {
    return actor && _renderActorMap.end() != _renderActorMap.find(actor->actorId());
}

void MyWorld::attachActorRendered(MyActor *actor) {
    assert(actor && "ERROR = MyWorld::attachActorRendered, actor be nullptr");
    if(isActorRendered(actor)) {
        return;
    }
    
    _renderActorMap[actor->actorId()] = actor;
}

void MyWorld::detachActorRendered(MyActor *actor, bool erased) {
    assert(actor && "ERROR = MyWorld::detachActorRendered, actor be nullptr");
    if(!isActorRendered(actor)) {
        return;
    }
    
    if(erased) {
        _renderActorMap.erase(actor->actorId());
    }
}

MINE_NAMESPACE_END
