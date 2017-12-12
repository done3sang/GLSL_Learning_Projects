//
//  MyMathUtil.hpp
//  MyGLSL
//
//  Created by xy on 12/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyMathUtil_hpp
#define MyMathUtil_hpp

#include <cmath>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyStatic;

class MyMathUtil: private MyStatic {
public:
    static float sinf(float rad) {
        return ::sin(rad);
    }
    
    static float cosf(float rad) {
        return ::cos(rad);
    }
    
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyMathUtil_hpp */
