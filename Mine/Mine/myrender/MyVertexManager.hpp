//
//  MyVertexAttributeManager.hpp
//  Mine
//
//  Created by xy on 27/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyVertexManager_hpp
#define MyVertexManager_hpp

#include <unordered_map>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MySingletonObject;
class MyVertex;

class MyVertexManager final: public MySingletonObject {
public:
    static MyVertexManager* sharedVertexManager(void);
    static void closeVertexManager(void);
    
    MyVertex* vertexByFormat(const char *format);
    
private:
    ~MyVertexManager(void) { purge(); }
    
    std::unordered_map<const char*, MyVertex*> _vertexMap;
    
    static MyVertexManager *_sharedVertexMgr;
    
    void purge(void);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyVertexAttributeManager_hpp */
