//
//  MyActor.hpp
//  MyGLSL
//
//  Created by xy on 11/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyActor_hpp
#define MyActor_hpp

#include <unordered_map>
#include <string>
#include <vector>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyUniqueObject;
class MyActorComponent;
class MyTransformComponent;
class MyLightActor;

class MyActor: public MyUniqueObject {
public:
    static MyActor* actorWithName(const char* name);
    
    size_t actorId(void) const { return _actorId; }
    void actorName(const std::string &name) { _actorName = name; }
    const std::string& actorName(void) { return _actorName; }
    
    bool operator<(const MyActor &other) {
        return actorId() < other.actorId();
    }
    bool operator==(const MyActor &other) {
        return actorId() == other.actorId();
    }
    
    MyActorComponent* componentByType(int compType) const {
        auto iter = _actorComponents.find(compType);
        return _actorComponents.end() != iter ? iter->second: nullptr;
    }
    bool containComponent(int compType) const {
        return _actorComponents.end() != _actorComponents.find(compType);
    }
    bool containComponent(const MyActorComponent *comp) const;
    
    MyTransformComponent* transform(void) { return _transform; }
    const MyTransformComponent* transform(void) const { return _transform; }
    
    bool addComponent(MyActorComponent *comp);
    bool deleteComponent(MyActorComponent *comp);
    bool deleteComponent(int compType);
    
    virtual void update(float deltaTime) {}
    
    static bool componentTypeImplicit(int compType) {
        return MyActorComponent::kComponentTypeTransform == compType;
    }
    
protected:
    MyActor(const char* name = "Actor");
    virtual ~MyActor(void) { destroy(); }
    
    static void pushWorldLight(MyLightActor *light);
    static void popWorldLight(MyLightActor *light);
    static const std::unordered_map<size_t, MyLightActor*>& worldLightMap(void);
    
private:
    size_t _actorId;
    std::string _actorName;
    std::unordered_map<int, MyActorComponent*> _actorComponents;
    
    static size_t _sharedActorCount;
    static std::vector<size_t> _sharedUsedActorId;
    static std::vector<size_t> _sharedDeletedActorId;
    static std::unordered_map<size_t, MyLightActor*> _worldLightMap;
    static size_t sharedActorId(void);
    MyTransformComponent *_transform;
    
    void actorId(size_t id) { _actorId = id; }
    void destroy(void);
    void clearComponent(void);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyActor_hpp */
