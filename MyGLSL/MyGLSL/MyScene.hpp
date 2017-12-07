//
//  MyScene.hpp
//  MyGLSL
//
//  Created by xy on 05/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyScene_hpp
#define MyScene_hpp

#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyUniqueRef;

class MyScene: public MyUniqueRef {
public:
    virtual bool initialize(void) = 0;
    virtual void update(float deltaTime) {}
    virtual void render(void) = 0;
    virtual void destroy(void) {}
    
    static MyScene* create(void);
    
protected:
    virtual ~MyScene(void);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyScene_hpp */
