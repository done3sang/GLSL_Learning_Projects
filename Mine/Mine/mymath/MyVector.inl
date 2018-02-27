//
//  MyFVector.inl
//  Mine
//
//  Created by xy on 23/02/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#include "MyMathUtil.hpp"

MINE_NAMESPACE_BEGIN

// MyFVector2 implementation

FORCEINLINE MyFVector2::MyFVector2(void) {}

FORCEINLINE MyFVector2::MyFVector2(float value):
x(value), y(value) {}

FORCEINLINE MyFVector2::MyFVector2(float vx, float vy):
x(vx), y(vy) {}

FORCEINLINE MyFVector2::MyFVector2(const MyFVector2 &other):
x(other.x), y(other.y) {}

FORCEINLINE MyFVector2::MyFVector2(const MyFVector2 &&other):
x(other.x), y(other.y) {}

FORCEINLINE MyFVector2::~MyFVector2(void) {}

FORCEINLINE MyFVector2& MyFVector2::operator=(const MyFVector2 &other) {
    MINE_ASSERT2(this != &other, "MyFVector2::operator=, same object");
    x = other.x;
    y = other.y;
    return *this;
}

FORCEINLINE MyFVector2& MyFVector2::operator=(const MyFVector2 &&other) {
    MINE_ASSERT2(this != &other, "MyFVector2::operator=, same object");
    x = other.x;
    y = other.y;
    return *this;
}

FORCEINLINE bool MyFVector2::operator==(const MyFVector2 &other) const {
    return x == other.x && y == other.y;
}

FORCEINLINE bool MyFVector2::operator!=(const MyFVector2 &other) const {
    return x != other.x || y != other.y;
}

FORCEINLINE MyFVector2& MyFVector2::operator+=(const MyFVector2 &other) {
    x += other.x;
    y += other.y;
    return *this;
}

FORCEINLINE MyFVector2& MyFVector2::operator-=(const MyFVector2 &other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

FORCEINLINE MyFVector2& MyFVector2::operator*=(float value) {
    x *= value;
    y *= value;
    return *this;
}

FORCEINLINE MyFVector2& MyFVector2::operator/=(float value) {
    const float inv(1/value);
    x *= inv;
    y *= inv;
    return *this;
}

FORCEINLINE MyFVector2 operator-(const MyFVector2 &v) {
    return MyFVector2(-v.x, -v.y);
}

FORCEINLINE MyFVector2 operator+(const MyFVector2 &lhs, const MyFVector2 &rhs) {
    return MyFVector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

FORCEINLINE MyFVector2 operator-(const MyFVector2 &lhs, const MyFVector2 &rhs) {
    return MyFVector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

FORCEINLINE MyFVector2 operator*(const MyFVector2 &v, float value) {
    return MyFVector2(v.x * value, v.y * value);
}

FORCEINLINE MyFVector2 operator*(float value, const MyFVector2 &v) {
    return MyFVector2(v.x * value, v.y * value);
}

FORCEINLINE MyFVector2 operator/(const MyFVector2 &v, float value) {
    const float inv(1/value);
    return MyFVector2(v.x * inv, v.y * inv);
}

FORCEINLINE float* value_pointer(MyFVector2 &v) {
    return &v.x;
}

FORCEINLINE const float* value_pointer(const MyFVector2 &v) {
    return &v.x;
}

// MyFVector3 implementation

FORCEINLINE MyFVector3::MyFVector3(void) {}

FORCEINLINE MyFVector3::MyFVector3(float value):
x(value), y(value), z(value) {}

FORCEINLINE MyFVector3::MyFVector3(float vx, float vy, float vz):
x(vx), y(vy), z(vz) {}

FORCEINLINE MyFVector3::MyFVector3(const MyFVector3 &other):
x(other.x), y(other.y), z(other.z) {}

FORCEINLINE MyFVector3::MyFVector3(const MyFVector3 &&other):
x(other.x), y(other.y), z(other.z) {}

FORCEINLINE MyFVector3::~MyFVector3(void) {}

FORCEINLINE MyFVector3& MyFVector3::operator=(const MyFVector3 &other) {
    MINE_ASSERT2(this != &other, "MyFVector3::operator=, same object");
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

FORCEINLINE MyFVector3& MyFVector3::operator=(const MyFVector3 &&other) {
    MINE_ASSERT2(this != &other, "MyFVector3::operator=, same object");
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

FORCEINLINE bool MyFVector3::operator==(const MyFVector3 &other) const {
    return x == other.x && y == other.y && z == other.z;
}

FORCEINLINE bool MyFVector3::operator!=(const MyFVector3 &other) const {
    return x != other.x || y != other.y || z != other.z;
}

FORCEINLINE MyFVector3& MyFVector3::operator+=(const MyFVector3 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

FORCEINLINE MyFVector3& MyFVector3::operator-=(const MyFVector3 &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

FORCEINLINE MyFVector3& MyFVector3::operator*=(float value) {
    x *= value;
    y *= value;
    z *= value;
    return *this;
}

FORCEINLINE MyFVector3& MyFVector3::operator/=(float value) {
    const float inv(1/value);
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
}

FORCEINLINE MyFVector3& MyFVector3::operator*=(const MyFVector3 &other) {
    float vx = y * other.z - z * other.y;
    float vy = z * other.x - x * other.z;
    float vz = x * other.y - y * other.x;
    x = vx;
    y = vy;
    z = vz;
    return *this;
}

FORCEINLINE MyFVector3 operator-(const MyFVector3 &v) {
    return MyFVector3(-v.x, -v.y, -v.z);
}

FORCEINLINE MyFVector3 operator+(const MyFVector3 &lhs, const MyFVector3 &rhs) {
    return MyFVector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

FORCEINLINE MyFVector3 operator-(const MyFVector3 &lhs, const MyFVector3 &rhs) {
    return MyFVector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

FORCEINLINE MyFVector3 operator*(const MyFVector3 &v, float value) {
    return MyFVector3(v.x * value, v.y * value, v.z * value);
}

FORCEINLINE MyFVector3 operator*(float value, const MyFVector3 &v) {
    return MyFVector3(v.x * value, v.y * value, v.z * value);
}

FORCEINLINE MyFVector3 operator/(const MyFVector3 &v, float value) {
    const float inv(1/value);
    return MyFVector3(v.x * inv, v.y * inv, v.z * inv);
}

FORCEINLINE MyFVector3 operator*(const MyFVector3 &lhs, const MyFVector3 &rhs) {
    return MyFVector3(lhs.y * rhs.z - lhs.z * rhs.y,
                        lhs.z * rhs.x - lhs.x * rhs.z,
                        lhs.x * rhs.y - lhs.y * rhs.x);
}

FORCEINLINE float* value_pointer(MyFVector3 &v) {
    return &v.x;
}

FORCEINLINE const float* value_pointer(const MyFVector3 &v) {
    return &v.x;
}

// MyFVector4 implementation

FORCEINLINE MyFVector4::MyFVector4(void) {}

FORCEINLINE MyFVector4::MyFVector4(float value):
x(value), y(value), z(value), w(value) {}

FORCEINLINE MyFVector4::MyFVector4(float vx,
                               float vy,
                               float vz,
                               float vw):
x(vx), y(vy), z(vz), w(vw) {}

FORCEINLINE MyFVector4::MyFVector4(const MyFVector4 &other):
x(other.x), y(other.y), z(other.z), w(other.w) {}

FORCEINLINE MyFVector4::MyFVector4(const MyFVector4 &&other):
x(other.x), y(other.y), z(other.z), w(other.w) {}

FORCEINLINE MyFVector4::~MyFVector4(void) {}

FORCEINLINE MyFVector4& MyFVector4::operator=(const MyFVector4 &other) {
    MINE_ASSERT2(this != &other, "MyFVector4::operator=, same object");
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
}

FORCEINLINE MyFVector4& MyFVector4::operator=(const MyFVector4 &&other) {
    MINE_ASSERT2(this != &other, "MyFVector4::operator=, same object");
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
}

FORCEINLINE bool MyFVector4::operator==(const MyFVector4 &other) const {
    return x == other.x && y == other.y && z == other.z && w == other.w;
}

FORCEINLINE bool MyFVector4::operator!=(const MyFVector4 &other) const {
    return x != other.x || y != other.y || z != other.z || w != other.w;
}

FORCEINLINE MyFVector4& MyFVector4::operator+=(const MyFVector4 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}

FORCEINLINE MyFVector4& MyFVector4::operator-=(const MyFVector4 &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
}

FORCEINLINE MyFVector4& MyFVector4::operator*=(float value) {
    x *= value;
    y *= value;
    z *= value;
    w *= value;
    return *this;
}

FORCEINLINE MyFVector4& MyFVector4::operator/=(float value) {
    const float inv(1/value);
    x *= inv;
    y *= inv;
    z *= inv;
    w *= inv;
    return *this;
}

FORCEINLINE MyFVector4 operator-(const MyFVector4 &v) {
    return MyFVector4(-v.x, -v.y, -v.z, -v.w);
}

FORCEINLINE MyFVector4 operator+(const MyFVector4 &lhs, const MyFVector4 &rhs) {
    return MyFVector4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}

FORCEINLINE MyFVector4 operator-(const MyFVector4 &lhs, const MyFVector4 &rhs) {
    return MyFVector4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
}

FORCEINLINE MyFVector4 operator*(const MyFVector4 &v, float value) {
    return MyFVector4(v.x * value, v.y * value, v.z * value, v.w * value);
}

FORCEINLINE MyFVector4 operator*(float value, const MyFVector4 &v) {
    return MyFVector4(v.x * value, v.y * value, v.z * value, v.w * value);
}

FORCEINLINE MyFVector4 operator/(const MyFVector4 &v, float value) {
    const float inv(1/value);
    return MyFVector4(v.x * inv, v.y * inv, v.z * inv, v.w * inv);
}

FORCEINLINE float* value_pointer(MyFVector4 &v) {
    return &v.x;
}

FORCEINLINE const float* value_pointer(const MyFVector4 &v) {
    return &v.x;
}

// basic operations of vector
FORCEINLINE float magnitudeVector(const MyFVector2 &vec) {
    return MyMathUtil::sqrt(magnitudeSquareVector(vec));
}

FORCEINLINE float magnitudeSquareVector(const MyFVector2 &vec) {
    return vec.x * vec.x + vec.y * vec.y;
}

FORCEINLINE float magnitudeVector(const MyFVector3 &vec) {
    return MyMathUtil::sqrt(magnitudeSquareVector(vec));
}

FORCEINLINE float magnitudeSquareVector(const MyFVector3 &vec) {
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

FORCEINLINE float magnitudeVector(const MyFVector4 &vec) {
    return MyMathUtil::sqrt(magnitudeSquareVector(vec));
}

FORCEINLINE float magnitudeSquareVector(const MyFVector4 &vec) {
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w;
}

FORCEINLINE MyFVector2 normalizeVector(const MyFVector2 &vec) {
    return vec/magnitudeVector(vec);
}

FORCEINLINE void normalizeVector(MyFVector2 &vec) {
    vec /= magnitudeVector(vec);
}

FORCEINLINE void normalizeVector(const MyFVector2 &inVec, MyFVector2 &outVec) {
    float mag = magnitudeVector(inVec);
    MINE_ASSERT2(!MyMathUtil::zero(mag), "normalizeVector, magnitude 0");
    mag = 1.0f/mag;
    outVec.x = inVec.x * mag;
    outVec.y = inVec.y * mag;
}

FORCEINLINE MyFVector3 normalizeVector(const MyFVector3 &vec) {
    return vec/magnitudeVector(vec);
}

FORCEINLINE void normalizeVector(MyFVector3 &vec) {
    vec /= magnitudeVector(vec);
}

FORCEINLINE void normalizeVector(const MyFVector3 &inVec, MyFVector3 &outVec) {
    float mag = magnitudeVector(inVec);
    MINE_ASSERT2(!MyMathUtil::zero(mag), "normalizeVector, magnitude 0");
    mag = 1.0f/mag;
    outVec.x = inVec.x * mag;
    outVec.y = inVec.y * mag;
    outVec.z = inVec.z * mag;
}

FORCEINLINE MyFVector4 normalizeVector(const MyFVector4 &vec) {
    return vec/magnitudeVector(vec);
}

FORCEINLINE void normalizeVector(MyFVector4 &vec) {
    vec /= magnitudeVector(vec);
}

FORCEINLINE void normalizeVector(const MyFVector4 &inVec, MyFVector4 &outVec) {
    float mag = magnitudeVector(inVec);
    MINE_ASSERT2(!MyMathUtil::zero(mag), "normalizeVector, magnitude 0");
    mag = 1.0f/mag;
    outVec.x = inVec.x * mag;
    outVec.y = inVec.y * mag;
    outVec.z = inVec.z * mag;
    outVec.w = inVec.w * mag;
}

FORCEINLINE float dotProduct(const MyFVector2 &a, const MyFVector2 &b) {
    return a.x * b.x + a.y * b.y;
}

FORCEINLINE float dotProduct(const MyFVector3 &a, const MyFVector3 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

FORCEINLINE float dotProduct(const MyFVector4 &a, const MyFVector4 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

FORCEINLINE void crossProduct(const MyFVector4 &a, const MyFVector4 &b, MyFVector3 &outVec) {
    outVec.x = a.y * b.z - a.z * b.y;
    outVec.y = a.z * b.x - a.x * b.z;
    outVec.z = a.x * b.y - a.y * b.x;
}

FORCEINLINE float radiusVector(const MyFVector2 &a, const MyFVector2 &b) {
    float ab = magnitudeVector(a) * magnitudeVector(b);
    return MyMathUtil::zero(ab) ? MyMathUtil::kMathPIOver2 : MyMathUtil::acos(dotProduct(a, b)/ab);
}

FORCEINLINE float radiusVector(const MyFVector3 &a, const MyFVector3 &b) {
    float ab = magnitudeVector(a) * magnitudeVector(b);
    return MyMathUtil::zero(ab) ? MyMathUtil::kMathPIOver2 : MyMathUtil::acos(dotProduct(a, b)/ab);
}

FORCEINLINE float radiusVector(const MyFVector4 &a, const MyFVector4 &b) {
    float ab = magnitudeVector(a) * magnitudeVector(b);
    return MyMathUtil::zero(ab) ? MyMathUtil::kMathPIOver2 : MyMathUtil::acos(dotProduct(a, b)/ab);
}

FORCEINLINE MyFVector3 projectVector(const MyFVector3 &a, const MyFVector3 &b) {
    MINE_ASSERT2(!MyMathUtil::zero(magnitudeSquareVector(b)), "projectVector, magnitude 0");
    float k = dotProduct(a, b)/magnitudeSquareVector(b);
    return MyFVector3(b.x * k, b.y * k, b.z * k);
}

FORCEINLINE void projectVector(MyFVector3 &a, const MyFVector3 &b) {
    MINE_ASSERT2(!MyMathUtil::zero(magnitudeSquareVector(b)), "projectVector, magnitude 0");
    float k = dotProduct(a, b)/magnitudeSquareVector(b);
    a.x = b.x * k;
    a.y = b.y * k;
    a.z = b.z * k;
}

FORCEINLINE void projectVector(const MyFVector3 &a, const MyFVector3 &b, MyFVector3 &outVec) {
    MINE_ASSERT2(!MyMathUtil::zero(magnitudeSquareVector(b)), "projectVector, magnitude 0");
    float k = dotProduct(a, b)/magnitudeSquareVector(b);
    outVec.x = b.x * k;
    outVec.y = b.y * k;
    outVec.z = b.z * k;
}

FORCEINLINE MyFVector3 projectNormalizedVector(const MyFVector3 &a, const MyFVector3 &b) {
    float k = dotProduct(a, b);
    return MyFVector3(b.x * k, b.y * k, b.z * k);
}

FORCEINLINE void projectNormalizedVector(MyFVector3 &a, const MyFVector3 &b) {
    float k = dotProduct(a, b);
    a.x = b.x * k;
    a.y = b.y * k;
    a.z = b.z * k;
}

FORCEINLINE void projectNormalizedVector(const MyFVector3 &a, const MyFVector3 &b, MyFVector3 &outVec) {
    float k = dotProduct(a, b);
    outVec.x = b.x * k;
    outVec.y = b.y * k;
    outVec.z = b.z * k;
}

MINE_NAMESPACE_END
