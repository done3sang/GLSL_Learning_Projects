//
//  MyVertexAttributeManager.cpp
//  Mine
//
//  Created by xy on 27/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyTemplate.hpp"
#include "MyVertexAttribute.hpp"
#include "MyVertexAttributeManager.hpp"

MINE_NAMESPACE_BEGIN

MyVertexAttributeManager* MyVertexAttributeManager::_sharedVertexAttributeMgr = nullptr;

MyVertexAttributeManager* MyVertexAttributeManager::sharedVertexAttributeManager(void) {
    if(!_sharedVertexAttributeMgr) {
        _sharedVertexAttributeMgr = new MyVertexAttributeManager();
        _sharedVertexAttributeMgr->refName("MyVertexAttributeManager");
    }
    
    return _sharedVertexAttributeMgr;
}

void MyVertexAttributeManager::closeVertexAttributeManager(void) {
    if(_sharedVertexAttributeMgr) {
        _sharedVertexAttributeMgr->release();
        _sharedVertexAttributeMgr = nullptr;
    }
}

void MyVertexAttributeManager::destroy(void) {
    for(auto &iter: _vertexAttributeMap) {
        iter.second->release();
    }
    _vertexAttributeMap.clear();
}

const MyVertexAttribute* MyVertexAttributeManager::attributeByName(const std::string &name) {
    auto iter = _vertexAttributeMap.find(name);
    if(iter != _vertexAttributeMap.end()) {
        return iter->second;
    }
    
    MyVertexAttribute *att = MyVertexAttribute::createWithFormat(name);
    if(att->loaded()) {
        att->addRef();
        _vertexAttributeMap[name] = att;
    } else {
        att = nullptr;
    }
    
    return att;
}

MINE_NAMESPACE_END
