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
#include "MyTransformComponent.hpp"
#include "MyModelComponent.hpp"
#include "MyVertexArrayObject.hpp"
#include "MyProgram.hpp"
#include "MyScenario.hpp"
#include "MyDirector.hpp"
#include "MyActor.hpp"

MINE_NAMESPACE_BEGIN

size_t MyActor::_sharedActorCount = 0;
std::vector<size_t> MyActor::_sharedUsedActorId;
std::vector<size_t> MyActor::_sharedDeletedActorId;

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

MyActor::MyActor(const std::string &name):
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
        MyScenario *runningScenario = MyDirector::sharedDirector()->runningScenario();
        if(runningScenario) {
            runningScenario->attachActorRendered(this);
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

void MyActor::render(void) {
    MyActorComponent *comp = componentByType(MyActorComponent::kComponentTypeModel);
    MyModelComponent *modelComp = dynamic_cast<MyModelComponent*>(comp);
    MyVertexArrayObject *runningVAO = MyVertexArrayObject::runningVertexArrayObject();
    assert(modelComp && "ERROR = MyActor::render, model null");
    assert(runningVAO && "ERROR = MyActor::render, vao null");
    
    auto &vertexAttrib = modelComp->vertexAttribute();
    MyBufferObject *vertexBuf = modelComp->modelVertexBuffer();
    //MyBufferObject *elemBuf = modelComp->modelElementBuffer();
    MyProgram *prog = modelComp->modelProgram();
    
    for(auto &iter: vertexAttrib) {
        runningVAO->vertexAttribPoint(*vertexBuf, iter.attrib, iter.size, iter.stride, iter.offset);
    }
    
    prog->useProgram();
    if(modelComp->modelElemented()) {
        //glDrawElements(modelComp->renderMode(), modelComp->renderCount(), <#GLenum type#>, <#const GLvoid *indices#>)
    } else {
        glDrawArrays(modelComp->renderMode(), modelComp->renderStart(), modelComp->renderCount());
    }
}

MINE_NAMESPACE_END
