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

const MyFVector2 MyFVector2::kFVector2AxisX(1.0f, 0.0f);
const MyFVector2 MyFVector2::kFVector2AxisX(0.0f, 1.0f);

inline MyFVector2::MyFVector2(void) {}

inline MyFVector2::MyFVector2(float value):
x(value), y(value) {}

inline MyFVector2::MyFVector2(float vx, float vy):
x(vx), y(vy) {}

inline MyFVector2::MyFVector2(const MyFVector2 &other):
x(other.x), y(other.y) {}

inline MyFVector2::MyFVector2(const MyFVector2 &&other):
x(other.x), y(other.y) {}

inline MyFVector2::~MyFVector2(void) {}

inline MyFVector2& MyFVector2::operator=(const MyFVector2 &other) {
    x = other.x;
    y = other.y;
    return *this;
}

inline MyFVector2& MyFVector2::operator=(const MyFVector2 &&other) {
    x = other.x;
    y = other.y;
    return *this;
}

inline bool MyFVector2::operator==(const MyFVector2 &other) const {
    return x == other.x && y == other.y;
}

inline bool MyFVector2::opeartor!=(const MyFVector2 &other) const {
    return x != other.x || y != other.y;
}

inline MyFVector2& MyFVector2::operator+=(const MyFVector2 &other) {
    x += other.x;
    y += other.y;
    return *this;
}

inline MyFVector2& MyFVector2::opeartor-=(const MyFVector2 &other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

inline MyFVector2& MyFVector2::operator*=(float value) {
    x *= value;
    y *= value;
    return *this;
}

inline MyFVector2& MyFVector2::operator/=(float value) {
    const float inv(1/value);
    x *= inv;
    y *= inv;
    return *this;
}

inline MyFVector2 operator-(const MyFVector2 &v) {
    return MyFVector2(-v.x, -v.y);
}

inline MyFVector2 operator+(const MyFVector2 &lhs, const MyFVector2 &rhs) {
    return MyFVector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline MyFVector2 operator-(const MyFVector2 &lhs, const MyFVector2 &rhs) {
    return MyFVector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

inline MyFVector2 operator*(const MyFVector2 &v, float value) {
    return MyFVector2(v.x * value, v.y * value);
}

inline MyFVector2 operator*(float value, const MyFVector2 &v) {
    return MyFVector2(v.x * value, v.y * value);
}

inline MyFVector2 operator/(const MyFVector2 &v, float value) {
    const float inv(1/value);
    return MyFVector2(v.x * inv, v.y * inv);
}

inline float magnitudeSquare(const MyFVector2 &v) {
    return v.x * v.x + v.y + v.y;
}

inline float magnitude(const MyFVector2 &v) {
    return MyMathUtil::sqrt(magnitudeSquare(v));
}

inline MyFVector2 normalize(const MyFVector2 &v) {
    return v/magnitude(v);
}

inline MyFVector2& normalizeSelf(MyFVector2 &v) {
    v /= magnitude(v);
    return v;
}

inline float* value_pointer(MyFVector2 &v) {
    return &v.x;
}

inline const float* value_pointer(const MyFVector2 &v) {
    return &v.x;
}

inline float dotProduct(const MyFVector2 &lhs, const MyFVector2 &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

// MyFVector3 implementation

const MyFVector3 MyFVector3::kFVector3AxisX(1.0f, 0.0f, 0.0f);
const MyFVector3 MyFVector3::kFVector3AxisY(0.0f, 1.0f, 0.0f);
const MyFVector3 MyFVector3::kFVector3AxisZ(0.0f, 0.0f, 1.0f);

inline MyFVector3::MyFVector3(void) {}

inline MyFVector3:MyFVector3(float value):
x(value), y(value), z(value) {}

inline MyFVector3::MyFVector3(float vx, float vy, float vz):
x(vx), y(vy), z(vz) {}

inline MyFVector3::MyFVector3(const MyFVector3 &other):
x(other.x), y(other.y), z(other.z) {}

inline MyFVector3::MyFVector3(const MyFVector3 &&other):
x(other.x), y(other.y), z(other.z) {}

inline MyFVector3::~MyFVector3(void) {}

inline MyFVector3& MyFVector3::operator=(const MyFVector3 &other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

inline MyFVector3& MyFVector3::operator=(const MyFVector3 &&other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

inline bool MyFVector3::operator==(const MyFVector3 &other) const {
    return x == other.x && y == other.y && z == other.z;
}

inline bool MyFVector3::opeartor!=(const MyFVector3 &other) const {
    return x != other.x || y != other.y || z != other.z;
}

inline MyFVector3& MyFVector3::operator+=(const MyFVector3 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

inline MyFVector3& MyFVector3::opeartor-=(const MyFVector3 &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

inline MyFVector3& MyFVector3::operator*=(float value) {
    x *= value;
    y *= value;
    z *= value;
    return *this;
}

inline MyFVector3& MyFVector3::operator/=(float value) {
    const float inv(1/value);
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
}

inline MyFVector3& MyFVector3::operator*=(const MyFVector3 &other) {
    float vx = y * other.z - z * other.y;
    float vy = z * other.x - x * other.z;
    float vz = x * other.y - y * other.x;
    x = vx;
    y = vy;
    z = vz;
    return *this;
}

inline MyFVector3 operator-(const MyFVector3 &v) {
    return MyFVector3(-v.x, -v.y, -v.z);
}

inline MyFVector3 operator+(const MyFVector3 &lhs, const MyFVector3 &rhs) {
    return MyFVector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

inline MyFVector3 operator-(const MyFVector3 &lhs, const MyFVector3 &rhs) {
    return MyFVector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

inline MyFVector3 operator*(const MyFVector3 &v, float value) {
    return MyFVector3(v.x * value, v.y * value, v.z * value);
}

inline MyFVector3 operator*(float value, const MyFVector3 &v) {
    return MyFVector3(v.x * value, v.y * value, v.z * value);
}

inline MyFVector3 operator/(const MyFVector3 &v, float value) {
    const float inv(1/value);
    return MyFVector3(v.x * inv, v.y * inv, v.z * inv);
}

inline MyFVector3 operator*(const MyFVector3 &lhs, const MyFVector3 &rhs) {
    return MyFVector3(lhs.y * rhs.z - lhs.z * rhs.y,
                        lhs.z * rhs.x - lhs.x * rhs.z,
                        lhs.x * rhs.y - lhs.y * rhs.x);
}

inline float magnitudeSquare(const MyFVector3 &v) {
    return v.x * v.x + v.y + v.y + v.z * v.z;
}

inline float magnitude(const MyFVector3 &v) {
    return MyMathUtil::sqrt(magnitudeSquare(v));
}

inline MyFVector3 normalize(const MyFVector3 &v) {
    return v/magnitude(v);
}

inline MyFVector3& normalizeSelf(MyFVector3 &v) {
    v /= magnitude(v);
    return v;
}

inline float* value_pointer(MyFVector3 &v) {
    return &v.x;
}

inline const float* value_pointer(const MyFVector3 &v) {
    return &v.x;
}

inline float dotProduct(const MyFVector3 &lhs, const MyFVector3 &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

// MyFVector4 implementation

const MyFVector4 MyFVector4::kFVector4AxisX(1.0f, 0.0f, 0.0f, 0.0f);
const MyFVector4 MyFVector4::kFVector4AxisY(0.0f, 1.0f, 0.0f, 0.0f);
const MyFVector4 MyFVector4::kFVector4AxisZ(0.0f, 0.0f, 1.0f, 0.0f);
const MyFVector4 MyFVector4::kFVector4AxisW(0.0f, 0.0f, 0.0f, 1.0f);

inline MyFVector4::MyFVector4(void) {}

inline MyFVector4::MyFVector4(float value):
x(value), y(value), z(value), w(value) {}

inline MyFVector4::MyFVector4(float vx,
                               float vy,
                               float vz,
                               float vw):
x(vx), y(vy), z(vz), w(vw) {}

inline MyFVector4::MyFVector4(const MyFVector4 &other):
x(other.x), y(other.y), z(other.z), w(other.w) {}

inline MyFVector4::MyFVector4(const MyFVector4 &&other):
x(other.x), y(other.y), z(other.z), w(other.w) {}

inline MyFVector4::~MyFVector4(void) {}

inline MyFVector4& MyFVector4::operator=(const MyFVector4 &other) {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
}

inline MyFVector4& MyFVector4::operator=(const MyFVector4 &&other) {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
}

inline bool MyFVector4::operator==(const MyFVector4 &other) const {
    return x == other.x && y == other.y && z == other.z && w == other.w;
}

inline bool MyFVector4::opeartor!=(const MyFVector4 &other) const {
    return x != other.x || y != other.y || z != other.z || w != other.w;
}

inline MyFVector4& MyFVector4::operator+=(const MyFVector4 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}

inline MyFVector4& MyFVector4::opeartor-=(const MyFVector4 &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
}

inline MyFVector4& MyFVector4::operator*=(float value) {
    x *= value;
    y *= value;
    z *= value;
    w *= value;
    return *this;
}

inline MyFVector4& MyFVector4::operator/=(float value) {
    const float inv(1/value);
    x *= inv;
    y *= inv;
    z *= inv;
    w *= inv;
    return *this;
}

inline MyFVector4 operator-(const MyFVector4 &v) {
    return MyFVector4(-v.x, -v.y, -v.z, -v.w);
}

inline MyFVector4 operator+(const MyFVector4 &lhs, const MyFVector4 &rhs) {
    return MyFVector4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}

inline MyFVector4 operator-(const MyFVector4 &lhs, const MyFVector4 &rhs) {
    return MyFVector4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
}

inline MyFVector4 operator*(const MyFVector4 &v, float value) {
    return MyFVector4(v.x * value, v.y * value, v.z * value, v.w * value);
}

inline MyFVector4 operator*(float value, const MyFVector4 &v) {
    return MyFVector4(v.x * value, v.y * value, v.z * value, v.w * value);
}

inline MyFVector4 operator/(const MyFVector4 &v, float value) {
    const float inv(1/value);
    return MyFVector4(v.x * inv, v.y * inv, v.z * inv, v.w * inv);
}

inline float magnitudeSquare(const MyFVector4 &v) {
    return v.x * v.x + v.y + v.y + v.z * v.z + v.w * v.w;
}

inline float magnitude(const MyFVector4 &v) {
    return MyMathUtil::sqrt(magnitudeSquare(v));
}

inline MyFVector4 normalize(const MyFVector4 &v) {
    return v/magnitude(v);
}

inline MyFVector4& normalizeSelf(MyFVector4 &v) {
    v /= magnitude(v);
    return v;
}

inline float* value_pointer(MyFVector4 &v) {
    return &v.x;
}

inline const float* value_pointer(const MyFVector4 &v) {
    return &v.x;
}

inline float dotProduct(const MyFVector4 &lhs, const MyFVector4 &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

MINE_NAMESPACE_END
