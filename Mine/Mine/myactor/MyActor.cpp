//
//  MyActor.cpp
//  MyGLSL
//
//  Created by xy on 11/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <cassert>
#include <glm/glm.hpp>
#include "MyTemplate.hpp"
#include "MyActorComponent.hpp"
#include "MyActor.hpp"

MINE_NAMESPACE_BEGIN

int MyActor::_sharedActorCount = 0;

bool MyActor::addComponent(Mine::MyActorComponent *comp) {
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
    
    return true;
}

bool MyActor::containComponent(const Mine::MyActorComponent *comp) const {
    return comp && containComponent(comp->componentType());
}

bool MyActor::deleteComponent(int compType) {
    auto iter = _actorComponents.find(compType);
    
    if(_actorComponents.end() != iter) {
        _actorComponents.erase(iter);
        iter->second->release();
        return true;
    }
    
    return false;
}

bool MyActor::deleteComponent(Mine::MyActorComponent *comp) {
    return comp && deleteComponent(comp->componentType());
}

void MyActor::clearComponent(void) {
    for(auto &iter: _actorComponents) {
        iter.second->release();
    }
    
    _actorComponents.clear();
}

MINE_NAMESPACE_END
