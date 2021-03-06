//
//  MyActor.cpp
//  MyGLSL
//
//  Created by xy on 11/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <cassert>
#include "MyObject.hpp"
#include "MyTemplate.hpp"
#include "MyActorComponent.hpp"
#include "MyVector.hpp"
#include "MyMatrix.hpp"
#include "MyQuaternion.hpp"
#include "MyCoordinate.hpp"
#include "MyTransformComponent.hpp"
#include "MyModelComponent.hpp"
#include "MyVertex.hpp"
#include "MyVertexManager.hpp"
#include "MyVertexArrayObject.hpp"
#include "MyProgram.hpp"
#include "MyWorld.hpp"
#include "MyRenderer.hpp"
#include "MyDirector.hpp"
#include "MyActor.hpp"
#include "MyLightActor.hpp"
#include "MyLightActor.hpp"
#include "MyDirectionalLight.hpp"
#include "MySpotLight.hpp"

MINE_NAMESPACE_BEGIN

size_t MyActor::_sharedActorCount = 0;
std::vector<size_t> MyActor::_sharedUsedActorId;
std::vector<size_t> MyActor::_sharedDeletedActorId;
std::unordered_map<size_t, MyLightActor*> MyActor::_worldLightMap;

MyActor* MyActor::actorWithName(const char *name) {
    MyActor *act = new MyActor(name);
    act->objectName(name);
    return act;
}

size_t MyActor::sharedActorId(void) {
    size_t aid(1);
    
    if(!_sharedDeletedActorId.empty()) {
        aid = _sharedDeletedActorId.back();
        _sharedDeletedActorId.pop_back();
    } else {
        aid = _sharedUsedActorId.size() + 1;
    }
    
    _sharedUsedActorId.push_back(aid);
    return aid;
}

void MyActor::pushWorldLight(MyLightActor *light) {
    _worldLightMap[light->actorId()] = light;
}

void MyActor::popWorldLight(MyLightActor *light) {
    auto iter = _worldLightMap.find(light->actorId());
    if(_worldLightMap.end() != iter) {
        _worldLightMap.erase(iter);
    }
}

const std::unordered_map<size_t, MyLightActor*>& MyActor::worldLightMap(void) {
    return _worldLightMap;
}

MyActor::MyActor(const char *name):
_actorName(name), _actorId(sharedActorId()) {
    _transform = MyTransformComponent::create();
    addComponent(_transform);
}

void MyActor::destroy(void) {
    auto iter = std::find(_sharedUsedActorId.begin(), _sharedUsedActorId.end(), _actorId);
    assert(_sharedUsedActorId.end() != iter && "ERROR = MyActor::destroy, actor not in used vector");
    auto lastIter = --_sharedUsedActorId.end();
    std::swap(*iter, *lastIter);
    _sharedUsedActorId.pop_back();
    _sharedDeletedActorId.push_back(_actorId);
    
    clearComponent();
}

bool MyActor::addComponent(MyActorComponent *comp) {
    assert(comp && "MyActor::addComponent = paramter null");
    
    if(containComponent(comp)) {
        return false;
    }
    
    for(auto &iter: _actorComponents) {
        if(iter.second->sameGroup(comp)) {
            return false;
        }
    }
    
    _actorComponents[comp->componentType()] = comp;
    comp->addRef();
    
    if(MyActorComponent::kComponentGroupModel == comp->componentType()) {
        MyWorld *runningWorld = MyDirector::sharedDirector()->runningWorld();
        if(runningWorld) {
            runningWorld->attachActorRendered(this);
        }
    }
    
    return true;
}

bool MyActor::containComponent(const MyActorComponent *comp) const {
    return comp && containComponent(comp->componentType());
}

bool MyActor::deleteComponent(int compType) {
    if(MyActor::componentTypeImplicit(compType)) {
        return false;
    }
    
    auto iter = _actorComponents.find(compType);
    
    if(_actorComponents.end() != iter) {
        _actorComponents.erase(iter);
        iter->second->release();
        return true;
    }
    
    return false;
}

bool MyActor::deleteComponent(MyActorComponent *comp) {
    return comp && deleteComponent(comp->componentType());
}

void MyActor::clearComponent(void) {
    for(auto &iter: _actorComponents) {
        iter.second->release();
    }
    
    _actorComponents.clear();
}

MINE_NAMESPACE_END
