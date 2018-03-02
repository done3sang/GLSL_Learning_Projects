//
//  MyMatrix2.hpp
//  Mine
//
//  Created by xy on 23/02/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MyMatrix_hpp
#define MyMatrix_hpp

#include <initializer_list>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

// MyFMatrix2 interface

class MyFMatrix2 final {
public:
    MyFMatrix2(void);
    MyFMatrix2(float value);
    MyFMatrix2(float in00, float in01, float in10, float in11);
    MyFMatrix2(const std::initializer_list<float> &il);
    MyFMatrix2(const MyFMatrix2 &other);
    MyFMatrix2(const MyFMatrix2 &&other);
    ~MyFMatrix2(void);
    
    MyFMatrix2& operator=(const MyFMatrix2 &other);
    MyFMatrix2& operator=(const MyFMatrix2 &&other);
    MyFMatrix2& operator=(const std::initializer_list<float> &il);
    
    bool operator==(const MyFMatrix2 &other) const;
    bool operator!=(const MyFMatrix2 &other) const;
    
    MyFMatrix2& operator+=(const MyFMatrix2 &other);
    MyFMatrix2& operator-=(const MyFMatrix2 &other);
    
    MyFMatrix2& operator*=(float value);
    MyFMatrix2& operator/=(float value);
    
    MyFMatrix2& operator*=(const MyFMatrix2 &other);
    
    float& valueAt(int x, int y);
    const float& valueAt(int x, int y) const;
    
    float determinant(void) const;
    bool inversible(void) const;
    
public:
    static const MyFMatrix2 kIdentity;
    static const MyFMatrix2 kZero;
    
private:
    float _value[2][2];
};

MyFMatrix2 operator-(const MyFMatrix2 &mat);

MyFMatrix2 operator+(const MyFMatrix2 &lhs, const MyFMatrix2 &rhs);
MyFMatrix2 operator-(const MyFMatrix2 &lhs, const MyFMatrix2 &rhs);

MyFMatrix2 operator*(const MyFMatrix2 &mat, float value);
MyFMatrix2 operator*(float value, const MyFMatrix2 &mat);

MyFMatrix2 operator/(const MyFMatrix2 &mat, float value);

MyFMatrix2 operator*(const MyFMatrix2 &lhs, const MyFMatrix2 &rhs);

float* value_pointer(MyFMatrix2 &mat);
const float* value_pointer(const MyFMatrix2 &mat);

// MyFMatrix3 interface

class MyFMatrix3 final {
public:
    MyFMatrix3(void);
    MyFMatrix3(float value);
    MyFMatrix3(float in00, float in01, float in02,
               float in10, float in11, float in12,
               float in20, float in21, float in22);
    MyFMatrix3(const std::initializer_list<float> &il);
    MyFMatrix3(const MyFMatrix3 &other);
    MyFMatrix3(const MyFMatrix3 &&other);
    ~MyFMatrix3(void);
    
    MyFMatrix3& operator=(const MyFMatrix3 &other);
    MyFMatrix3& operator=(const MyFMatrix3 &&other);
    MyFMatrix3& operator=(const std::initializer_list<float> &il);
    
    bool operator==(const MyFMatrix3 &other) const;
    bool operator!=(const MyFMatrix3 &other) const;
    
    MyFMatrix3& operator+=(const MyFMatrix3 &other);
    MyFMatrix3& operator-=(const MyFMatrix3 &other);
    
    MyFMatrix3& operator*=(float value);
    MyFMatrix3& operator/=(float value);
    
    MyFMatrix3& operator*=(const MyFMatrix3 &other);
    
    float& valueAt(int x, int y);
    const float& valueAt(int x, int y) const;
    
    float determinant(void) const;
    bool inversible(void) const;
    
public:
    static const MyFMatrix3 kIdentity;
    static const MyFMatrix3 kZero;
    
private:
    float _value[3][3];
};

MyFMatrix3 operator-(const MyFMatrix3 &mat);

MyFMatrix3 operator+(const MyFMatrix3 &lhs, const MyFMatrix3 &rhs);
MyFMatrix3 operator-(const MyFMatrix3 &lhs, const MyFMatrix3 &rhs);

MyFMatrix3 operator*(const MyFMatrix3 &mat, float value);
MyFMatrix3 operator*(float value, const MyFMatrix3 &mat);

MyFMatrix3 operator/(const MyFMatrix3 &mat, float value);

MyFMatrix3 operator*(const MyFMatrix3 &lhs, const MyFMatrix3 &rhs);

float* value_pointer(MyFMatrix3 &mat);
const float* value_pointer(const MyFMatrix3 &mat);

// MyFMatrix4 interface

class MyFMatrix4 final {
public:
    MyFMatrix4(void);
    MyFMatrix4(float value);
    MyFMatrix4(float in00, float in01, float in02, float in03,
               float in10, float in11, float in12, float in13,
               float in20, float in21, float in22, float in23,
               float in30, float in31, float in32, float in33);
    MyFMatrix4(const std::initializer_list<float> &il);
    MyFMatrix4(const MyFMatrix4 &other);
    MyFMatrix4(const MyFMatrix4 &&other);
    ~MyFMatrix4(void);
    
    MyFMatrix4& operator=(const MyFMatrix4 &other);
    MyFMatrix4& operator=(const MyFMatrix4 &&other);
    MyFMatrix4& operator=(const std::initializer_list<float> &il);
    
    bool operator==(const MyFMatrix4 &other) const;
    bool operator!=(const MyFMatrix4 &other) const;
    
    MyFMatrix4& operator+=(const MyFMatrix4 &other);
    MyFMatrix4& operator-=(const MyFMatrix4 &other);
    
    MyFMatrix4& operator*=(float value);
    MyFMatrix4& operator/=(float value);
    
    MyFMatrix4& operator*=(const MyFMatrix4 &other);
    
    float& valueAt(int x, int y);
    const float& valueAt(int x, int y) const;
    
    float determinant(void) const;
    bool inversible(void) const;
    
public:
    static const MyFMatrix4 kIdentity;
    static const MyFMatrix4 kZero;
    
private:
    float _value[4][4];
};

MyFMatrix4 operator-(const MyFMatrix4 &mat);

MyFMatrix4 operator+(const MyFMatrix4 &lhs, const MyFMatrix4 &rhs);
MyFMatrix4 operator-(const MyFMatrix4 &lhs, const MyFMatrix4 &rhs);

MyFMatrix4 operator*(const MyFMatrix4 &mat, float value);
MyFMatrix4 operator*(float value, const MyFMatrix4 &mat);

MyFMatrix4 operator/(const MyFMatrix4 &mat, float value);

MyFMatrix4 operator*(const MyFMatrix4 &lhs, const MyFMatrix4 &rhs);

float* value_pointer(MyFMatrix4 &mat);
const float* value_pointer(const MyFMatrix4 &mat);

// basic operations of matrix
void zeroMatrix(MyFMatrix2 &mat);
void identityMatrix(MyFMatrix2 &mat);
void transposeMatrix(MyFMatrix2 &mat);
void transposeMatrix(const MyFMatrix2 &inMat, MyFMatrix2 &outMat);
MyFMatrix2 transposeMatrix(const MyFMatrix2 &mat);
bool inverseMatrix(const MyFMatrix2 &mat, MyFMatrix2 &invMat);
bool inverseMatrix(MyFMatrix2 &mat);

void zeroMatrix(MyFMatrix3 &mat);
void identityMatrix(MyFMatrix3 &mat);
void transposeMatrix(MyFMatrix3 &mat);
void transposeMatrix(const MyFMatrix3 &inMat, MyFMatrix3 &outMat);
MyFMatrix3 transposeMatrix(const MyFMatrix3 &mat);
bool inverseMatrix(const MyFMatrix3 &mat, MyFMatrix3 &invMat);
bool inverseMatrix(MyFMatrix3 &mat);

void zeroMatrix(MyFMatrix4 &mat);
void identityMatrix(MyFMatrix4 &mat);
void transposeMatrix(MyFMatrix4 &mat);
void transposeMatrix(const MyFMatrix4 &inMat, MyFMatrix4 &outMat);
MyFMatrix4 transposeMatrix(const MyFMatrix4 &mat);
bool inverseMatrix(const MyFMatrix4 &mat, MyFMatrix4 &invMat);
bool inverseMatrix(MyFMatrix4 &mat);

bool matrixOrthogonal(const MyFMatrix3 &mat);

MINE_NAMESPACE_END

#pragma GCC visibility pop

#include "MyMatrix.inl"

#endif /* MyMatrix_hpp */
