//
//  MyActor.hpp
//  MyGLSL
//
//  Created by xy on 11/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyActor_hpp
#define MyActor_hpp

#include <map>
#include <string>
#include <glm/fwd.hpp>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyUniqueRef;
class MyActorComponent;

class MyActor: public MyUniqueRef {
public:
    int actorId(void) const { return _actorId; }
    
    void actorName(const std::string &name) { _actorName = name; }
    const std::string& actorName(void) { return _actorName; }
    
    void actorPosition(const glm::vec3 &pos) { _actorPosition = pos; }
    const glm::vec3& actorPosition(void) const { return _actorPosition; }
    
    MyActorComponent* componentByType(int compType) const {
        auto iter = _actorComponents.find(compType);
        return _actorComponents.end() != iter ? iter->second: nullptr;
    }
    bool containComponent(int compType) const {
        return _actorComponents.end() != _actorComponents.find(compType);
    }
    bool containComponent(const MyActorComponent *comp) const;
    
    bool addComponent(MyActorComponent *comp);
    bool deleteComponent(MyActorComponent *comp);
    bool deleteComponent(int compType);
    
    void clearComponent(void);
    
protected:
    MyActor(const std::string &name = "Actor"):
    _actorName(name), _actorId(++_sharedActorCount) {}
    ~MyActor(void) { destroy(); }
    
private:
    int _actorId;
    std::string _actorName;
    glm::vec3 _actorPosition;
    std::map<int, MyActorComponent*> _actorComponents;
    
    static int _sharedActorCount;
    
    void actorId(int id) { _actorId = id; }
    void destroy(void);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyActor_hpp */
