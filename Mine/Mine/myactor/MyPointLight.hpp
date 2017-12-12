//
//  MyPointLight.hpp
//  MyGLSL
//
//  Created by xy on 12/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyPointLight_hpp
#define MyPointLight_hpp

#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyActor;

class MyPointLight: public MyActor {
public:
    static MyPointLight* create(void);
    
private:
    MyPointLight(void);
    ~MyPointLight(void) {}
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyPointLight_hpp */
