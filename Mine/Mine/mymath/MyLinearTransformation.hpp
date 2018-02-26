//
//  MyLinearTransformation.hpp
//  Mine
//
//  Created by xy on 24/02/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MyLinearTransformation_hpp
#define MyLinearTransformation_hpp

#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyStatic;
class MyFMatrix2;
class MyFMatrix3;
class MyFMatrix4;
class MyCoordinate;

class MyCoordinateTransition {
public:
    MyCoordinateTransition(void);
    MyCoordinateTransition(const MyCoordinate &coordA, const MyCoordinate &coordB);
    MyCoordinateTransition(const MyCoordinateTransition &other);
    MyCoordinateTransition(const MyCoordinateTransition &&other);
    ~MyCoordinateTransition(void);
    
    MyCoordinateTransition& operator=(const MyCoordinateTransition &other);
    MyCoordinateTransition& operator=(const MyCoordinateTransition &&other);
    
    bool operator==(const MyCoordinateTransition &other);
    bool operator!=(const MyCoordinateTransition &other);
    
    void transformVectorForward(const MyFVector3 &vecA, MyFVector3 &vecB);
    void transformVectorBackward(const MyFVector3 &vecB, MyFVector3 &vecA);
    
private:
    MyCoordinate _coordA;
    MyCoordinate _coordB;
    MyFMatrix3 _transitMatrix; // B = P * A
};

class MyLinearTransformation: private MyStatic {
public:
    static float magnitudeVector(const MyFVector2 &vec);
    static float magnitudeSquareVector(const MyFVector2 &vec);
    
    static float magnitudeVector(const MyFVector3 &vec);
    static float magnitudeSquareVector(const MyFVector3 &vec);
    
    static float magnitudeVector(const MyFVector4 &vec);
    static float magnitudeSquareVector(const MyFVector4 &vec);
    
    static MyFVector2 normalizeVector(const MyFVector2 &vec);
    static MyFVector2& normalizeVectorSelf(MyFVector2 &vec);
    
    static MyFVector3 normalizeVector(const MyFVector3 &vec);
    static MyFVector3& normalizeVectorSelf(MyFVector3 &vec);
    
    static MyFVector4 normalizeVector(const MyFVector4 &vec);
    static MyFVector4& normalizeVectorSelf(MyFVector4 &vec);
    
    static float dotProduct(const MyFVector2 &a, const MyFVector2 &b);
    static float dotProduct(const MyFVector3 &a, const MyFVector3 &b);
    static float dotProduct(const MyFVector4 &a, const MyFVector4 &b);
    
    static float radiusVector(const MyFVector2 &a, const MyFVector2 &b);
    static float radiusVector(const MyFVector3 &a, const MyFVector3 &b);
    static float radiusVector(const MyFVector4 &a, const MyFVector4 &b);
    
    static MyFVector3 projectVector(const MyFVector3 &x, const MyFVector3 &b);
    static MyFVector3& projectVectorSelf(MyFVector3 &a, const MyFVector3 &b);
    
    static MyFVector3 projectNormalizedVector(const MyFVector3 &x, const MyFVector3 &b);
    static MyFVector3& projectNormalizedVectorSelf(MyFVector3 &a, const MyFVector3 &b);
    
    static void zeroMatrix(MyFMatrix2 &mat);
    static void identityMatrix(MyFMatrix2 &mat);
    static MyFMatrix2 transposeMatrix(const MyFMatrix2 &mat);
    static MyFMatrix2& transposeMatrixSelf(MyFMatrix2 &mat);
    static bool inverseMatrix(MyFMatrix2 &mat, MyFMatrix2 &invMat);
    static bool inverseMatrixSelf(MyFMatrix2 &mat);
    
    static void zeroMatrix(MyFMatrix3 &mat);
    static void identityMatrix(MyFMatrix3 &mat);
    static MyFMatrix3 transposeMatrix(const MyFMatrix3 &mat);
    static MyFMatrix3& transposeMatrixSelf(MyFMatrix3 &mat);
    static bool inverseMatrix(MyFMatrix3 &mat, MyFMatrix3 &invMat);
    static bool inverseMatrixSelf(MyFMatrix3 &mat);
    
    static void zeroMatrix(MyFMatrix4 &mat);
    static void identityMatrix(MyFMatrix4 &mat);
    static MyFMatrix4 transposeMatrix(const MyFMatrix4 &mat);
    static MyFMatrix4& transposeMatrixSelf(MyFMatrix4 &mat);
    static bool inverseMatrix(MyFMatrix4 &mat, MyFMatrix4 &invMat);
    static bool inverseMatrixSelf(MyFMatrix4 &mat);
    
    static MyFVector2& transformVector(const MyFMatrix2 &mat, MyFVector2 &vec);
    static MyFVector3& transformVector(const MyFMatrix3 &mat, MyFVector3 &vec);
    static MyFVector4& transformVector(const MyFMatrix4 &mat, MyFVector4 &vec);
    
    static MyFMatrix2& rotateMatrix(MyFMatrix2 &mat, float radius);
    
    static MyFMatrix3& rotateMatrixByAxisX(MyFMatrix3 &mat, float radius);
    static MyFMatrix3& rotateMatrixByAxisY(MyFMatrix3 &mat, float radius);
    static MyFMatrix3& rotateMatrixByAxisZ(MyFMatrix3 &mat, float radius);
    static MyFMatrix3& rotateMatrixByAxis(MyFMatrix3 &mat,
                                          const MyFVector3 &vec,
                                          float radius);
    static MyFMatrix3& rotateMatrixByNormalizedAxis(MyFMatrix3 &mat,
                                                    const MyFVector3 &vec,
                                                    float radius);
    
    // coordinate
    static bool validateCoordinate(const MyCoordinate &coord);
    static bool validateCoordinate(const MyFVector3 &inX,
                                   const MyFVector3 &inY,
                                   const MyFVector3 &inZ);
    
    // B = A * P -> P = A ^ -1 * B
    static void transformCoordinateMatrix(const MyCoordinate &coordA,
                                          const MyCoordinate &coordB,
                                          MyFMatrix3 &mat);
    
    // B = A * P, x = A * a = B * b = A * P * b -> a = P * b -> b = P ^ -1 * a
    static void transformCoordinateVectorForward(const MyFMatrix3 &transitMat,
                                          const MyFVector3 &vecA,
                                          MyFVector3 &vecB);
    static void transformCoordinateVectorBackward(const MyFMatrix3 &transitMat,
                                                 const MyFVector3 &vecB,
                                                 MyFVector3 &vecA);
    
private:
    static void swapMatrixRow(MyFMatrix2 &mat,
                              int x,
                              int y,
                              int startIndex = 0);
    static void multiplyMatrixRow(MyFMatrix2 &mat,
                                  int x,
                                  float multiple,
                                  int startIndex = 0);
    static void substractMatrixRow(MyFMatrix2 &mat,
                                   int x,
                                   int y,
                                   float multiple,
                                   int startIndex = 0);
    static void swapMatrixColumn(MyFMatrix2 &mat,
                                 int x,
                                 int y,
                                 int startIndex = 0);
    static void multiplyMatrixColumn(MyFMatrix2 &mat,
                                     int x,
                                     float multiple,
                                     int startIndex = 0);
    static void substractMatrixColumn(MyFMatrix2 &mat,
                                      int x,
                                      int y,
                                      float multiple,
                                      int startIndex = 0);
    
    static void swapMatrixRow(MyFMatrix3 &mat,
                              int x,
                              int y,
                              int startIndex = 0);
    static void multiplyMatrixRow(MyFMatrix3 &mat,
                                  int x,
                                  float multiple,
                                  int startIndex = 0);
    static void substractMatrixRow(MyFMatrix3 &mat,
                                   int x,
                                   int y,
                                   float multiple,
                                   int startIndex = 0);
    static void swapMatrixColumn(MyFMatrix3 &mat,
                                 int x,
                                 int y,
                                 int startIndex = 0);
    static void multiplyMatrixColumn(MyFMatrix3 &mat,
                                     int x,
                                     float multiple,
                                     int startIndex = 0);
    static void substractMatrixColumn(MyFMatrix3 &mat,
                                      int x,
                                      int y,
                                      float multiple,
                                      int startIndex = 0);
    
    static void swapMatrixRow(MyFMatrix4 &mat,
                              int x,
                              int y,
                              int startIndex = 0);
    static void multiplyMatrixRow(MyFMatrix4 &mat,
                                  int x,
                                  float multiple,
                                  int startIndex = 0);
    static void substractMatrixRow(MyFMatrix4 &mat,
                                   int x,
                                   int y,
                                   float multiple,
                                   int startIndex = 0);
    static void swapMatrixColumn(MyFMatrix4 &mat,
                                 int x,
                                 int y,
                                 int startIndex = 0);
    static void multiplyMatrixColumn(MyFMatrix4 &mat,
                                     int x,
                                     float multiple,
                                     int startIndex = 0);
    static void substractMatrixColumn(MyFMatrix4 &mat,
                                      int x,
                                      int y,
                                      float multiple,
                                      int startIndex = 0);
    
    template<class M, int D>
    static bool metaInverseMatrix(M &mat, M &invMat);
    template<class M, int D>
    static bool metaInverseMatrixSelf(M &mat);
};

MyFVector2 operator*(const MyFMatrix2 &mat, const MyFVector2 &vev);

MyFVector3 operator*(const MyFMatrix3 &mat, const MyFVector3 &vec);

MyFVector4 operator*(const MyFMatrix4 &mat, const MyFVector4 &vec);

MINE_NAMESPACE_END

#pragma GCC visibility pop

#include "MyLinearTransformation.inl"

#endif /* MyLinearTransformation_hpp */
