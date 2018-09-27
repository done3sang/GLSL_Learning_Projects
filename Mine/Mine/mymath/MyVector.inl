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

FORCEINLINE MyFVector3::MyFVector3(const MyFVector2& vec2):
x(vec2.x), y(vec2.y), z(0.0f) {}

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
    return MyMathUtil::equal(x, other.x) && MyMathUtil::equal(y, other.y) && MyMathUtil::equal(z, other.z);
    //return x == other.x && y == other.y && z == other.z;
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

FORCEINLINE MyFVector4::MyFVector4(const MyFVector3& vec3):
x(vec3.x), y(vec3.y), z(vec3.z), w(1.0f) {}

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
FORCEINLINE float magnitudeSquareVector(const MyFVector2 &vec) {
    return vec.x * vec.x + vec.y * vec.y;
}

FORCEINLINE float magnitudeVector(const MyFVector2 &vec) {
    return MyMathUtil::sqrt(magnitudeSquareVector(vec));
}

FORCEINLINE float magnitudeSquareVector(const MyFVector3 &vec) {
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

FORCEINLINE float magnitudeVector(const MyFVector3 &vec) {
    return MyMathUtil::sqrt(magnitudeSquareVector(vec));
}

FORCEINLINE float magnitudeSquareVector(const MyFVector4 &vec) {
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w;
}

FORCEINLINE float magnitudeVector(const MyFVector4 &vec) {
    return MyMathUtil::sqrt(magnitudeSquareVector(vec));
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

FORCEINLINE bool vectorNormalized(const MyFVector2 &vec) {
    return MyMathUtil::identity(magnitudeSquareVector(vec));
}

FORCEINLINE MyFVector2 normalizeVector(const MyFVector2 &vec) {
    MyFVector2 ret;
    normalizeVector(vec, ret);
    return ret;
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

FORCEINLINE bool vectorNormalized(const MyFVector3 &vec) {
    return MyMathUtil::identity(magnitudeSquareVector(vec));
}

FORCEINLINE MyFVector3 normalizeVector(const MyFVector3 &vec) {
    MyFVector3 ret;
    normalizeVector(vec, ret);
    return ret;
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

FORCEINLINE bool vectorNormalized(const MyFVector4 &vec) {
    return MyMathUtil::identity(magnitudeSquareVector(vec));
}

FORCEINLINE MyFVector4 normalizeVector(const MyFVector4 &vec) {
    MyFVector4 ret;
    normalizeVector(vec, ret);
    return ret;
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

// p = dot(v, n)/dot(n, n) *n
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

FORCEINLINE MyFVector3 projectVector(const MyFVector3 &a, const MyFVector3 &b) {
    MyFVector3 ret;
    projectVector(a, b, ret);
    return ret;
}

FORCEINLINE void projectNormalizedVector(MyFVector3 &a, const MyFVector3 &b) {
    MINE_ASSERT2(MyMathUtil::identity(magnitudeSquareVector(b)), "projectNormalizedVector, vector not normalized");
    float k = dotProduct(a, b);
    a.x = b.x * k;
    a.y = b.y * k;
    a.z = b.z * k;
}

FORCEINLINE void projectNormalizedVector(const MyFVector3 &a, const MyFVector3 &b, MyFVector3 &outVec) {
    MINE_ASSERT2(MyMathUtil::identity(magnitudeSquareVector(b)), "projectNormalizedVector, vector not normalized");
    float k = dotProduct(a, b);
    outVec.x = b.x * k;
    outVec.y = b.y * k;
    outVec.z = b.z * k;
}

FORCEINLINE MyFVector3 projectNormalizedVector(const MyFVector3 &a, const MyFVector3 &b) {
    MyFVector3 ret;
    projectNormalizedVector(a, b, ret);
    return ret;
}

// p = dot(v, n)/dot(n, n) *n, q = v - p
FORCEINLINE void perpendicularVector(MyFVector3 &a, const MyFVector3 &b) {
    MINE_ASSERT2(!MyMathUtil::zero(magnitudeSquareVector(b)), "perpendicularVector, magnitude 0");
    float k = dotProduct(a, b)/magnitudeSquareVector(b);
    a.x -= b.x * k;
    a.y -= b.y * k;
    a.z -= b.z * k;
}

FORCEINLINE void perpendicularVector(const MyFVector3 &a, const MyFVector3 &b, MyFVector3 &outVec) {
    MINE_ASSERT2(!MyMathUtil::zero(magnitudeSquareVector(b)), "perpendicularVector, magnitude 0");
    float k = dotProduct(a, b)/magnitudeSquareVector(b);
    outVec.x = a.x - b.x * k;
    outVec.y = a.y - b.y * k;
    outVec.z = a.z - b.z * k;
}

FORCEINLINE MyFVector3 perpendicularVector(const MyFVector3 &a, const MyFVector3 &b) {
    MyFVector3 ret;
    perpendicularVector(a, b, ret);
    return ret;
}

FORCEINLINE void perpendicularNormalizedVector(MyFVector3 &a, const MyFVector3 &b) {
    MINE_ASSERT2(MyMathUtil::identity(magnitudeSquareVector(b)), "perpendicularNormalizedVector, vector not normalized");
    float k = dotProduct(a, b);
    a.x -= b.x * k;
    a.y -= b.y * k;
    a.z -= b.z * k;
}

FORCEINLINE void perpendicularNormalizedVector(const MyFVector3 &a, const MyFVector3 &b, MyFVector3 &outVec) {
    MINE_ASSERT2(MyMathUtil::identity(magnitudeSquareVector(b)), "perpendicularNormalizedVector, vector not normalized");
    float k = dotProduct(a, b);
    outVec.x = a.x - b.x * k;
    outVec.y = a.x - b.y * k;
    outVec.z = a.x - b.z * k;
}

FORCEINLINE MyFVector3 perpendicularNormalizedVector(const MyFVector3 &a, const MyFVector3 &b) {
    MyFVector3 ret;
    perpendicularNormalizedVector(a, b, ret);
    return ret;
}

FORCEINLINE void partitionVector(const MyFVector3 &a,
                                 const MyFVector3 &b,
                                 MyFVector3 &projVec,
                                 MyFVector3 &perpVec) {
    MINE_ASSERT2(!MyMathUtil::zero(magnitudeSquareVector(b)), "partitionVector, magnitude 0");
    float k = dotProduct(a, b)/magnitudeSquareVector(b);
    projVec.x = b.x * k;
    projVec.y = b.y * k;
    projVec.z = b.z * k;
    perpVec.x = a.x - projVec.x;
    perpVec.y = a.y - projVec.y;
    perpVec.z = a.z - projVec.z;
}

FORCEINLINE void partitionNormalizedVector(const MyFVector3 &a,
                                           const MyFVector3 &b,
                                           MyFVector3 &projVec,
                                           MyFVector3 &perpVec) {
    MINE_ASSERT2(MyMathUtil::identity(magnitudeSquareVector(b)), "partitionNormalizedVector, vector not normalized");
    float k = dotProduct(a, b);
    projVec.x = b.x * k;
    projVec.y = b.y * k;
    projVec.z = b.z * k;
    perpVec.x = a.x - projVec.x;
    perpVec.y = a.y - projVec.y;
    perpVec.z = a.z - projVec.z;
}

FORCEINLINE void schmidtVector(MyFVector3 &a,
                               MyFVector3 &b,
                               MyFVector3 &c) {
    normalizeVector(a);
    normalizeVector(b);
    normalizeVector(c);
    float kab = dotProduct(a, b);
    float kbc = dotProduct(b, c);
    float kca = dotProduct(c, a);
    b.x -= kab * a.x;
    b.y -= kab * a.y;
    b.z -= kab * a.z;
    c.x -= kca * a.x + kbc * b.x;
    c.y -= kca * a.y + kbc * b.y;
    c.z -= kca * a.z + kbc * b.z;
}

FORCEINLINE bool vectorOrthogonal(const MyFVector2 &vec1, const MyFVector2 &vec2) {
    return MyMathUtil::zero(dotProduct(vec1, vec2));
}

FORCEINLINE bool vectorOrthogonal(const MyFVector3 &vec1, const MyFVector3 &vec2) {
    return MyMathUtil::zero(dotProduct(vec1, vec2));
}

FORCEINLINE bool vectorOrthogonal(const MyFVector4 &vec1, const MyFVector4 &vec2) {
    return MyMathUtil::zero(dotProduct(vec1, vec2));
}

FORCEINLINE float distanceSquareVector(const MyFVector2 &a, const MyFVector2 &b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return dx * dx + dy * dy;
}

FORCEINLINE float distanceSquareVector(const MyFVector3 &a, const MyFVector3 &b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float dz = a.z - b.z;
    return dx * dx + dy * dy + dz * dz;
}

FORCEINLINE float distanceSquareVector(const MyFVector4 &a, const MyFVector4 &b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float dz = a.z - b.z;
    float dw = a.w - b.w;
    return dx * dx + dy * dy + dz * dz + dw * dw;
}

FORCEINLINE float distanceVector(const MyFVector2 &a, const MyFVector2 &b) {
    return MyMathUtil::sqrt(distanceSquareVector(a, b));
}

FORCEINLINE float distanceVector(const MyFVector3 &a, const MyFVector3 &b) {
    return MyMathUtil::sqrt(distanceSquareVector(a, b));
}

FORCEINLINE float distanceVector(const MyFVector4 &a, const MyFVector4 &b) {
    return MyMathUtil::sqrt(distanceSquareVector(a, b));
}

MINE_NAMESPACE_END
