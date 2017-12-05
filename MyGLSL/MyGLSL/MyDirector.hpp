//
//  MyDirector.hpp
//  MyGLSL
//
//  Created by xy on 05/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyDirector_hpp
#define MyDirector_hpp

#include "Precompiled.h"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MySingleton;

class MyDirector: public MySingleton {
public:
    static MyDirector* sharedDirector(void);
    
private:
    static MyDirector* _sharedDirector;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyDirector_hpp */
