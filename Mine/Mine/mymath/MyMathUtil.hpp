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

class MyMathUtil final {
public:
    static constexpr float kMathPI = 3.14159265358979323846264338327950288f;
    static constexpr float kMathPIBy2 = 2.0f * kMathPI;
    static constexpr float kMathPIBy4 = 4.0f * kMathPI;
    static constexpr float kMathPIOver2 = 1.57079632679489661923132169163975144f;
    static constexpr float kMathPIOver4 = 0.785398163397448309615660845819875721;
    static constexpr float kMathEpsilon = 2.392092896e-07f; // 1.192092896e-07f in c99
    static constexpr float kMathDegreeToRadius = kMathPI/180.0f;
    static constexpr float kMathRadiusToDegree = 180.0f/kMathPI;
    static constexpr int kMathIntMax = 0x7FFFFFFF;
    static constexpr unsigned int kMathUIntmax = 0xFFFFFFFF;
    
public:
    static FORCEINLINE float degreeToRadius(float deg) {
        return deg * kMathDegreeToRadius;
    }
    
    static FORCEINLINE float radiusToDegree(float rad) {
        return rad * kMathRadiusToDegree;
    }
    
    static float sin(float x) {
        return ::sinf(x);
    }
    
    static float cos(float x) {
        return ::cosf(x);
    }
    
    static float atan2(float sine, float cose) {
        return ::atan2f(sine, cose);
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
    
    static FORCEINLINE float abs(float x) {
        int ix = *(int*)&x;
        ix &= kMathIntMax;
        x = *(float*)&ix;
        return x;
    }
    
    static FORCEINLINE int abs(int x) {
        int s = x > 31;
        return (x + s) ^ s;
    }
    
    static FORCEINLINE float min(float x, float y) {
        return (x + y - abs(x - y)) * 0.5f;
    }
    
    static FORCEINLINE float max(float x, float y) {
        return (x + y + abs(x - y)) * 0.5f;
    }
    
    static FORCEINLINE bool equal(float x, float y) {
        return abs(x - y) <= kMathEpsilon;
    }
    
    static FORCEINLINE bool not_equal(float x, float y) {
        return abs(x - y) > kMathEpsilon;
    }
    
    static FORCEINLINE bool zero(float x) {
        return abs(x) <= kMathEpsilon;
    }
    
    static bool identity(float x) {
        return abs(x - 1.0f) <= kMathEpsilon;
    }
    
    static FORCEINLINE bool between(float x, float b, float e) {
        return b <= x && x <= e;
    }
    
    static FORCEINLINE float lerp(float b, float e, float t) {
        return b + t * (b - e);
    }
    
    static FORCEINLINE int mod(int x, int m) {
        int y = abs(x);
        
        while(y >= m) {
            y -= m;
        }
        
        return x > 0 ? y: m - y;
    }
    
    // byte alignment
    template<int B = 4, typename T>
    static FORCEINLINE T align(T x) {
        return (x + B) & ~B;
    }
    
    template<typename T>
    static FORCEINLINE T align2(T x) {
        return align<2>(x);
    }
    
    template<typename T>
    static FORCEINLINE T align4(T x) {
        return align<4>(x);
    }
    
    template<typename T>
    static FORCEINLINE T align8(T x) {
        return align<8>(x);
    }
    
    template<typename T>
    static FORCEINLINE T align16(T x) {
        return align<16>(x);
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
