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

class MyMathUtil final: private MyStatic {
public:
    static constexpr float kMathPI = 3.14159265358979323846264338327950288f;
    static constexpr float kMathPIBy2 = 2.0f * kMathPI;
    static constexpr float kMathPIBy4 = 4.0f * kMathPI;
    static constexpr float kMathPIOver2 = 1.57079632679489661923132169163975144f;
    static constexpr float kMathPIOver4 = 0.785398163397448309615660845819875721;
    
public:
    static float sin(float rad) {
        return ::sin(rad);
    }
    
    static float cos(float rad) {
        return ::cos(rad);
    }
    
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyMathUtil_hpp */
