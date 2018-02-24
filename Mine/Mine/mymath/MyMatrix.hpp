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
    
    //float& valueAt(constexpr int x, constexpr int y);
    //const float& valueAt(const int x, constexpr int y);
    
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

void zeroMatrix(MyFMatrix2 &mat);
void identityMatrix(MyFMatrix2 &mat);
MyFMatrix2 transposeMatrix(const MyFMatrix2 &mat);
MyFMatrix2& transposeMatrixSelf(MyFMatrix2 &mat);
MyFMatrix2 inverseMatrix(const MyFMatrix2 &mat);
MyFMatrix2& inverseMatrixSelf(MyFMatrix2 &mat);

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
    
    //float& valueAt(constexpr int x, constexpr int y);
    //const float& valueAt(const int x, constexpr int y);
    
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

void zeroMatrix(MyFMatrix3 &mat);
void identityMatrix(MyFMatrix3 &mat);
MyFMatrix3 transposeMatrix(const MyFMatrix3 &mat);
MyFMatrix3& transposeMatrixSelf(MyFMatrix3 &mat);
MyFMatrix3 inverseMatrix(const MyFMatrix3 &mat);
MyFMatrix3& inverseMatrixSelf(MyFMatrix3 &mat);

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
    
    //float& valueAt(constexpr int x, constexpr int y);
    //const float& valueAt(const int x, constexpr int y);
    
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

void zeroMatrix(MyFMatrix4 &mat);
void identityMatrix(MyFMatrix4 &mat);
MyFMatrix4 transposeMatrix(const MyFMatrix4 &mat);
MyFMatrix4& transposeMatrixSelf(MyFMatrix4 &mat);
//MyFMatrix4 inverseMatrix(const MyFMatrix4 &mat);
//MyFMatrix4& inverseMatrixSelf(MyFMatrix4 &mat);

float* value_pointer(MyFMatrix4 &mat);
const float* value_pointer(const MyFMatrix4 &mat);

MINE_NAMESPACE_END

#pragma GCC visibility pop

#include "MyMatrix.inl"

#endif /* MyMatrix_hpp */
