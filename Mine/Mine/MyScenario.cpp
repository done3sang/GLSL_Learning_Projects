//
//  MyScenario.cpp
//  Mine
//
//  Created by xy on 25/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <glm/glm.hpp>
#include "MyObject.hpp"
#include "MyActorComponent.hpp"
#include "MyActor.hpp"
#include "MyModelComponent.hpp"
#include "MyScenario.hpp"

MINE_NAMESPACE_BEGIN

void MyScenario::destroy(void) {
    for(auto &iter: _updateActorMap) {
        detachActorUpdated(iter.second, false);
    }
    for(auto &iter: _renderActorMap) {
        detachActorRendered(iter.second, false);
    }
    for(auto &iter: _scenarioActorMap) {
       detachActor(iter.second, false);
    }
    _updateActorMap.clear();
    _renderActorMap.clear();
    _scenarioActorMap.clear();
}

void MyScenario::update(float deltaTime) {
    for(auto &iter: _updateActorMap) {
        iter.second->update(deltaTime);
    }
}

void MyScenario::render(void) {
    for(auto &iter: _renderActorMap) {
        iter.second->render();
    }
}

bool MyScenario::isActorAttached(MyActor *actor) const {
    return actor && _scenarioActorMap.end() != _scenarioActorMap.find(actor->actorId());
}

void MyScenario::attachActor(MyActor *actor) {
    MINE_ASSERT2(actor, "ERROR = MyScenario::attachActor, actor be nullptr");
    if(isActorAttached(actor)) {
        return;
    }
    
    MyActorComponent *model = actor->componentByType(MyActorComponent::kComponentTypeModel);
    if(model && model->componentEnabled()) {
        attachActorRendered(actor);
    }
    
    actor->addRef();
    _scenarioActorMap[actor->actorId()] =  actor;
}

void MyScenario::detachActor(MyActor *actor, bool erased) {
    assert(actor && "ERROR = MyScenario::detachActor, actor be nullptr");
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
        _scenarioActorMap.erase(actor->actorId());
    }
}

bool MyScenario::isActorUpdated(MyActor *actor) const {
    return actor && _updateActorMap.end() != _updateActorMap.find(actor->actorId());
}

void MyScenario::attachActorUpdated(MyActor *actor) {
    assert(actor && "ERROR = MyScenario::attachActorUpdated, actor be nullptr");
    if(isActorUpdated(actor)) {
        return;
    }
    
    _updateActorMap[actor->actorId()] = actor;
}

void MyScenario::detachActorUpdated(MyActor *actor, bool erased) {
    assert(actor && "ERROR = MyScenario::detachActorUpdated, actor be nullptr");
    if(!isActorUpdated(actor)) {
        return;
    }
    
    if(erased) {
        _updateActorMap.erase(actor->actorId());
    }
}

bool MyScenario::isActorRendered(MyActor *actor) const {
    return actor && _renderActorMap.end() != _renderActorMap.find(actor->actorId());
}

void MyScenario::attachActorRendered(MyActor *actor) {
    assert(actor && "ERROR = MyScenario::attachActorRendered, actor be nullptr");
    if(isActorRendered(actor)) {
        return;
    }
    
    _renderActorMap[actor->actorId()] = actor;
}

void MyScenario::detachActorRendered(MyActor *actor, bool erased) {
    assert(actor && "ERROR = MyScenario::detachActorRendered, actor be nullptr");
    if(!isActorRendered(actor)) {
        return;
    }
    
    if(erased) {
        _renderActorMap.erase(actor->actorId());
    }
}

MINE_NAMESPACE_END
