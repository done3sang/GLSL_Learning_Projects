//
//  MyScenario.hpp
//  Mine
//
//  Created by xy on 25/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyScenario_hpp
#define MyScenario_hpp

#include <unordered_map>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyUniqueRef;
class MyActor;

class MyScenario: public MyUniqueRef {
public:
    virtual bool initialize(void) = 0;
    virtual void destroy(void);
    
    virtual void update(float deltaTime);
    virtual void render(void);
    
    static MyScenario* create(void) { return nullptr; }
    
public:
    bool isActorAttached(MyActor *actor) const;
    void attachActor(MyActor *actor);
    void detachActor(MyActor *actor);
    
    bool isActorUpdated(MyActor *actor) const;
    void attachActorUpdated(MyActor *actor);
    void detachActorUpdated(MyActor *actor);
    
    bool isActorRendered(MyActor *actor) const;
    void attachActorRendered(MyActor *actor);
    void detachActorRendered(MyActor *actor);
    
protected:
    MyScenario(void) {}
    virtual ~MyScenario(void) { destroy(); }
    
private:
    std::unordered_map<size_t, MyActor*> _scenarioActorMap;
    std::unordered_map<size_t, MyActor*> _updateActorMap;
    std::unordered_map<size_t, MyActor*> _renderActorMap;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyScenario_hpp */
