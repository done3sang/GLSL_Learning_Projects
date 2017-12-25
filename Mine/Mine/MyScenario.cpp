//
//  MyScenario.cpp
//  Mine
//
//  Created by xy on 25/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <cassert>
#include <glm/glm.hpp>
#include "MyRef.hpp"
#include "MyTemplate.hpp"
#include "MyActor.hpp"
#include "MyActorComponent.hpp"
#include "MyModelComponent.hpp"
#include "MyScenario.hpp"

MINE_NAMESPACE_BEGIN

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
    assert(actor && "ERROR = MyScenario::attachActor, actor be nullptr");
    if(isActorAttached(actor)) {
        return;
    }
    
    MyActorComponent *model = actor->componentByType(MyActorComponent::kComponentTypeModel);
    if(model && model->componentEnabled()) {
        attachActorRendered(actor);
    }
    
    actor->addRef();
    _scenarioActorMap[actor->actorId()] = actor;
}

void MyScenario::detachActor(MyActor *actor) {
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
    _scenarioActorMap.erase(actor->actorId());
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

void MyScenario::detachActorUpdated(MyActor *actor) {
    assert(actor && "ERROR = MyScenario::detachActorUpdated, actor be nullptr");
    if(!isActorUpdated(actor)) {
        return;
    }
    
    _updateActorMap.erase(actor->actorId());
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

void MyScenario::detachActorRendered(MyActor *actor) {
    assert(actor && "ERROR = MyScenario::detachActorRendered, actor be nullptr");
    if(!isActorRendered(actor)) {
        return;
    }
    
    _renderActorMap.erase(actor->actorId());
}

MINE_NAMESPACE_END
