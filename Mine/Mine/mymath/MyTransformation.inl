//
//  MyTransformation.inl
//  Mine
//
//  Created by xy on 24/02/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#include "MyVector.hpp"
#include "MyMatrix.hpp"
#include "MyCoordinate.hpp"
#include "MyPlane.hpp"

MINE_NAMESPACE_BEGIN

FORCEINLINE void MyTransformation::transformVector(const MyFMatrix2 &mat,
                                                         MyFVector2 &vec) {
    float y = mat.valueAt(1, 0) * vec.x + mat.valueAt(1, 1) * vec.y;
    vec.x = mat.valueAt(0, 0) * vec.x + mat.valueAt(0, 1) * vec.y;
    vec.y = y;
}

FORCEINLINE void MyTransformation::transformVector(const MyFMatrix3 &mat,
                                                         MyFVector3 &vec) {
    float y = mat.valueAt(1, 0) * vec.x + mat.valueAt(1, 1) * vec.y + mat.valueAt(1, 2) * vec.z;
    float z = mat.valueAt(2, 0) * vec.x + mat.valueAt(2, 1) * vec.y + mat.valueAt(2, 2) * vec.z;
    vec.x = mat.valueAt(0, 0) * vec.x + mat.valueAt(0, 1) * vec.y + mat.valueAt(0, 2) * vec.z;
    vec.y = y;
    vec.z = z;
}

FORCEINLINE void MyTransformation::transformVector(const MyFMatrix4 &mat,
                                                         MyFVector4 &vec) {
    float y = mat.valueAt(1, 0) * vec.x + mat.valueAt(1, 1) * vec.y + mat.valueAt(1, 2) * vec.z + mat.valueAt(1, 3) * vec.w;
    float z = mat.valueAt(2, 0) * vec.x + mat.valueAt(2, 1) * vec.y + mat.valueAt(2, 2) * vec.z + mat.valueAt(2, 3) * vec.w;
    float w = mat.valueAt(3, 0) * vec.x + mat.valueAt(3, 1) * vec.y + mat.valueAt(3, 2) * vec.z + mat.valueAt(3, 3) * vec.w;
    vec.x = mat.valueAt(0, 0) * vec.x + mat.valueAt(0, 1) * vec.y + mat.valueAt(0, 2) * vec.z + mat.valueAt(0, 3) * vec.w;;
    vec.y = y;
    vec.z = z;
    vec.w = w;
}

FORCEINLINE void MyTransformation::transformVector(const MyFMatrix2 &mat,
                                                         const MyFVector2 &inVec,
                                                         MyFVector2 &outVec) {
    outVec.x = mat.valueAt(0, 0) * inVec.x + mat.valueAt(0, 1) * inVec.y;
    outVec.y = mat.valueAt(1, 0) * inVec.x + mat.valueAt(1, 1) * inVec.y;
}

FORCEINLINE void MyTransformation::transformVector(const MyFMatrix3 &mat,
                                                         const MyFVector3 &inVec,
                                                         MyFVector3 &outVec) {
    outVec.y = mat.valueAt(1, 0) * inVec.x + mat.valueAt(1, 1) * inVec.y + mat.valueAt(1, 2) * inVec.z;
    outVec.z = mat.valueAt(2, 0) * inVec.x + mat.valueAt(2, 1) * inVec.y + mat.valueAt(2, 2) * inVec.z;
    outVec.x = mat.valueAt(0, 0) * inVec.x + mat.valueAt(0, 1) * inVec.y + mat.valueAt(0, 2) * inVec.z;
}

FORCEINLINE void MyTransformation::transformVector(const MyFMatrix4 &mat,
                                                         const MyFVector4 &inVec,
                                                         MyFVector4 &outVec) {
    outVec.x = mat.valueAt(0, 0) * inVec.x + mat.valueAt(0, 1) * inVec.y +
    mat.valueAt(0, 2) * inVec.z + mat.valueAt(0, 3) * inVec.w;
    outVec.y = mat.valueAt(1, 0) * inVec.x + mat.valueAt(1, 1) * inVec.y +
    mat.valueAt(1, 2) * inVec.z + mat.valueAt(1, 3) * inVec.w;
    outVec.z = mat.valueAt(2, 0) * inVec.x + mat.valueAt(2, 1) * inVec.y +
    mat.valueAt(2, 2) * inVec.z + mat.valueAt(2, 3) * inVec.w;
    outVec.w = mat.valueAt(3, 0) * inVec.x + mat.valueAt(3, 1) * inVec.y +
    mat.valueAt(3, 2) * inVec.z + mat.valueAt(3, 3) * inVec.w;
}

/*
 cose -sine
 sine cose
 */
FORCEINLINE MyFMatrix2& MyTransformation::rotateMatrix(MyFMatrix2 &mat,
                                                             float radius) {
    float sine = MyMathUtil::sin(radius);
    float cose = MyMathUtil::cos(radius);
    float tmp = -sine * mat.valueAt(0, 0) + cose * mat.valueAt(1, 0);
    mat.valueAt(0, 0) = cose * mat.valueAt(0, 0) - sine * mat.valueAt(1, 0);
    mat.valueAt(1, 0) = tmp;
    tmp = -sine * mat.valueAt(0, 1) + cose * mat.valueAt(1, 1);
    mat.valueAt(0, 1) = cose * mat.valueAt(0, 1) - sine * mat.valueAt(1, 1);
    mat.valueAt(1, 1) = tmp;
    return mat;
}

/*
 1      0       0
 0      cose   -sine
 0      sine    cose
 */
FORCEINLINE MyFMatrix3& MyTransformation::rotateMatrixByAxisX(MyFMatrix3 &mat,
                                                                    float radius) {
    float sine = MyMathUtil::sin(radius);
    float cose = MyMathUtil::cos(radius);
    float tmp1 = cose * mat.valueAt(1, 1) - sine * mat.valueAt(2, 1);
    float tmp2 = cose * mat.valueAt(1, 2) - sine * mat.valueAt(2, 2);
    mat.valueAt(1, 0) = cose * mat.valueAt(1, 0) - sine * mat.valueAt(2, 0);
    mat.valueAt(1, 1) = tmp1;
    mat.valueAt(1, 2) = tmp2;
    tmp1 = sine * mat.valueAt(1, 1) + cose * mat.valueAt(2, 1);
    tmp2 = sine * mat.valueAt(1, 2) + cose * mat.valueAt(2, 2);
    mat.valueAt(2, 0) = sine * mat.valueAt(1, 0) + cose * mat.valueAt(2, 0);
    mat.valueAt(2, 1) = tmp1;
    mat.valueAt(2, 2) = tmp2;
    return mat;
}

/*
 cose      0       sine
 0          1       0
 -sine      0       cose
 */
FORCEINLINE MyFMatrix3& MyTransformation::rotateMatrixByAxisY(MyFMatrix3 &mat,
                                                                    float radius) {
    float sine = MyMathUtil::sin(radius);
    float cose = MyMathUtil::cos(radius);
    float tmp1 = cose * mat.valueAt(0, 1) + sine * mat.valueAt(2, 1);
    float tmp2 = cose * mat.valueAt(0, 2) + sine * mat.valueAt(2, 2);
    mat.valueAt(0, 0) = cose * mat.valueAt(0, 0) + sine * mat.valueAt(2, 0);
    mat.valueAt(0, 1) = tmp1;
    mat.valueAt(0, 2) = tmp2;
    tmp1 = -sine * mat.valueAt(0, 1) + cose * mat.valueAt(2, 1);
    tmp2 = -sine * mat.valueAt(0, 2) + cose * mat.valueAt(2, 2);
    mat.valueAt(2, 0) = -sine * mat.valueAt(0, 0) + cose * mat.valueAt(2, 0);
    mat.valueAt(2, 1) = tmp1;
    mat.valueAt(2, 2) = tmp2;
    return mat;
}

/*
 cose      -sine      0
 0          1           0
 sine       cose       0
 */
FORCEINLINE MyFMatrix3& MyTransformation::rotateMatrixByAxisZ(MyFMatrix3 &mat,
                                                                    float radius) {
    float sine = MyMathUtil::sin(radius);
    float cose = MyMathUtil::cos(radius);
    float tmp1 = cose * mat.valueAt(0, 1) - sine * mat.valueAt(1, 1);
    float tmp2 = cose * mat.valueAt(0, 2) - sine * mat.valueAt(1, 2);
    mat.valueAt(0, 0) = cose * mat.valueAt(0, 0) - sine * mat.valueAt(1, 0);
    mat.valueAt(0, 1) = tmp1;
    mat.valueAt(0, 2) = tmp2;
    tmp1 = sine * mat.valueAt(0, 1) + cose * mat.valueAt(1, 1);
    tmp2 = sine * mat.valueAt(0, 2) + cose * mat.valueAt(1, 2);
    mat.valueAt(2, 0) = sine * mat.valueAt(0, 0) + cose * mat.valueAt(1, 0);
    mat.valueAt(2, 1) = tmp1;
    mat.valueAt(2, 2) = tmp2;
    return mat;
}

FORCEINLINE MyFMatrix3& MyTransformation::rotateMatrixByAxis(MyFMatrix3 &mat,
                                                                   const MyFVector3 &vec,
                                                                   float radius) {
    MyFVector3 normalizedVec;
    normalizeVector(vec, normalizedVec);
    return rotateMatrixByNormalizedAxis(mat, normalizedVec, radius);
}

// v' = (v - dot(v, n)n)cose + cross(v, n) * sine
FORCEINLINE MyFMatrix3& MyTransformation::rotateMatrixByNormalizedAxis(
                                                                             MyFMatrix3 &mat,
                                                                             const MyFVector3 &vec,
                                                                             float radius) {
    float sine = MyMathUtil::sin(radius);
    float cose = MyMathUtil::cos(radius);
    float oneMinusCose = 1.0f - cose;
    float xx = vec.x * vec.x;
    float xy = vec.x * vec.y;
    float yy = vec.y * vec.y;
    float yz = vec.y * vec.z;
    float zz = vec.z * vec.z;
    float zx = vec.z * vec.x;
    float xsine = vec.x * sine;
    float ysine = vec.y * sine;
    float zsine = vec.z * sine;
    float mx = oneMinusCose * xx + cose;
    float my = oneMinusCose * xy + zsine;
    float mz = oneMinusCose * zx - ysine;
    float tmp0 = mx * mat.valueAt(0, 0) + my * mat.valueAt(1, 0) + mz * mat.valueAt(2, 0);
    float tmp1 = mx * mat.valueAt(0, 1) + my * mat.valueAt(1, 1) + mz * mat.valueAt(2, 1);
    float tmp2 = mx * mat.valueAt(0, 2) + my * mat.valueAt(1, 2) + mz * mat.valueAt(2, 2);
    mx = oneMinusCose * xy - zsine;
    my = oneMinusCose * yy + cose;
    mz = oneMinusCose * yz + xsine;
    float tmp3 = mx * mat.valueAt(0, 0) + my * mat.valueAt(1, 0) + mz * mat.valueAt(2, 0);
    float tmp4 = mx * mat.valueAt(0, 1) + my * mat.valueAt(1, 1) + mz * mat.valueAt(2, 1);
    float tmp5 = mx * mat.valueAt(0, 2) + my * mat.valueAt(1, 2) + mz * mat.valueAt(2, 2);
    mx = oneMinusCose * zx + ysine;
    my = oneMinusCose * yz - xsine;
    mz = oneMinusCose * zz + cose;
    float tmp6 = mx * mat.valueAt(0, 0) + my * mat.valueAt(1, 0) + mz * mat.valueAt(2, 0);
    float tmp7 = mx * mat.valueAt(0, 1) + my * mat.valueAt(1, 1) + mz * mat.valueAt(2, 1);
    float tmp8 = mx * mat.valueAt(0, 2) + my * mat.valueAt(1, 2) + mz * mat.valueAt(2, 2);
    mat.valueAt(0, 0) = tmp0; mat.valueAt(0, 1) = tmp1; mat.valueAt(0, 2) = tmp2;
    mat.valueAt(1, 0) = tmp3; mat.valueAt(1, 1) = tmp4; mat.valueAt(1, 2) = tmp5;
    mat.valueAt(2, 0) = tmp6; mat.valueAt(2, 1) = tmp7; mat.valueAt(2, 2) = tmp8;
    return mat;
}

/*
 k  0
 0  k
*/
FORCEINLINE MyFMatrix2& MyTransformation::scaleMatrix(MyFMatrix2 &mat, float scalar) {
    mat *= scalar;
    return mat;
}

/*
 k  0   0
 0  k   0 = kE
 0  0   k
*/
FORCEINLINE MyFMatrix3& MyTransformation::scaleMatrix(MyFMatrix3 &mat, float scalar) {
    mat *= scalar;
    return mat;
}

/* v' = v + (k - 1)dot(v, n)n
 1 + (k - 1)nx * nx     (k - 1) * ny * nx       (k - 1) * nz * nx
 (k - 1) * nx * ny      1 + (k - 1)* ny * ny    (k - 1) * nz * ny
 (k - 1) * nx * nz      (k - 1) * ny * nz       1 + (k - 1) * nz * nz
*/
FORCEINLINE MyFMatrix3& MyTransformation::scaleMatrix(MyFMatrix3 &mat,
                                                            const MyFVector3 &axis,
                                                            float scalar) {
    MINE_ASSERT2(vectorNormalized(axis), "MyTransformation::scaleMatrix, axis not normalized");
    float scalarMinusOne = scalar - 1.0f;
    float mxy = scalarMinusOne * axis.x * axis.y;
    float myz = scalarMinusOne * axis.y * axis.z;
    float mzx = scalarMinusOne * axis.z * axis.x;
    float mxx = 1 + scalarMinusOne * axis.x * axis.x;
    float myy = 1 + scalarMinusOne * axis.y * axis.y;
    float mzz = 1 + scalarMinusOne * axis.z * axis.z;
    float tmp0 = mxy * mat.valueAt(0, 0) + myy * mat.valueAt(1, 0) + myz * mat.valueAt(2, 0);
    float tmp1 = mxy * mat.valueAt(0, 1) + myy * mat.valueAt(1, 1) + myz * mat.valueAt(2, 1);
    float tmp2 = mxy * mat.valueAt(0, 2) + myy * mat.valueAt(1, 2) + myz * mat.valueAt(2, 2);
    float tmp3 = mzx * mat.valueAt(0, 0) + myz * mat.valueAt(1, 0) + mzz * mat.valueAt(2, 0);
    float tmp4 = mzx * mat.valueAt(0, 1) + myz * mat.valueAt(1, 1) + mzz * mat.valueAt(2, 1);
    float tmp5 = mzx * mat.valueAt(0, 2) + myz * mat.valueAt(1, 2) + mzz * mat.valueAt(2, 2);
    mat.valueAt(0, 0) = mxx * mat.valueAt(0, 0) + mxy * mat.valueAt(1, 0) + mzx * mat.valueAt(2, 0);
    mat.valueAt(0, 1) = mxx * mat.valueAt(0, 1) + mxy * mat.valueAt(1, 1) + mzx * mat.valueAt(2, 1);
    mat.valueAt(0, 2) = mxx * mat.valueAt(0, 2) + mxy * mat.valueAt(1, 2) + mzx * mat.valueAt(2, 2);
    mat.valueAt(1, 0) = tmp0; mat.valueAt(1, 1) = tmp1; mat.valueAt(1, 2) = tmp2;
    mat.valueAt(2, 0) = tmp3; mat.valueAt(2, 1) = tmp4; mat.valueAt(2, 2) = tmp5;
    return mat;
}

/* v' = v + (k - 1)dot(v, n)n, n = [0 0 1]', k = 0
 1      0       0
 0      1       0
 0      0       0
 */
FORCEINLINE MyFMatrix3& MyTransformation::orthogonalMatrixByPlaneXY(MyFMatrix3 &mat) {
    mat.valueAt(2, 0) = mat.valueAt(2, 1) = mat.valueAt(2, 2) = 0.0f;
    return mat;
}

/* v' = v + (k - 1)dot(v, n)n, n = [1 0 0]', k = 0
 0      0      0
 0      1       0
 0      0       1
 */
FORCEINLINE MyFMatrix3& MyTransformation::orthogonalMatrixByPlaneYZ(MyFMatrix3 &mat) {
    mat.valueAt(0, 0) = mat.valueAt(0, 1) = mat.valueAt(0, 2) = 0.0f;
    return mat;
}

/* v' = v + (k - 1)dot(v, n)n, n = [0 1 0]', k = 0
 1      0       0
 0      0       0
 0      0       1
 */
FORCEINLINE MyFMatrix3& MyTransformation::orthogonalMatrixByPlaneZX(MyFMatrix3 &mat) {
    mat.valueAt(1, 0) = mat.valueAt(1, 1) = mat.valueAt(1, 2) = 0.0f;
    return mat;
}

/* v' = v + (k - 1)dot(v, n)n, k = 0
 1 - nx * nx    -ny * nx       -nz * nx
 -nx * ny       1 - ny * ny    -nz * ny
 -nx * nz       -ny * nz       1 - nz * nz
 */
FORCEINLINE MyFMatrix3& MyTransformation::orthogonalMatrix(MyFMatrix3 &mat, const MyPlane &plane) {
    const MyFVector3 &axis = plane.normal();
    float mxy = -axis.x * axis.y;
    float myz = -axis.y * axis.z;
    float mzx = -axis.z * axis.x;
    float mxx = 1 - axis.x * axis.x;
    float myy = 1 - axis.y * axis.y;
    float mzz = 1 - axis.z * axis.z;
    float tmp0 = mxy * mat.valueAt(0, 0) + myy * mat.valueAt(1, 0) + myz * mat.valueAt(2, 0);
    float tmp1 = mxy * mat.valueAt(0, 1) + myy * mat.valueAt(1, 1) + myz * mat.valueAt(2, 1);
    float tmp2 = mxy * mat.valueAt(0, 2) + myy * mat.valueAt(1, 2) + myz * mat.valueAt(2, 2);
    float tmp3 = mzx * mat.valueAt(0, 0) + myz * mat.valueAt(1, 0) + mzz * mat.valueAt(2, 0);
    float tmp4 = mzx * mat.valueAt(0, 1) + myz * mat.valueAt(1, 1) + mzz * mat.valueAt(2, 1);
    float tmp5 = mzx * mat.valueAt(0, 2) + myz * mat.valueAt(1, 2) + mzz * mat.valueAt(2, 2);
    mat.valueAt(0, 0) = mxx * mat.valueAt(0, 0) + mxy * mat.valueAt(1, 0) + mzx * mat.valueAt(2, 0);
    mat.valueAt(0, 1) = mxx * mat.valueAt(0, 1) + mxy * mat.valueAt(1, 1) + mzx * mat.valueAt(2, 1);
    mat.valueAt(0, 2) = mxx * mat.valueAt(0, 2) + mxy * mat.valueAt(1, 2) + mzx * mat.valueAt(2, 2);
    mat.valueAt(1, 0) = tmp0; mat.valueAt(1, 1) = tmp1; mat.valueAt(1, 2) = tmp2;
    mat.valueAt(2, 0) = tmp3; mat.valueAt(2, 1) = tmp4; mat.valueAt(2, 2) = tmp5;
    return mat;
}

/* v' = v + (k - 1)dot(v, n)n, n = [0 0 1]', k = -1
 1      0       0
 0      1       0
 0      0       -1
 */
FORCEINLINE MyFMatrix3& MyTransformation::mirrorMatrixByPlaneXY(MyFMatrix3 &mat) {
    mat.valueAt(2, 0) *= -1.0f;
    mat.valueAt(2, 1) *= -1.0f;
    mat.valueAt(2, 2) *= -1.0f;
    return mat;
}

/* v' = v + (k - 1)dot(v, n)n, n = [1 0 0]', k = 0
 -1     0      0
 0      1       0
 0      0       1
 */
FORCEINLINE MyFMatrix3& MyTransformation::mirrorMatrixByPlaneYZ(MyFMatrix3 &mat) {
    mat.valueAt(0, 0) *= -1.0f;
    mat.valueAt(0, 1) *= -1.0f;
    mat.valueAt(0, 2) *= -1.0f;
    return mat;
}

/* v' = v + (k - 1)dot(v, n)n, n = [0 1 0]', k = 0
 1      0       0
 0      -1      0
 0      0       1
 */
FORCEINLINE MyFMatrix3& MyTransformation::mirrorMatrixByPlaneZX(MyFMatrix3 &mat) {
    mat.valueAt(1, 0) *= -1.0f;
    mat.valueAt(1, 1) *= -1.0f;
    mat.valueAt(1, 2) *= -1.0f;
    return mat;
}

/* v' = v + (k - 1)dot(v, n)n, k = -1
 1 - 2nx * nx    -2ny * nx       -2nz * nx
 -2nx * ny       1 - 2ny * ny    -2nz * ny
 -2nx * nz       -2ny * nz       1 - 2nz * nz
 */
FORCEINLINE MyFMatrix3& MyTransformation::mirrorMatrix(MyFMatrix3 &mat, const MyPlane &plane) {
    const MyFVector3 &axis = plane.normal();
    float mxy = -2.0f * axis.x * axis.y;
    float myz = -2.0f * axis.y * axis.z;
    float mzx = -2.0f * axis.z * axis.x;
    float mxx = 1 - 2.0f * axis.x * axis.x;
    float myy = 1 - 2.0f * axis.y * axis.y;
    float mzz = 1 - 2.0f * axis.z * axis.z;
    float tmp0 = mxy * mat.valueAt(0, 0) + myy * mat.valueAt(1, 0) + myz * mat.valueAt(2, 0);
    float tmp1 = mxy * mat.valueAt(0, 1) + myy * mat.valueAt(1, 1) + myz * mat.valueAt(2, 1);
    float tmp2 = mxy * mat.valueAt(0, 2) + myy * mat.valueAt(1, 2) + myz * mat.valueAt(2, 2);
    float tmp3 = mzx * mat.valueAt(0, 0) + myz * mat.valueAt(1, 0) + mzz * mat.valueAt(2, 0);
    float tmp4 = mzx * mat.valueAt(0, 1) + myz * mat.valueAt(1, 1) + mzz * mat.valueAt(2, 1);
    float tmp5 = mzx * mat.valueAt(0, 2) + myz * mat.valueAt(1, 2) + mzz * mat.valueAt(2, 2);
    mat.valueAt(0, 0) = mxx * mat.valueAt(0, 0) + mxy * mat.valueAt(1, 0) + mzx * mat.valueAt(2, 0);
    mat.valueAt(0, 1) = mxx * mat.valueAt(0, 1) + mxy * mat.valueAt(1, 1) + mzx * mat.valueAt(2, 1);
    mat.valueAt(0, 2) = mxx * mat.valueAt(0, 2) + mxy * mat.valueAt(1, 2) + mzx * mat.valueAt(2, 2);
    mat.valueAt(1, 0) = tmp0; mat.valueAt(1, 1) = tmp1; mat.valueAt(1, 2) = tmp2;
    mat.valueAt(2, 0) = tmp3; mat.valueAt(2, 1) = tmp4; mat.valueAt(2, 2) = tmp5;
    return mat;
}

/* row(a) += k * row(b), det' == det -> volume/area not changed
 1  s   t
 0  1   0
 0  0   1
*/
FORCEINLINE MyFMatrix3& MyTransformation::shearMatrixByAxisX(MyFMatrix3 &mat, float s, float t) {
    mat.valueAt(0, 0) += s * mat.valueAt(1, 0) + t * mat.valueAt(2, 0);
    mat.valueAt(0, 1) += s * mat.valueAt(1, 1) + t * mat.valueAt(2, 1);
    mat.valueAt(0, 2) += s * mat.valueAt(1, 2) + t * mat.valueAt(2, 2);
    return mat;
}

/* row(a) += k * row(b), det' == det -> volume/area not changed
 1  0   0
 s  1   t
 0  0   1
 */
FORCEINLINE MyFMatrix3& MyTransformation::shearMatrixByAxisY(MyFMatrix3 &mat, float s, float t) {
    mat.valueAt(1, 0) += s * mat.valueAt(0, 0) + t * mat.valueAt(2, 0);
    mat.valueAt(1, 1) += s * mat.valueAt(0, 1) + t * mat.valueAt(2, 1);
    mat.valueAt(1, 2) += s * mat.valueAt(0, 2) + t * mat.valueAt(2, 2);
    return mat;
}

/* row(a) += k * row(b), det' == det -> volume/area not changed
 1  0   0
 0  1   0
 s  t   1
 */
FORCEINLINE MyFMatrix3& MyTransformation::shearMatrixByAxisZ(MyFMatrix3 &mat, float s, float t) {
    mat.valueAt(2, 0) += s * mat.valueAt(0, 0) + t * mat.valueAt(1, 0);
    mat.valueAt(2, 1) += s * mat.valueAt(0, 1) + t * mat.valueAt(1, 1);
    mat.valueAt(2, 2) += s * mat.valueAt(0, 2) + t * mat.valueAt(1, 2);
    return mat;
}

// B = A * P -> P = A ^ -1 * B, a = A * x = B * y = A * P * y -> x = Py ->y = P ^ -1 * x
FORCEINLINE void MyTransformation::transformCoordianteVectorForward(const MyCoordinateTransition &coordTransit,
                                                                    const MyFVector3 &vecA,
                                                                    MyFVector3 &vecB) {
    transformVector(coordTransit.backwardMatrix(), vecA, vecB);
}

/* translation(x, y, z)
 1  0   0   x
 0  1   0   y
 0  0   1   z
 0  0   0   1
*/
MyFMatrix4& MyTransformation::translateMatrix(MyFMatrix4 &mat, const MyFVector3 &vec) {
    mat.valueAt(0, 0) += vec.x * mat.valueAt(3, 0);
    mat.valueAt(0, 1) += vec.x * mat.valueAt(3, 1);
    mat.valueAt(0, 2) += vec.x * mat.valueAt(3, 2);
    mat.valueAt(0, 3) += vec.x * mat.valueAt(3, 3);
    mat.valueAt(1, 0) += vec.y * mat.valueAt(3, 0);
    mat.valueAt(1, 1) += vec.y * mat.valueAt(3, 1);
    mat.valueAt(1, 2) += vec.y * mat.valueAt(3, 2);
    mat.valueAt(1, 3) += vec.y * mat.valueAt(3, 3);
    mat.valueAt(2, 0) += vec.z * mat.valueAt(3, 0);
    mat.valueAt(2, 1) += vec.z * mat.valueAt(3, 1);
    mat.valueAt(2, 2) += vec.z * mat.valueAt(3, 2);
    mat.valueAt(2, 3) += vec.z * mat.valueAt(3, 3);
    return mat;
}

MyFMatrix4& MyTransformation::translateMatrix(MyFMatrix4 &mat, float x, float y, float z) {
    mat.valueAt(0, 0) += x * mat.valueAt(3, 0);
    mat.valueAt(0, 1) += x * mat.valueAt(3, 1);
    mat.valueAt(0, 2) += x * mat.valueAt(3, 2);
    mat.valueAt(0, 3) += x * mat.valueAt(3, 3);
    mat.valueAt(1, 0) += y * mat.valueAt(3, 0);
    mat.valueAt(1, 1) += y * mat.valueAt(3, 1);
    mat.valueAt(1, 2) += y * mat.valueAt(3, 2);
    mat.valueAt(1, 3) += y * mat.valueAt(3, 3);
    mat.valueAt(2, 0) += z * mat.valueAt(3, 0);
    mat.valueAt(2, 1) += z * mat.valueAt(3, 1);
    mat.valueAt(2, 2) += z * mat.valueAt(3, 2);
    mat.valueAt(2, 3) += z * mat.valueAt(3, 3);
    return mat;
}

/* since we're in right-hand coordinate, v' = [x y z] * (d/z), d < 0 -> [x y z z/d] (homogeneous)
 1      0       0       0
 0      1       0       0
 0      0       1       0
 0      0       1/d     0
*/
MyFMatrix4& MyTransformation::perspectiveMatrix(MyFMatrix4 &mat, float zd) {
    MINE_ASSERT2(zd < 0.0f, "MyTransformation::perspectiveMatrix, d >= 0");
    float invD = 1.0f/zd;
    mat.valueAt(3, 0) = mat.valueAt(2, 0) * invD;
    mat.valueAt(3, 1) = mat.valueAt(2, 1) * invD;
    mat.valueAt(3, 2) = mat.valueAt(2, 2) * invD;
    mat.valueAt(3, 3) = mat.valueAt(2, 3) * invD;
    return mat;
}

// B = A * P -> P = A ^ -1 * B, a = A * x = B * y = A * P * y -> x = Py
FORCEINLINE void MyTransformation::transformCoordianteVectorBackward(const MyCoordinateTransition &coordTransit,
                                                                    const MyFVector3 &vecB,
                                                                    MyFVector3 &vecA) {
    transformVector(coordTransit.forwardMatrix(), vecB, vecA);
}

FORCEINLINE MyFVector2 operator*(const MyFMatrix2 &mat, const MyFVector2 &vec) {
    return MyFVector2(mat.valueAt(0, 0) * vec.x + mat.valueAt(0, 1) * vec.y,
                      mat.valueAt(1, 0) * vec.x + mat.valueAt(1, 1) * vec.y);
}

FORCEINLINE MyFVector3 operator*(const MyFMatrix3 &mat, const MyFVector3 &vec) {
    return MyFVector3(mat.valueAt(0, 0) * vec.x + mat.valueAt(0, 1) * vec.y + mat.valueAt(0, 2) * vec.z,
                      mat.valueAt(1, 0) * vec.x + mat.valueAt(1, 1) * vec.y + mat.valueAt(1, 2) * vec.z,
                      mat.valueAt(2, 0) * vec.x + mat.valueAt(2, 1) * vec.y + mat.valueAt(2, 2) * vec.z);
}

FORCEINLINE MyFVector4 operator*(const MyFMatrix4 &mat, const MyFVector4 &vec) {
    return MyFVector4(mat.valueAt(0, 0) * vec.x + mat.valueAt(0, 1) * vec.y + mat.valueAt(0, 2) * vec.z + mat.valueAt(0, 3) * vec.w,
                      mat.valueAt(1, 0) * vec.x + mat.valueAt(1, 1) * vec.y + mat.valueAt(1, 2) * vec.z + mat.valueAt(1, 3) * vec.w,
                      mat.valueAt(2, 0) * vec.x + mat.valueAt(2, 1) * vec.y + mat.valueAt(2, 2) * vec.z + mat.valueAt(2, 3) * vec.w,
                      mat.valueAt(3, 0) * vec.x + mat.valueAt(3, 1) * vec.y + mat.valueAt(3, 2) * vec.z + mat.valueAt(3, 3) * vec.w);
}

MINE_NAMESPACE_END
