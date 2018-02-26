//
//  MyFVector.hpp
//  Mine
//
//  Created by xy on 23/02/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MyVector_hpp
#define MyVector_hpp

#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

// MyFVector2 interface

class MyFVector2 final {
public:
    MyFVector2(void);
    MyFVector2(float value);
    MyFVector2(float vx, float vy);
    MyFVector2(const MyFVector2 &other);
    MyFVector2(const MyFVector2 &&other);
    ~MyFVector2(void);
    
    MyFVector2& operator=(const MyFVector2 &other);
    MyFVector2& operator=(const MyFVector2 &&other);
    
    bool operator==(const MyFVector2 &other) const;
    bool operator!=(const MyFVector2 &other) const;
    
    MyFVector2& operator+=(const MyFVector2 &other);
    MyFVector2& operator-=(const MyFVector2 &other);
    
    MyFVector2& operator*=(float value);
    MyFVector2& operator/=(float value);
    
public:
    static const MyFVector2 kFVector2AxisX;
    static const MyFVector2 kFVector2AxisY;
    
public:
    float x;
    float y;
};

MyFVector2 operator-(const MyFVector2 &v);

MyFVector2 operator+(const MyFVector2 &lhs, const MyFVector2 &rhs);
MyFVector2 operator-(const MyFVector2 &lhs, const MyFVector2 &rhs);

MyFVector2 operator*(const MyFVector2 &v, float value);
MyFVector2 operator*(float value, const MyFVector2 &v);

MyFVector2 operator/(const MyFVector2 &v, float value);

float* value_pointer(MyFVector2 &v);
const float* value_pointer(const MyFVector2 &v);

// MyFVector3 interface

class MyFVector3 final {
public:
    MyFVector3(void);
    MyFVector3(float value);
    MyFVector3(float vx, float vy, float vz);
    MyFVector3(const MyFVector3 &other);
    MyFVector3(const MyFVector3 &&other);
    ~MyFVector3(void);
    
    MyFVector3& operator=(const MyFVector3 &other);
    MyFVector3& operator=(const MyFVector3 &&other);
    
    bool operator==(const MyFVector3 &other) const;
    bool operator!=(const MyFVector3 &other) const;
    
    MyFVector3& operator+=(const MyFVector3 &other);
    MyFVector3& operator-=(const MyFVector3 &other);
    
    MyFVector3& operator*=(float value);
    MyFVector3& operator/=(float value);
    
    MyFVector3& operator*=(const MyFVector3 &other);
    
public:
    static const MyFVector3 kFVector3AxisX;
    static const MyFVector3 kFVector3AxisY;
    static const MyFVector3 kFVector3AxisZ;
    
public:
    float x;
    float y;
    float z;
};

MyFVector3 operator-(const MyFVector3 &v);

MyFVector3 operator+(const MyFVector3 &lhs, const MyFVector3 &rhs);
MyFVector3 operator-(const MyFVector3 &lhs, const MyFVector3 &rhs);

MyFVector3 operator*(const MyFVector3 &v, float value);
MyFVector3 operator*(float value, const MyFVector3 &v);

MyFVector3 operator/(const MyFVector3 &v, float value);
MyFVector3 operator*(const MyFVector3 &lhs, const MyFVector3 &rhs);

float* value_pointer(MyFVector3 &v);
const float* value_pointer(const MyFVector3 &v);

// MyFVector4 interface

class MyFVector4 final {
public:
    MyFVector4(void);
    MyFVector4(float value);
    MyFVector4(float vx,
              float vy,
              float vz,
              float vw);
    MyFVector4(const MyFVector4 &other);
    MyFVector4(const MyFVector4 &&other);
    ~MyFVector4(void);
    
    MyFVector4& operator=(const MyFVector4 &other);
    MyFVector4& operator=(const MyFVector4 &&other);
    
    bool operator==(const MyFVector4 &other) const;
    bool operator!=(const MyFVector4 &other) const;
    
    MyFVector4& operator+=(const MyFVector4 &other);
    MyFVector4& operator-=(const MyFVector4 &other);
    
    MyFVector4& operator*=(float value);
    MyFVector4& operator/=(float value);
    
public:
    static const MyFVector4 kFVector4AxisX;
    static const MyFVector4 kFVector4AxisY;
    static const MyFVector4 kFVector4AxisZ;
    static const MyFVector4 kFVector4AxisW;
    
public:
    float x;
    float y;
    float z;
    float w;
};

MyFVector4 operator-(const MyFVector4 &v);

MyFVector4 operator+(const MyFVector4 &lhs, const MyFVector4 &rhs);
MyFVector4 operator-(const MyFVector4 &lhs, const MyFVector4 &rhs);

MyFVector4 operator*(const MyFVector4 &v, float value);
MyFVector4 operator*(float value, const MyFVector4 &v);

MyFVector4 operator/(const MyFVector4 &v, float value);

float* value_pointer(MyFVector4 &v);
const float* value_pointer(const MyFVector4 &v);

MINE_NAMESPACE_END

#pragma GCC visibility pop

#include "MyVector.inl"

#endif /* MyVector_hpp */
