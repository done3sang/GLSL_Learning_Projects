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

class MyFMatrix2;
class MyFMatrix3;
class MyFMatrix4;
class MyFQuaternion;
class MyPlane;
class MyCoordinate;
class MyCoordinateTransition;

class MyTransformation {
public:
    // transformation of matrix and vector
    static void transformVector(const MyFMatrix2 &mat, MyFVector2 &vec);
    static void transformVector(const MyFMatrix3 &mat, MyFVector3 &vec);
    static void transformVector(const MyFMatrix4 &mat, MyFVector4 &vec);
    static void transformVector(const MyFMatrix2 &mat,
                                       const MyFVector2 &inVec,
                                       MyFVector2 &outVec);
    static void transformVector(const MyFMatrix3 &mat,
                                const MyFVector3 &inVec,
                                MyFVector3 &outVec);
    static void transformVector(const MyFMatrix4 &mat,
                                const MyFVector4 &inVec,
                                MyFVector4 &outVec);
    
    // rotation
    static MyFMatrix2& rotateMatrix(MyFMatrix2 &mat, float radius);
    
    static MyFMatrix3& rotateMatrixByAxisX(MyFMatrix3 &mat, float radius);
    static MyFMatrix3& rotateMatrixByAxisY(MyFMatrix3 &mat, float radius);
    static MyFMatrix3& rotateMatrixByAxisZ(MyFMatrix3 &mat, float radius);
    static MyFMatrix4& rotateMatrixByAxisZ(MyFMatrix4 &mat, float radius);
    static MyFMatrix3& rotateMatrixByAxis(MyFMatrix3 &mat,
                                          const MyFVector3 &vec,
                                          float radius);
    static MyFMatrix3& rotateMatrixByNormalizedAxis(MyFMatrix3 &mat,
                                                    const MyFVector3 &vec,
                                                    float radius);
    
    // scale
    static MyFMatrix2& scaleMatrix(MyFMatrix2 &mat, float scalar);
    static MyFMatrix3& scaleMatrix(MyFMatrix3 &mat, float scalar);
    static MyFMatrix3& scaleMatrix(MyFMatrix3 &mat, const MyFVector3 &axis);
    static MyFMatrix4& scaleMatrix(MyFMatrix4 &mat, const MyFVector3 &axis);
    static MyFMatrix3& scaleMatrix(MyFMatrix3 &mat, const MyFVector3 &axis, float scalar);
    
    // orthogonal
    static MyFMatrix3& orthogonalMatrixByPlaneXY(MyFMatrix3 &mat);
    static MyFMatrix3& orthogonalMatrixByPlaneYZ(MyFMatrix3 &mat);
    static MyFMatrix3& orthogonalMatrixByPlaneZX(MyFMatrix3 &mat);
    static MyFMatrix3& orthogonalMatrix(MyFMatrix3 &mat, const MyPlane &plane);
    
    // mirror
    static MyFMatrix3& mirrorMatrixByPlaneXY(MyFMatrix3 &mat);
    static MyFMatrix3& mirrorMatrixByPlaneYZ(MyFMatrix3 &mat);
    static MyFMatrix3& mirrorMatrixByPlaneZX(MyFMatrix3 &mat);
    static MyFMatrix3& mirrorMatrix(MyFMatrix3 &mat, const MyPlane &plane);
    
    // shear
    static MyFMatrix3& shearMatrixByAxisX(MyFMatrix3 &mat, float s, float t);
    static MyFMatrix3& shearMatrixByAxisY(MyFMatrix3 &mat, float s, float t);
    static MyFMatrix3& shearMatrixByAxisZ(MyFMatrix3 &mat, float s, float t);
    
    // translation
    static MyFMatrix4& translateMatrix(MyFMatrix4 &mat, const MyFVector3 &vec);
    static MyFMatrix4& translateMatrix(MyFMatrix4 &mat, float x, float y, float z);
    
    // perspective
    static MyFMatrix4& perspectiveMatrix(MyFMatrix4 &mat, float zd);
    
    // coordinate
    static void transformCoordianteVectorForward(const MyCoordinateTransition &coordTransit,
                                          const MyFVector3 &vecA,
                                          MyFVector3 &vecB);
    static void transformCoordianteVectorBackward(const MyCoordinateTransition &coordTransit,
                                          const MyFVector3 &vecB,
                                          MyFVector3 &vecA);
    
    // quateranion
    static MyFQuaternion& rotateQuaternionByAxisX(MyFQuaternion &quat, float radius);
    static MyFQuaternion& rotateQuaternionByAxisY(MyFQuaternion &quat, float radius);
    static MyFQuaternion& rotateQuaternionByAxisZ(MyFQuaternion &quat, float radius);
    static MyFQuaternion& rotateQuaternionByAxis(MyFQuaternion &quat,
                                           const MyFVector3 &axis,
                                           float radius);
    static void quaternionVectorForward(const MyFQuaternion &quat, MyFVector3 &vec);
    static void quaternionVectorBackward(const MyFQuaternion &quat, MyFVector3 &vec);
    static void quaternionVectorForward(const MyFQuaternion &quat,
                                        const MyFVector3 &inVec,
                                        MyFVector3 &outVec);
    static void quaternionVectorBackward(const MyFQuaternion &quat,
                                         const MyFVector3 &inVec,
                                         MyFVector3 &outVec);
    
    // transition between matrix and quaternion
    static void quaternionToMatrix(const MyFQuaternion &quat, MyFMatrix3 &mat);
    static void matrixToQuaternion(const MyFMatrix3 &mat, MyFQuaternion &quat);
    
    static void quaternionToMatrix(const MyFQuaternion &quat, MyFMatrix4 &mat);
    static void matrixToQuaternion(const MyFMatrix4 &mat, MyFQuaternion &quat);
    
public:
    MyTransformation(void) = delete;
    MyTransformation(const MyTransformation&) = delete;
    MyTransformation(MyTransformation&&) = delete;
    ~MyTransformation(void) = delete;
    
    MyTransformation& operator=(const MyTransformation&) = delete;
    MyTransformation& operator=(MyTransformation&&) = delete;
};

MyFVector2 operator*(const MyFMatrix2 &mat, const MyFVector2 &vev);
MyFVector3 operator*(const MyFMatrix3 &mat, const MyFVector3 &vec);
MyFVector4 operator*(const MyFMatrix4 &mat, const MyFVector4 &vec);

MINE_NAMESPACE_END

#pragma GCC visibility pop

#include "MyTransformation.inl"

#endif /* MyLinearTransformation_hpp */
