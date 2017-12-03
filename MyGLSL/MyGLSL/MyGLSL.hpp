//
//  MyGLSL.hpp
//  MyGLSL
//
//  Created by xy on 27/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyGLSL_
#define MyGLSL_

#include <string>
#include "Precompiled.h"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MySingleton;

class MyGLSL: public MySingleton {
public:
    static MyGLSL* sharedGLSL(void);
    
    bool checkOpenGLError();
    int errCode(void) const { return _errCode; }
    const std::string& errDesc(void) const { return _errDesc; }
    
    void closeGLSL(void);
    
private:
    MyGLSL(void) {}
    ~MyGLSL(void);
    
    int _errCode;
    std::string _errDesc;
    
    static MyGLSL *_shardeGLSL;
    
    void initialize(void);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif
