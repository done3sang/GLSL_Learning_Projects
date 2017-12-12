//
//  MyDirectionalLight.hpp
//  MyGLSL
//
//  Created by xy on 12/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyDirectionalLight_hpp
#define MyDirectionalLight_hpp

#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyActor;

class MyDirectionalLight: public MyActor {
public:
    static MyDirectionalLight* create(void);
    
private:
    MyDirectionalLight(void);
    ~MyDirectionalLight(void) {}
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyDirectionalLight_hpp */
