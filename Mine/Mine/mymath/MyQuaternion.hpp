//
//  MyQuaternion.hpp
//  Mine
//
//  Created by xy on 01/03/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MyQuaternion_hpp
#define MyQuaternion_hpp

#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyFQuaternion final {
public:
    MyFQuaternion(void);
    MyFQuaternion(float inW);
    MyFQuaternion(float inW, float inX, float inY, float inZ);
    MyFQuaternion(const MyFQuaternion &other);
    MyFQuaternion(const MyFQuaternion &&other);
    ~MyFQuaternion(void);
    
    MyFQuaternion& operator=(const MyFQuaternion &other);
    MyFQuaternion& operator=(const MyFQuaternion &&other);
    
    bool operator==(const MyFQuaternion &other) const;
    bool operator!=(const MyFQuaternion &other) const;
    
    MyFQuaternion& operator*=(float value);
    MyFQuaternion& operator/=(float value);
    
    MyFQuaternion& operator*=(const MyFQuaternion &other);
    
public:
    float w;
    float x;
    float y;
    float z;
};

MyFQuaternion operator-(const MyFQuaternion &quat);
MyFQuaternion operator*(const MyFQuaternion &lhs, const MyFQuaternion &rhs);
MyFQuaternion operator*(const MyFQuaternion &quat, float value);
MyFQuaternion operator*(float value, const MyFQuaternion &quat);
MyFQuaternion operator/(const MyFQuaternion &quat, float value);

void identityQuaternion(MyFQuaternion &quat);
void zeroQuaternion(MyFQuaternion &quat);

float magnitudeSquareQuaternion(const MyFQuaternion &quat);
float magnitudeQuaternion(const MyFQuaternion &quat);

bool quaternionNormalized(const MyFQuaternion &quat);
void normalizeQuaternion(MyFQuaternion &quat);
void normalizeQuaternion(const MyFQuaternion &quat, MyFQuaternion &outQuat);
MyFQuaternion normalizeQuaternion(const MyFQuaternion &quat);

void conjugateQuaternion(MyFQuaternion &quat);
void conjugateQuaternion(const MyFQuaternion &quat, MyFQuaternion &outQuat);
MyFQuaternion conjugateQuaternion(const MyFQuaternion &quat);

void inverseQuaternion(MyFQuaternion &quat);
void inverseQuaternion(const MyFQuaternion &quat, MyFQuaternion &outQuat);
MyFQuaternion inverseQuaternion(const MyFQuaternion &quat);

void inverseNormalizedQuaternion(MyFQuaternion &quat);
void inverseNormalizedQuaternion(const MyFQuaternion &quat,
                                 MyFQuaternion &outQuat);
MyFQuaternion inverseNormalizedQuaternion(const MyFQuaternion &quat);

float dotProduct(const MyFQuaternion &lhs, const MyFQuaternion &rhs);

void crossProduct(const MyFQuaternion &lhs,
                  const MyFQuaternion &rhs,
                  MyFQuaternion &outQuat);

void differQuaternion(const MyFQuaternion &begQuat,
                      const MyFQuaternion &endQuat,
                      MyFQuaternion &outQuat);
MyFQuaternion differQuaternion(const MyFQuaternion &begQuat,
                               const MyFQuaternion &endQuat);

void logQuaternion(const MyFQuaternion &quat, MyFQuaternion &outQuat);
MyFQuaternion logQuaternion(const MyFQuaternion &quat);

void expQuaternion(const MyFQuaternion &quat, MyFQuaternion &outQuat);
MyFQuaternion expQuaternion(const MyFQuaternion &quat);

void powerQuaternion(const MyFQuaternion &quat,
                     float power,
                     MyFQuaternion &outQuat);
MyFQuaternion powerQuaternion(const MyFQuaternion &quat, float power);

void slerpQuaternion(const MyFQuaternion &begQuat,
                     const MyFQuaternion &endQuat,
                     float t,
                     MyFQuaternion &outQuat);
MyFQuaternion slerpQuaternion(const MyFQuaternion &begQuat,
                              const MyFQuaternion &endQuat,
                              float t);

MINE_NAMESPACE_END

#pragma GCC visibility pop

#include "MyQuaternion.inl"

#endif /* Quaternion_hpp */
