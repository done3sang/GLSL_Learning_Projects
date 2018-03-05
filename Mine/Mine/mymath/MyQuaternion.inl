//
//  MyQuaternion.inl
//  Mine
//
//  Created by xy on 01/03/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#include "MyMathUtil.hpp"

MINE_NAMESPACE_BEGIN

FORCEINLINE MyFQuaternion::MyFQuaternion(void) {}

FORCEINLINE MyFQuaternion::~MyFQuaternion(void) {}

FORCEINLINE MyFQuaternion::MyFQuaternion(float inW):
w(inW),
x(0.0f),
y(0.0f),
z(0.0f) {}

FORCEINLINE MyFQuaternion::MyFQuaternion(float inW, float inX, float inY, float inZ):
w(inW),
x(inX),
y(inY),
z(inZ) {}

FORCEINLINE MyFQuaternion::MyFQuaternion(const MyFQuaternion &other):
w(other.w),
x(other.x),
y(other.y),
z(other.z) {}

FORCEINLINE MyFQuaternion::MyFQuaternion(const MyFQuaternion &&other):
w(other.w),
x(other.x),
y(other.y),
z(other.z) {}

FORCEINLINE MyFQuaternion& MyFQuaternion::operator=(const MyFQuaternion &other) {
    w = other.w;
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

FORCEINLINE MyFQuaternion& MyFQuaternion::operator=(const MyFQuaternion &&other) {
    w = other.w;
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

FORCEINLINE bool MyFQuaternion::operator==(const MyFQuaternion &other) const {
    return MyMathUtil::equal(w, other.w) &&
    MyMathUtil::equal(x, other.x) &&
    MyMathUtil::equal(y, other.y) &&
    MyMathUtil::equal(z, other.z);
}

FORCEINLINE bool MyFQuaternion::operator!=(const MyFQuaternion &other) const {
    return !MyMathUtil::equal(w, other.w) ||
    !MyMathUtil::equal(x, other.x) ||
    !MyMathUtil::equal(y, other.y) ||
    !MyMathUtil::equal(z, other.z);
}

FORCEINLINE MyFQuaternion& MyFQuaternion::operator*=(float value) {
    w *= value;
    x *= value;
    y *= value;
    z *= value;
    return *this;
}

FORCEINLINE MyFQuaternion& MyFQuaternion::operator/=(float value) {
    MINE_ASSERT2(!MyMathUtil::zero(value), "MyFQuaternion::operator/=, value be zero");
    w *= value;
    x *= value;
    y *= value;
    z *= value;
    return *this;
}

// a * b = [w1 v1] * [w2 v2] = [w1 * w2 - dot(v1, v2) w1v2 + w2v1 + cross(v1, v2)]
FORCEINLINE MyFQuaternion& MyFQuaternion::operator*=(const MyFQuaternion &other) {
    float tw = w * other.w - x * other.x - y * other.y - z * other.z;
    float tx = w * other.x + other.w * x + y * other.z - z * other.y;
    float ty = w * other.y + other.w * y + z * other.x - x * other.z;
    z = w * other.z + other.w * z + x * other.y - y * other.x;
    w = tw;
    x = tx;
    y = ty;
    return *this;
}

FORCEINLINE MyFQuaternion operator-(const MyFQuaternion &quat) {
    return MyFQuaternion(-quat.w, -quat.x, -quat.y, -quat.z);
}

FORCEINLINE MyFQuaternion operator*(const MyFQuaternion &lhs, const MyFQuaternion &rhs) {
    return MyFQuaternion(lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z,
                         lhs.w * rhs.x + rhs.w * lhs.x + lhs.y * rhs.z - lhs.z * rhs.y,
                         lhs.w * rhs.y + rhs.w * lhs.y + lhs.z * rhs.x - lhs.x * rhs.z,
                         lhs.w * rhs.z + rhs.w * lhs.z + lhs.x * rhs.y - lhs.y * rhs.x);
}

FORCEINLINE MyFQuaternion operator*(const MyFQuaternion &quat, float value) {
    return MyFQuaternion(quat.w * value, quat.x * value, quat.y * value, quat.z * value);
}

FORCEINLINE MyFQuaternion operator*(float value, const MyFQuaternion &quat) {
    return MyFQuaternion(quat.w * value, quat.x * value, quat.y * value, quat.z * value);
}

FORCEINLINE MyFQuaternion operator/(const MyFQuaternion &quat, float value) {
    MINE_ASSERT2(!MyMathUtil::zero(value), "operator/, value be zero");
    value = 1.0f/value;
    return MyFQuaternion(quat.w * value, quat.x * value, quat.y * value, quat.z * value);
}

FORCEINLINE void identityQuaternion(MyFQuaternion &quat) {
    quat.w = 1.0f; quat.x = quat.y = quat.z = 0.0f;
}

FORCEINLINE void zeroQuaternion(MyFQuaternion &quat) {
    quat.w = quat.x = quat.y = quat.z = 0.0f;
}

FORCEINLINE float magnitudeSquareQuaternion(const MyFQuaternion &quat) {
    return quat.w * quat.w + quat.x * quat.x + quat.y * quat.y + quat.z * quat.z;
}

FORCEINLINE float magnitudeQuaternion(const MyFQuaternion &quat) {
    return MyMathUtil::sqrt(magnitudeSquareQuaternion(quat));
}

FORCEINLINE bool quaternionNormalized(const MyFQuaternion &quat) {
    return MyMathUtil::identity(magnitudeSquareQuaternion(quat));
}

FORCEINLINE void normalizeQuaternion(MyFQuaternion &quat) {
    MINE_ASSERT2(!MyMathUtil::zero(magnitudeQuaternion(quat)), "normalizeQuaternion, magnitude be zero");
    float invMag = 1.0f/magnitudeQuaternion(quat);
    quat.w *= invMag;
    quat.x *= invMag;
    quat.y *= invMag;
    quat.z *= invMag;
}

FORCEINLINE void normalizeQuaternion(const MyFQuaternion &quat, MyFQuaternion &outQuat) {
    MINE_ASSERT2(!MyMathUtil::zero(magnitudeQuaternion(quat)), "normalizeQuaternion, magnitude be zero");
    float invMag = 1.0f/magnitudeQuaternion(quat);
    outQuat.w = quat.w * invMag;
    outQuat.x = quat.x * invMag;
    outQuat.y = quat.y * invMag;
    outQuat.z = quat.z * invMag;
}

FORCEINLINE MyFQuaternion normalizeQuaternion(const MyFQuaternion &quat) {
    MyFQuaternion ret;
    normalizeQuaternion(quat, ret);
    return ret;
}

// [w -x -y -z]
FORCEINLINE void conjugateQuaternion(MyFQuaternion &quat) {
    quat.x = -quat.x;
    quat.y = -quat.y;
    quat.z = -quat.z;
}

FORCEINLINE void conjugateQuaternion(const MyFQuaternion &quat, MyFQuaternion &outQuat) {
    outQuat.w = quat.w;
    outQuat.x = -quat.x;
    outQuat.y = -quat.y;
    outQuat.z = -quat.z;
}

FORCEINLINE MyFQuaternion conjugateQuaternion(const MyFQuaternion &quat) {
    return MyFQuaternion(quat.w, -quat.x, -quat.y, -quat.z);
}

// q-1 = q*/|q|
FORCEINLINE void inverseQuaternion(MyFQuaternion &quat) {
    MINE_ASSERT2(!MyMathUtil::zero(magnitudeQuaternion(quat)), "inverseQuaternion, magnitude be zero");
    float invMag = 1.0f/magnitudeQuaternion(quat);
    quat.w *= invMag;
    invMag = -invMag;
    quat.x *= invMag;
    quat.y *= invMag;
    quat.z *= invMag;
}

FORCEINLINE void inverseQuaternion(const MyFQuaternion &quat, MyFQuaternion &outQuat) {
    MINE_ASSERT2(!MyMathUtil::zero(magnitudeQuaternion(quat)), "inverseQuaternion, magnitude be zero");
    float invMag = 1.0f/magnitudeQuaternion(quat);
    outQuat.w = quat.w * invMag;
    outQuat.x = -quat.x * invMag;
    outQuat.y = -quat.y * invMag;
    outQuat.z = -quat.z * invMag;
}

FORCEINLINE MyFQuaternion inverseQuaternion(const MyFQuaternion &quat) {
    MyFQuaternion ret;
    inverseQuaternion(quat, ret);
    return ret;
}

FORCEINLINE void inverseNormalizedQuaternion(MyFQuaternion &quat) {
    MINE_ASSERT2(MyMathUtil::identity(magnitudeSquareQuaternion(quat)), "inverseNormalizedQuaternion, quaternion not normalized");
    quat.x = -quat.x;
    quat.y = -quat.y;
    quat.z = -quat.z;
}

FORCEINLINE void inverseNormalizedQuaternion(const MyFQuaternion &quat, MyFQuaternion &outQuat) {
    MINE_ASSERT2(MyMathUtil::identity(magnitudeSquareQuaternion(quat)), "inverseNormalizedQuaternion, quaternion not normalized");
    outQuat.w = quat.w;
    outQuat.x = -quat.x;
    outQuat.y = -quat.y;
    outQuat.z = -quat.z;
}

FORCEINLINE MyFQuaternion inverseNormalizedQuaternion(const MyFQuaternion &quat) {
    MyFQuaternion ret;
    inverseNormalizedQuaternion(quat, ret);
    return ret;
}

FORCEINLINE float dotProduct(const MyFQuaternion &lhs, const MyFQuaternion &rhs) {
    return lhs.w * rhs.w + lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

FORCEINLINE void crossProduct(const MyFQuaternion &lhs,
                               const MyFQuaternion &rhs,
                               MyFQuaternion &outQuat) {
    outQuat.w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;
    outQuat.x = lhs.w * rhs.x + rhs.w * lhs.x + lhs.y * rhs.z - lhs.z * rhs.y;
    outQuat.y = lhs.w * rhs.y + rhs.w * lhs.y + lhs.z * rhs.x - lhs.x * rhs.z;
    outQuat.z = lhs.w * rhs.z + rhs.w * lhs.z + lhs.x * rhs.y - lhs.y * rhs.x;
}

// a * d = b -> d = a-1 * b
FORCEINLINE void differQuaternion(const MyFQuaternion &begQuat,
                                  const MyFQuaternion &endQuat,
                                  MyFQuaternion &outQuat) {
    inverseNormalizedQuaternion(begQuat, outQuat);
    outQuat *= endQuat;
}

FORCEINLINE MyFQuaternion differQuaternion(const MyFQuaternion &begQuat, const MyFQuaternion &endQuat) {
    MyFQuaternion ret;
    differQuaternion(begQuat, endQuat, ret);
    return ret;
}

// logq = log([cose nsine]) = [0 en]
FORCEINLINE void logQuaternion(const MyFQuaternion &quat, MyFQuaternion &outQuat) {
    MINE_ASSERT2(quaternionNormalized(quat), "logQuaternion, quaternion not normalized");
    if(MyMathUtil::identity(quat.w)) {
        zeroQuaternion(outQuat);
    } else {
        float radius = MyMathUtil::acos(quat.w);
        float coff = radius/MyMathUtil::sin(radius);
        outQuat.w = 0.0f;
        outQuat.x = quat.x * coff;
        outQuat.y = quat.y * coff;
        outQuat.z = quat.z * coff;
    }
}

FORCEINLINE MyFQuaternion logQuaternion(const MyFQuaternion &quat) {
    MyFQuaternion ret;
    logQuaternion(quat, ret);
    return ret;
}

// expq = exp([0 en]) = [cose nsine], |n| = 1 -> x * x + y * y + z * z = e^2 * |n| * |n| = e^2
FORCEINLINE void expQuaternion(const MyFQuaternion &quat, MyFQuaternion &outQuat) {
    MINE_ASSERT2(MyMathUtil::zero(quat.w), "expQuaternion, w not zero");
    float theta = quat.x * quat.x + quat.y * quat.y + quat.z * quat.z;
    if(MyMathUtil::zero(theta)) {
        identityQuaternion(outQuat);
    } else {
        theta = MyMathUtil::sqrt(theta);
        float coff = MyMathUtil::sin(theta)/theta;
        outQuat.w = MyMathUtil::cos(theta);
        outQuat.x = quat.x * coff;
        outQuat.y = quat.y * coff;
        outQuat.z = quat.z * coff;
    }
}

FORCEINLINE MyFQuaternion expQuaternion(const MyFQuaternion &quat) {
    MyFQuaternion ret;
    expQuaternion(quat, ret);
    return ret;
}

// powerq = exp(tlog(q))
FORCEINLINE void powerQuaternion(const MyFQuaternion &quat,
                                 float power,
                                 MyFQuaternion &outQuat) {
    MINE_ASSERT2(quaternionNormalized(quat), "powerQuaternion, quaternion not normalized");
    if(MyMathUtil::identity(quat.w)) {
        identityQuaternion(outQuat);
    } else {
        float theta = MyMathUtil::acos(quat.w);
        float sine = MyMathUtil::sin(theta);
        theta *= power;
        float coff = MyMathUtil::sin(theta)/sine;
        outQuat.w = MyMathUtil::cos(theta);
        outQuat.x = quat.x * coff;
        outQuat.y = quat.y * coff;
        outQuat.z = quat.z * coff;
    }
}

FORCEINLINE MyFQuaternion powerQuaternion(const MyFQuaternion &quat, float power) {
    MyFQuaternion ret;
    powerQuaternion(quat, power, ret);
    return ret;
}

// slerpq = sin(w * (1 -t))/sin(w) * q0 + sin(w * t)/sin(w) * q1
FORCEINLINE void slerpQuaternion(const MyFQuaternion &begQuat,
                                 const MyFQuaternion &endQuat,
                                 float t,
                                 MyFQuaternion &outQuat) {
    MINE_ASSERT2(quaternionNormalized(begQuat), "slerpQuaternion, begQuat not normalized");
    MINE_ASSERT2(quaternionNormalized(endQuat), "slerpQuaternion, endQuat not normalized");
    MINE_ASSERT2(t >= 0.0f && t <= 1.0f, "slerpQuaternion, t not of range");
    float cosOmega = dotProduct(begQuat, endQuat);
    float k = 1.0f;
    if(cosOmega < 0.0f) {
        cosOmega = -cosOmega;
        k = -1.0f;
    }
    float k0 = 1.0f - t, k1 = t;
    if(!MyMathUtil::identity(cosOmega)) {
        float sinOmega = MyMathUtil::sqrt(1.0f - cosOmega * cosOmega); // sine = sqrt(1 - cose^2)
        float omega = MyMathUtil::atan2(sinOmega, cosOmega);
        float invSineOmega = 1.0f/sinOmega;
        k0 = MyMathUtil::sin(omega * k0) * invSineOmega;
        k1 = MyMathUtil::sin(omega * k1) * invSineOmega * k;
    }
    outQuat.w = begQuat.w * k0 + endQuat.w * k1;
    outQuat.x = begQuat.x * k0 + endQuat.x * k1;
    outQuat.y = begQuat.y * k0 + endQuat.y * k1;
    outQuat.z = begQuat.z * k0 + endQuat.z * k1;
}

FORCEINLINE MyFQuaternion slerpQuaternion(const MyFQuaternion &begQuat,
                                          const MyFQuaternion &endQuat,
                                          float t) {
    MyFQuaternion ret;
    slerpQuaternion(begQuat, endQuat, t, ret);
    return ret;
}

MINE_NAMESPACE_END
