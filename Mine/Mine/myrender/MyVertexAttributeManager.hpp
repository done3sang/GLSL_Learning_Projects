//
//  MyVertexAttributeManager.hpp
//  Mine
//
//  Created by xy on 27/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyVertexAttributeManager_hpp
#define MyVertexAttributeManager_hpp

#include <string>
#include <unordered_map>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MySingletonObject;
class MyVertexAttribute;

class MyVertexAttributeManager final: public MySingletonObject {
public:
    static MyVertexAttributeManager* sharedVertexAttributeManager(void);
    static void closeVertexAttributeManager(void);
    
    const MyVertexAttribute* attributeByName(const std::string &name);
    
private:
    ~MyVertexAttributeManager(void) { destroy(); }
    
    std::unordered_map<std::string, MyVertexAttribute*> _vertexAttributeMap;
    
    static MyVertexAttributeManager *_sharedVertexAttributeMgr;
    
    void destroy(void);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyVertexAttributeManager_hpp */
