//
//  MyVertexAttributeManager.cpp
//  Mine
//
//  Created by xy on 27/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyObject.hpp"
#include "MyVertex.hpp"
#include "MyVertexManager.hpp"

MINE_NAMESPACE_BEGIN

MyVertexManager* MyVertexManager::_sharedVertexMgr = nullptr;

MyVertexManager* MyVertexManager::sharedVertexManager(void) {
    if(!_sharedVertexMgr) {
        _sharedVertexMgr = new MyVertexManager();
        _sharedVertexMgr->objectName("MyVertexManager");
    }
    
    return _sharedVertexMgr;
}

void MyVertexManager::close(void) {
    RELEASE_OBJECT(_sharedVertexMgr);
}

void MyVertexManager::purge(void) {
    for(auto &iter: _vertexMap) {
        RELEASE_OBJECT(iter.second);
    }
    _vertexMap.clear();
}

MyVertex* MyVertexManager::vertexByFormat(const char *format) {
    auto iter = _vertexMap.find(format);
    if(iter != _vertexMap.end()) {
        return iter->second;
    }
    
    MyVertex *vertex = MyVertex::vertexWithFormat(format);
    if(vertex->ready()) {
        RETAIN_OBJECT(vertex);
        _vertexMap[format] = vertex;
    } else {
        vertex = nullptr;
    }
    
    return vertex;
}

MINE_NAMESPACE_END
