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
    MyFVector3(const MyFVector2& vec2);
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
    MyFVector4(const MyFVector3& vec2);
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

// basic operation of vector
float magnitudeSquareVector(const MyFVector2 &vec);
float magnitudeVector(const MyFVector2 &vec);

float magnitudeSquareVector(const MyFVector3 &vec);
float magnitudeVector(const MyFVector3 &vec);

float magnitudeSquareVector(const MyFVector4 &vec);
float magnitudeVector(const MyFVector4 &vec);

void normalizeVector(MyFVector2 &vec);
void normalizeVector(const MyFVector2 &inVec, MyFVector2 &outVec);
bool vectorNormalized(const MyFVector2 &vec);
MyFVector2 normalizeVector(const MyFVector2 &vec);

void normalizeVectorSelf(MyFVector3 &vec);
void normalizeVector(const MyFVector3 &inVec, MyFVector3 &outVec);
bool vectorNormalized(const MyFVector3 &vec);
MyFVector3 normalizeVector(const MyFVector3 &vec);

void normalizeVectorSelf(MyFVector4 &vec);
void normalizeVector(const MyFVector4 &inVec, MyFVector4 &outVec);
bool vectorNormalized(const MyFVector4 &vec);
MyFVector4 normalizeVector(const MyFVector4 &vec);

float dotProduct(const MyFVector2 &a, const MyFVector2 &b);
float dotProduct(const MyFVector3 &a, const MyFVector3 &b);
float dotProduct(const MyFVector4 &a, const MyFVector4 &b);

void crossProduct(const MyFVector3 &a, const MyFVector3 &b, MyFVector3 &outVec);

float radiusVector(const MyFVector2 &a, const MyFVector2 &b);
float radiusVector(const MyFVector3 &a, const MyFVector3 &b);
float radiusVector(const MyFVector4 &a, const MyFVector4 &b);

void projectVector(MyFVector3 &a, const MyFVector3 &b);
void projectVector(const MyFVector3 &a, const MyFVector3 &b, MyFVector3 &outVec);
MyFVector3 projectVector(const MyFVector3 &a, const MyFVector3 &b);

void projectNormalizedVector(MyFVector3 &a, const MyFVector3 &b);
void projectNormalizedVector(const MyFVector3 &a,
                             const MyFVector3 &b,
                             MyFVector3 &outVec);
MyFVector3 projectNormalizedVector(const MyFVector3 &a, const MyFVector3 &b);

void perpendicularVector(MyFVector3 &a, const MyFVector3 &b);
void perpendicularVector(const MyFVector3 &a,
                         const MyFVector3 &b,
                         MyFVector3 &outVec);
MyFVector3 perpendicularVector(const MyFVector3 &a, const MyFVector3 &b);

void perpendicularNormalizedVector(MyFVector3 &a, const MyFVector3 &b);
void perpendicularNormalizedVector(const MyFVector3 &a,
                                   const MyFVector3 &b,
                                   MyFVector3 &outVec);
MyFVector3 perpendicularNormalizedVector(const MyFVector3 &a,
                                         const MyFVector3 &b);

void partitionVector(const MyFVector3 &a,
                     const MyFVector3 &b,
                     MyFVector3 &projVec,
                     MyFVector3 &perpVec);

void partitionNormalizedVector(const MyFVector3 &a,
                               const MyFVector3 &b,
                               MyFVector3 &projVec,
                               MyFVector3 &perpVec);

void schmidtVector(MyFVector3 &a,
                   MyFVector3 &b,
                   MyFVector3 &c);

bool vectorOrthogonal(const MyFVector2 &vec1, const MyFVector2 &vec2);
bool vectorOrthogonal(const MyFVector3 &vec1, const MyFVector3 &vec2);
bool vectorOrthogonal(const MyFVector4 &vec1, const MyFVector4 &vec2);

float distanceSquareVector(const MyFVector2 &a, const MyFVector2 &b);
float distanceSquareVector(const MyFVector3 &a, const MyFVector3 &b);
float distanceSquareVector(const MyFVector4 &a, const MyFVector4 &b);

float distanceVector(const MyFVector2 &a, const MyFVector2 &b);
float distanceVector(const MyFVector3 &a, const MyFVector3 &b);
float distanceVector(const MyFVector4 &a, const MyFVector4 &b);

MINE_NAMESPACE_END

#pragma GCC visibility pop

#include "MyVector.inl"

#endif /* MyVector_hpp */
