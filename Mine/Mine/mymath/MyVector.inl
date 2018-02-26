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
    x = other.x;
    y = other.y;
    return *this;
}

FORCEINLINE MyFVector2& MyFVector2::operator=(const MyFVector2 &&other) {
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
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

FORCEINLINE MyFVector3& MyFVector3::operator=(const MyFVector3 &&other) {
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
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
}

FORCEINLINE MyFVector4& MyFVector4::operator=(const MyFVector4 &&other) {
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

MINE_NAMESPACE_END
