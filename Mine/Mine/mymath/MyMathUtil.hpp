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

class MyMathUtil final {
public:
    static constexpr float kMathPI = 3.14159265358979323846264338327950288f;
    static constexpr float kMathPIBy2 = 2.0f * kMathPI;
    static constexpr float kMathPIBy4 = 4.0f * kMathPI;
    static constexpr float kMathPIOver2 = 1.57079632679489661923132169163975144f;
    static constexpr float kMathPIOver4 = 0.785398163397448309615660845819875721;
    static constexpr float kMathEpsilon = 1.192092896e-07f;
    
public:
    static float sin(float x) {
        return ::sinf(x);
    }
    
    static float cos(float x) {
        return ::cosf(x);
    }
    
    static float asin(float x) {
        return ::asinf(x);
    }
    
    static float acos(float x) {
        return ::acosf(x);
    }
    
    static float sqrt(float x) {
        return ::sqrtf(x);
    }
    
    static float abs(float x) {
        return ::fabsf(x);
    }
    
    static bool equal(float x, float y) {
        return abs(x - y) <= kMathEpsilon;
    }
    
    static bool zero(float x) {
        return abs(x) <= kMathEpsilon;
    }
    
    static bool identity(float x) {
        return abs(x - 1.0f) <= kMathEpsilon;
    }
    
public:
    MyMathUtil(void) = delete;
    MyMathUtil(const MyMathUtil&) = delete;
    MyMathUtil(MyMathUtil&&) = delete;
    ~MyMathUtil(void) = delete;
    
    MyMathUtil& operator=(const MyMathUtil&) = delete;
    MyMathUtil& operator=(MyMathUtil&&) = delete;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyMathUtil_hpp */
