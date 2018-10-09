//
//  MyWorld.hpp
//  Mine
//
//  Created by xy on 25/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyWorld_hpp
#define MyWorld_hpp

#include <unordered_map>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyUniqueObject;
class MyActor;

class MyWorld: public MyUniqueObject {
public:
    virtual bool initialize(void) = 0;
    void destroy(void);
    
    virtual void update(float deltaTime);
    void render(void);
    
public:
    bool isActorAttached(MyActor *actor) const;
    void attachActor(MyActor *actor);
    void detachActor(MyActor *actor, bool erased = true);
    
    bool isActorUpdated(MyActor *actor) const;
    void attachActorUpdated(MyActor *actor);
    void detachActorUpdated(MyActor *actor, bool erased = true);
    
    bool isActorRendered(MyActor *actor) const;
    void attachActorRendered(MyActor *actor);
    void detachActorRendered(MyActor *actor, bool erased = true);
    
protected:
    MyWorld(void) {}
    virtual ~MyWorld(void) { destroy(); }
    
    void renderActor(const MyActor* actor);
    
private:
    std::unordered_map<size_t, MyActor*> _worldActorMap;
    std::unordered_map<size_t, MyActor*> _updateActorMap;
    std::unordered_map<size_t, MyActor*> _renderActorMap;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyWorld_hpp */
