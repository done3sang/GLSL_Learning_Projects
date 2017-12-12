//
//  MySpotLight.hpp
//  MyGLSL
//
//  Created by xy on 12/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MySpotLight_hpp
#define MySpotLight_hpp

#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyActor;

class MySpotLight: public MyActor {
public:
    static MySpotLight* create(void);
    
private:
    MySpotLight(void);
    ~MySpotLight(void) {}
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MySpotLight_hpp */
