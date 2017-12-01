//
//  MyGLSL.hpp
//  MyGLSL
//
//  Created by xy on 27/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyGLSL_
#define MyGLSL_

#include "Precompiled.h"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MySingleton;

class MyGLSL: public MySingleton {
public:
    static MyGLSL* sharedGLSL(void);
    
    void closeGLSL(void);
    
private:
    MyGLSL(void) {}
    ~MyGLSL(void);
    
    static MyGLSL *_shardeGLSL;
    
    void initialize(void);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif
