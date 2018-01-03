//
//  MyLightActor.hpp
//  Mine
//
//  Created by xy on 03/01/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MyLightActor_hpp
#define MyLightActor_hpp

#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyActor;
class MyProgram;

class MyLightActor: public MyActor {
public:
    virtual void bindProgram(MyProgram *prog) = 0;
    
protected:
    MyLightActor(void);
    virtual ~MyLightActor(void);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyLightActor_hpp */
