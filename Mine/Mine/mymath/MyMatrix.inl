//
//  MyMatrix2.inl
//  Mine
//
//  Created by xy on 23/02/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#include "MyMathUtil.hpp"

MINE_NAMESPACE_BEGIN

// MyFMatrix2 implementation

FORCEINLINE MyFMatrix2::MyFMatrix2(void) {}

FORCEINLINE MyFMatrix2::~MyFMatrix2(void) {}

FORCEINLINE MyFMatrix2::MyFMatrix2(float value) {
    _value[0][0] = value; _value[0][1] = 0.0f;
    _value[1][0] = 0.0f; _value[1][1] = value;
}

FORCEINLINE MyFMatrix2::MyFMatrix2(float in00, float in01, float in10, float in11) {
    _value[0][0] = in00; _value[0][1] = in01;
    _value[1][0] = in10; _value[1][1] = in11;
}

FORCEINLINE MyFMatrix2::MyFMatrix2(const MyFMatrix2 &other) {
    _value[0][0] = other._value[0][0];
    _value[0][1] = other._value[0][1];
    _value[1][0] = other._value[1][0];
    _value[1][1] = other._value[1][1];
}

FORCEINLINE MyFMatrix2::MyFMatrix2(const MyFMatrix2 &&other) {
    _value[0][0] = other._value[0][0];
    _value[0][1] = other._value[0][1];
    _value[1][0] = other._value[1][0];
    _value[1][1] = other._value[1][1];
}

FORCEINLINE MyFMatrix2::MyFMatrix2(const std::initializer_list<float> &il) {
    auto initIter(il.begin());
    auto initEnd(il.end());
    _value[0][0] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[0][1] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[1][0] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[1][1] = (initIter != initEnd) ? *(initIter++) : 0.0f;
}

FORCEINLINE MyFMatrix2& MyFMatrix2::operator=(const MyFMatrix2 &other) {
    MINE_ASSERT2(this != &other, "MyFMatrix2::operator=, same object");
    _value[0][0] = other._value[0][0];
    _value[0][1] = other._value[0][1];
    _value[1][0] = other._value[1][0];
    _value[1][1] = other._value[1][1];
    return *this;
}

FORCEINLINE MyFMatrix2& MyFMatrix2::operator=(const MyFMatrix2 &&other) {
    MINE_ASSERT2(this != &other, "MyFMatrix2::operator=, same object");
    _value[0][0] = other._value[0][0];
    _value[0][1] = other._value[0][1];
    _value[1][0] = other._value[1][0];
    _value[1][1] = other._value[1][1];
    return *this;
}

FORCEINLINE MyFMatrix2& MyFMatrix2::operator=(const std::initializer_list<float> &il) {
    auto initIter(il.begin());
    auto initEnd(il.end());
    _value[0][0] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[0][1] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[1][0] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[1][1] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    return *this;
}

FORCEINLINE bool MyFMatrix2::operator==(const MyFMatrix2 &other) const {
    return _value[0][0] == other._value[0][0] &&
    _value[0][1] == other._value[0][1] &&
    _value[1][0] == other._value[1][0] &&
    _value[1][1] == other._value[1][1];
}

FORCEINLINE bool MyFMatrix2::operator!=(const MyFMatrix2 &other) const {
    return _value[0][0] != other._value[0][0] ||
    _value[0][1] != other._value[0][1] ||
    _value[1][0] != other._value[1][0] ||
    _value[1][1] != other._value[1][1];
}

FORCEINLINE MyFMatrix2& MyFMatrix2::operator+=(const MyFMatrix2 &other) {
    _value[0][0] += other._value[0][0];
    _value[0][1] += other._value[0][1];
    _value[1][0] += other._value[1][0];
    _value[1][1] += other._value[1][1];
    return *this;
}

FORCEINLINE MyFMatrix2& MyFMatrix2::operator-=(const MyFMatrix2 &other) {
    _value[0][0] -= other._value[0][0];
    _value[0][1] -= other._value[0][1];
    _value[1][0] -= other._value[1][0];
    _value[1][1] -= other._value[1][1];
    return *this;
}

FORCEINLINE MyFMatrix2& MyFMatrix2::operator*=(float value) {
    _value[0][0] *= value;
    _value[0][1] *= value;
    _value[1][0] *= value;
    _value[1][1] *= value;
    return *this;
}

FORCEINLINE MyFMatrix2& MyFMatrix2::operator/=(float value) {
    MINE_ASSERT2(!MyMathUtil::zero(value), "MyFMatrix2::operator/=, value be 0");
    value = 1.0f/value;
    _value[0][0] *= value;
    _value[0][1] *= value;
    _value[1][0] *= value;
    _value[1][1] *= value;
    return *this;
}

FORCEINLINE MyFMatrix2& MyFMatrix2::operator*=(const MyFMatrix2 &other) {
    float out00 = _value[0][0] * other._value[0][0] + _value[0][1] * other._value[1][0];
    float out01 = _value[0][0] * other._value[0][1] + _value[0][1] * other._value[1][1];
    float out10 = _value[1][0] * other._value[0][0] + _value[1][1] * other._value[1][0];
    float out11 = _value[1][0] * other._value[0][1] + _value[1][1] * other._value[1][1];
    _value[0][0] = out00; _value[0][1] = out01;
    _value[1][0] = out10; _value[1][1] = out11;
    return *this;
}

FORCEINLINE float& MyFMatrix2::valueAt(int x, int y) {
    MINE_ASSERT2(0 <= x && x <= 1, "MyFMatrix2::valueAt, index(x) out of range");
    MINE_ASSERT2(0 <= y && y <= 1, "MyFMatrix2::valueAt, index(y) out of range");
    return _value[x][y];
}

FORCEINLINE const float& MyFMatrix2::valueAt(int x, int y) const {
    MINE_ASSERT2(0 <= x && x <= 1, "MyFMatrix2::valueAt, index(x) out of range");
    MINE_ASSERT2(0 <= y && y <= 1, "MyFMatrix2::valueAt, index(y) out of range");
    return _value[x][y];
}

FORCEINLINE float MyFMatrix2::determinant(void) const {
    return _value[0][0] * _value[1][1] - _value[0][1] * _value[1][0];
}

FORCEINLINE bool MyFMatrix2::inversible(void) const {
    return !MyMathUtil::zero(determinant());
}

FORCEINLINE MyFMatrix2 operator-(const MyFMatrix2 &mat) {
    return MyFMatrix2(-mat.valueAt(0, 0),
                      -mat.valueAt(0, 1),
                      -mat.valueAt(1, 0),
                      -mat.valueAt(1, 1));
}

FORCEINLINE MyFMatrix2 operator+(const MyFMatrix2 &lhs, const MyFMatrix2 &rhs) {
    return MyFMatrix2(lhs.valueAt(0, 0) + rhs.valueAt(0, 0),
                      lhs.valueAt(0, 1) + rhs.valueAt(0, 1),
                      lhs.valueAt(1, 0) + rhs.valueAt(1, 0),
                      lhs.valueAt(1, 1) + rhs.valueAt(1, 1));
}

FORCEINLINE MyFMatrix2 operator-(const MyFMatrix2 &lhs, const MyFMatrix2 &rhs) {
    return MyFMatrix2(lhs.valueAt(0, 0) - rhs.valueAt(0, 0),
                      lhs.valueAt(0, 1) - rhs.valueAt(0, 1),
                      lhs.valueAt(1, 0) - rhs.valueAt(1, 0),
                      lhs.valueAt(1, 1) - rhs.valueAt(1, 1));
}

FORCEINLINE MyFMatrix2 operator*(const MyFMatrix2 &mat, float value) {
    return MyFMatrix2(mat.valueAt(0, 0) * value,
                      mat.valueAt(0, 1) * value,
                      mat.valueAt(1, 0) * value,
                      mat.valueAt(1, 1) * value);
}

FORCEINLINE MyFMatrix2 operator*(float value, const MyFMatrix2 &mat) {
    return MyFMatrix2(mat.valueAt(0, 0) * value,
                      mat.valueAt(0, 1) * value,
                      mat.valueAt(1, 0) * value,
                      mat.valueAt(1, 1) * value);
}

FORCEINLINE MyFMatrix2 operator/(const MyFMatrix2 &mat, float value) {
    MINE_ASSERT2(!MyMathUtil::zero(value), "operator/, value be zero");
    value = 1.0f/value;
    return MyFMatrix2(mat.valueAt(0, 0) * value,
                      mat.valueAt(0, 1) * value,
                      mat.valueAt(1, 0) * value,
                      mat.valueAt(1, 1) * value);
}

FORCEINLINE MyFMatrix2 operator*(const MyFMatrix2 &lhs, const MyFMatrix2 &rhs) {
    return MyFMatrix2(lhs.valueAt(0, 0) * rhs.valueAt(0, 0) + lhs.valueAt(0, 1) * rhs.valueAt(1, 0),
                      lhs.valueAt(0, 0) * rhs.valueAt(0, 1) + lhs.valueAt(0, 1) * rhs.valueAt(1, 1),
                      lhs.valueAt(1, 0) * rhs.valueAt(0, 0) + lhs.valueAt(1, 1) * rhs.valueAt(1, 0),
                      lhs.valueAt(1, 0) * rhs.valueAt(0, 1) + lhs.valueAt(1, 1) * rhs.valueAt(1, 1));
}

FORCEINLINE float* value_pointer(MyFMatrix2 &mat) {
    return &mat.valueAt(0, 0);
}

FORCEINLINE const float* value_pointer(const MyFMatrix2 &mat) {
    return &mat.valueAt(0, 0);
}

// MyFMatrix3 implementation

FORCEINLINE MyFMatrix3::MyFMatrix3(void) {}

FORCEINLINE MyFMatrix3::~MyFMatrix3(void) {}

FORCEINLINE MyFMatrix3::MyFMatrix3(float value) {
    _value[0][0] = value; _value[0][1] = 0.0f; _value[0][2] = 0.0f;
    _value[1][0] = 0.0f; _value[1][1] = value;  _value[1][2] = 0.0f;
    _value[2][0] = 0.0f; _value[2][1] = 0.0f; _value[2][2] = value;
}

FORCEINLINE MyFMatrix3::MyFMatrix3(float in00, float in01, float in02,
                                   float in10, float in11, float in12,
                                   float in20, float in21, float in22) {
    _value[0][0] = in00; _value[0][1] = in01; _value[0][2] = in02;
    _value[1][0] = in10; _value[1][1] = in11; _value[1][2] = in12;
    _value[2][0] = in20; _value[2][1] = in21; _value[2][2] = in22;
}

FORCEINLINE MyFMatrix3::MyFMatrix3(const MyFMatrix3 &other) {
    MINE_ASSERT2(this != &other, "MyFMatrix3::operator=, same object");
    _value[0][0] = other._value[0][0];
    _value[0][1] = other._value[0][1];
    _value[0][2] = other._value[0][2];
    _value[1][0] = other._value[1][0];
    _value[1][1] = other._value[1][1];
    _value[1][2] = other._value[1][2];
    _value[2][0] = other._value[2][0];
    _value[2][1] = other._value[2][1];
    _value[2][2] = other._value[2][2];
}

FORCEINLINE MyFMatrix3::MyFMatrix3(const MyFMatrix3 &&other) {
    MINE_ASSERT2(this != &other, "MyFMatrix3::operator=, same object");
    _value[0][0] = other._value[0][0];
    _value[0][1] = other._value[0][1];
    _value[0][2] = other._value[0][2];
    _value[1][0] = other._value[1][0];
    _value[1][1] = other._value[1][1];
    _value[1][2] = other._value[1][2];
    _value[2][0] = other._value[2][0];
    _value[2][1] = other._value[2][1];
    _value[2][2] = other._value[2][2];
}

FORCEINLINE MyFMatrix3::MyFMatrix3(const std::initializer_list<float> &il) {
    auto initIter(il.begin());
    auto initEnd(il.end());
    _value[0][0] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[0][1] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[0][2] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[1][0] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[1][1] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[1][2] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[2][0] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[2][1] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[2][2] = (initIter != initEnd) ? *(initIter++) : 0.0f;
}

FORCEINLINE MyFMatrix3& MyFMatrix3::operator=(const MyFMatrix3 &other) {
    _value[0][0] = other._value[0][0];
    _value[0][1] = other._value[0][1];
    _value[0][2] = other._value[0][2];
    _value[1][0] = other._value[1][0];
    _value[1][1] = other._value[1][1];
    _value[1][2] = other._value[1][2];
    _value[2][0] = other._value[2][0];
    _value[2][1] = other._value[2][1];
    _value[2][2] = other._value[2][2];
    return *this;
}

FORCEINLINE MyFMatrix3& MyFMatrix3::operator=(const MyFMatrix3 &&other) {
    _value[0][0] = other._value[0][0];
    _value[0][1] = other._value[0][1];
    _value[0][2] = other._value[0][2];
    _value[1][0] = other._value[1][0];
    _value[1][1] = other._value[1][1];
    _value[1][2] = other._value[1][2];
    _value[2][0] = other._value[2][0];
    _value[2][1] = other._value[2][1];
    _value[2][2] = other._value[2][2];
    return *this;
}

FORCEINLINE MyFMatrix3& MyFMatrix3::operator=(const std::initializer_list<float> &il) {
    auto initIter(il.begin());
    auto initEnd(il.end());
    _value[0][0] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[0][1] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[0][2] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[1][0] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[1][1] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[1][2] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[2][0] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[2][1] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[2][2] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    return *this;
}

FORCEINLINE bool MyFMatrix3::operator==(const MyFMatrix3 &other) const {
    return _value[0][0] == other._value[0][0] &&
    _value[0][1] == other._value[0][1] &&
    _value[0][2] == other._value[0][2] &&
    _value[1][0] == other._value[1][0] &&
    _value[1][1] == other._value[1][1] &&
    _value[1][2] == other._value[1][2] &&
    _value[2][0] == other._value[2][0] &&
    _value[2][1] == other._value[2][1] &&
    _value[2][2] == other._value[2][2];
}

FORCEINLINE bool MyFMatrix3::operator!=(const MyFMatrix3 &other) const {
    return _value[0][0] != other._value[0][0] ||
    _value[0][1] != other._value[0][1] ||
    _value[0][2] != other._value[0][2] ||
    _value[1][0] != other._value[1][0] ||
    _value[1][1] != other._value[1][1] ||
    _value[1][2] != other._value[1][2] ||
    _value[2][0] != other._value[2][0] ||
    _value[2][1] != other._value[2][1] ||
    _value[2][2] != other._value[2][2];
}

FORCEINLINE MyFMatrix3& MyFMatrix3::operator+=(const MyFMatrix3 &other) {
    _value[0][0] += other._value[0][0];
    _value[0][1] += other._value[0][1];
    _value[0][2] += other._value[0][2];
    _value[1][0] += other._value[1][0];
    _value[1][1] += other._value[1][1];
    _value[1][2] += other._value[1][2];
    _value[2][0] += other._value[2][0];
    _value[2][1] += other._value[2][1];
    _value[2][2] += other._value[2][2];
    return *this;
}

FORCEINLINE MyFMatrix3& MyFMatrix3::operator-=(const MyFMatrix3 &other) {
    _value[0][0] -= other._value[0][0];
    _value[0][1] -= other._value[0][1];
    _value[0][2] -= other._value[0][2];
    _value[1][0] -= other._value[1][0];
    _value[1][1] -= other._value[1][1];
    _value[1][2] -= other._value[1][2];
    _value[2][0] -= other._value[2][0];
    _value[2][1] -= other._value[2][1];
    _value[2][2] -= other._value[2][2];
    return *this;
}

FORCEINLINE MyFMatrix3& MyFMatrix3::operator*=(float value) {
    _value[0][0] *= value;
    _value[0][1] *= value;
    _value[0][2] *= value;
    _value[1][0] *= value;
    _value[1][1] *= value;
    _value[1][2] *= value;
    _value[2][0] *= value;
    _value[2][1] *= value;
    _value[2][2] *= value;
    return *this;
}

FORCEINLINE MyFMatrix3& MyFMatrix3::operator/=(float value) {
    MINE_ASSERT2(!MyMathUtil::zero(value), "MyFMatrix2::operator/=, value be 0");
    value = 1.0f/value;
    _value[0][0] *= value;
    _value[0][1] *= value;
    _value[0][2] *= value;
    _value[1][0] *= value;
    _value[1][1] *= value;
    _value[1][2] *= value;
    _value[2][0] *= value;
    _value[2][1] *= value;
    _value[2][2] *= value;
    return *this;
}

FORCEINLINE MyFMatrix3& MyFMatrix3::operator*=(const MyFMatrix3 &other) {
    float out00 = _value[0][0] * other._value[0][0] + _value[0][1] * other._value[1][0] + _value[0][2] * other._value[2][0];
    float out01 = _value[0][0] * other._value[0][1] + _value[0][1] * other._value[1][1] + _value[0][2] * other._value[2][1];
    float out02 = _value[0][0] * other._value[0][2] + _value[0][1] * other._value[1][2] + _value[0][2] * other._value[2][2];
    float out10 = _value[1][0] * other._value[0][0] + _value[1][1] * other._value[1][0] + _value[1][2] * other._value[2][0];
    float out11 = _value[1][0] * other._value[0][1] + _value[1][1] * other._value[1][1] + _value[1][2] * other._value[2][1];
    float out12 = _value[1][0] * other._value[0][2] + _value[1][1] * other._value[1][2] + _value[1][2] * other._value[2][2];
    float out20 = _value[2][0] * other._value[0][0] + _value[2][1] * other._value[1][0] + _value[2][2] * other._value[2][0];
    float out21 = _value[2][0] * other._value[0][1] + _value[2][1] * other._value[1][1] + _value[2][2] * other._value[2][1];
    float out22 = _value[2][0] * other._value[0][2] + _value[2][1] * other._value[1][2] + _value[2][2] * other._value[2][2];
    _value[0][0] = out00; _value[0][1] = out01; _value[0][2] = out02;
    _value[1][0] = out10; _value[1][1] = out11; _value[1][2] = out12;
    _value[2][0] = out20; _value[2][1] = out21; _value[2][2] = out22;
    return *this;
}

FORCEINLINE float& MyFMatrix3::valueAt(int x, int y) {
    MINE_ASSERT2(0 <= x && x <= 2, "MyFMatrix3::valueAt, index(x) out of range");
    MINE_ASSERT2(0 <= y && y <= 2, "MyFMatrix3::valueAt, index(y) out of range");
    return _value[x][y];
}

FORCEINLINE const float& MyFMatrix3::valueAt(int x, int y) const {
    MINE_ASSERT2(0 <= x && x <= 2, "MyFMatrix3::valueAt, index(x) out of range");
    MINE_ASSERT2(0 <= y && y <= 2, "MyFMatrix3::valueAt, index(y) out of range");
    return _value[x][y];
}

FORCEINLINE float MyFMatrix3::determinant(void) const {
    return _value[0][0] * (_value[1][1] * _value[2][2] - _value[1][2] * _value[2][1]) -
    _value[0][1] * (_value[1][0] * _value[2][2] - _value[1][2] * _value[2][0])
    + _value[0][2] * (_value[1][0] * _value[2][1] - _value[1][1] * _value[2][0]);
}

FORCEINLINE bool MyFMatrix3::inversible(void) const {
    return !MyMathUtil::zero(determinant());
}

FORCEINLINE MyFMatrix3 operator-(const MyFMatrix3 &mat) {
    return MyFMatrix3(-mat.valueAt(0, 0), -mat.valueAt(0, 1), -mat.valueAt(0, 2),
                      -mat.valueAt(1, 0), -mat.valueAt(1, 1), -mat.valueAt(1, 2),
                      -mat.valueAt(2, 0), -mat.valueAt(2, 1), -mat.valueAt(2, 2));
}

FORCEINLINE MyFMatrix3 operator+(const MyFMatrix3 &lhs, const MyFMatrix3 &rhs) {
    return MyFMatrix3(lhs.valueAt(0, 0) + rhs.valueAt(0, 0),
                      lhs.valueAt(0, 1) + rhs.valueAt(0, 1),
                      lhs.valueAt(0, 2) + rhs.valueAt(0, 2),
                      lhs.valueAt(1, 0) + rhs.valueAt(1, 0),
                      lhs.valueAt(1, 1) + rhs.valueAt(1, 1),
                      lhs.valueAt(1, 2) + rhs.valueAt(1, 2),
                      lhs.valueAt(2, 0) + rhs.valueAt(2, 0),
                      lhs.valueAt(2, 1) + rhs.valueAt(2, 1),
                      lhs.valueAt(2, 2) + rhs.valueAt(2, 2));
}

FORCEINLINE MyFMatrix3 operator-(const MyFMatrix3 &lhs, const MyFMatrix3 &rhs) {
    return MyFMatrix3(lhs.valueAt(0, 0) - rhs.valueAt(0, 0),
                      lhs.valueAt(0, 1) - rhs.valueAt(0, 1),
                      lhs.valueAt(0, 2) - rhs.valueAt(0, 2),
                      lhs.valueAt(1, 0) - rhs.valueAt(1, 0),
                      lhs.valueAt(1, 1) - rhs.valueAt(1, 1),
                      lhs.valueAt(1, 2) - rhs.valueAt(1, 2),
                      lhs.valueAt(2, 0) - rhs.valueAt(2, 0),
                      lhs.valueAt(2, 1) - rhs.valueAt(2, 1),
                      lhs.valueAt(2, 2) - rhs.valueAt(2, 2));
}

FORCEINLINE MyFMatrix3 operator*(const MyFMatrix3 &mat, float value) {
    return MyFMatrix3(mat.valueAt(0, 0) * value,
                      mat.valueAt(0, 1) * value,
                      mat.valueAt(0, 2) * value,
                      mat.valueAt(1, 0) * value,
                      mat.valueAt(1, 1) * value,
                      mat.valueAt(1, 2) * value,
                      mat.valueAt(2, 0) * value,
                      mat.valueAt(2, 1) * value,
                      mat.valueAt(2, 2) * value);
}

FORCEINLINE MyFMatrix3 operator*(float value, const MyFMatrix3 &mat) {
    return MyFMatrix3(mat.valueAt(0, 0) * value,
                      mat.valueAt(0, 1) * value,
                      mat.valueAt(0, 2) * value,
                      mat.valueAt(1, 0) * value,
                      mat.valueAt(1, 1) * value,
                      mat.valueAt(1, 2) * value,
                      mat.valueAt(2, 0) * value,
                      mat.valueAt(2, 1) * value,
                      mat.valueAt(2, 2) * value);
}

FORCEINLINE MyFMatrix3 operator/(const MyFMatrix3 &mat, float value) {
    MINE_ASSERT2(!MyMathUtil::zero(value), "operator/, value be zero");
    value = 1.0f/value;
    return MyFMatrix3(mat.valueAt(0, 0) * value,
                      mat.valueAt(0, 1) * value,
                      mat.valueAt(0, 2) * value,
                      mat.valueAt(1, 0) * value,
                      mat.valueAt(1, 1) * value,
                      mat.valueAt(1, 2) * value,
                      mat.valueAt(2, 0) * value,
                      mat.valueAt(2, 1) * value,
                      mat.valueAt(2, 2) * value);
}

FORCEINLINE MyFMatrix3 operator*(const MyFMatrix3 &lhs, const MyFMatrix3 &rhs) {
    return MyFMatrix3(lhs.valueAt(0, 0) * rhs.valueAt(0, 0) + lhs.valueAt(0, 1) * rhs.valueAt(1, 0) + lhs.valueAt(0, 2) * rhs.valueAt(2, 0),
                      lhs.valueAt(0, 0) * rhs.valueAt(0, 1) + lhs.valueAt(0, 1) * rhs.valueAt(1, 1) + lhs.valueAt(0, 2) * rhs.valueAt(2, 1),
                      lhs.valueAt(0, 0) * rhs.valueAt(0, 2) + lhs.valueAt(0, 1) * rhs.valueAt(1, 2) + lhs.valueAt(0, 2) * rhs.valueAt(2, 2),
                      lhs.valueAt(1, 0) * rhs.valueAt(0, 0) + lhs.valueAt(0, 1) * rhs.valueAt(1, 0) + lhs.valueAt(1, 2) * rhs.valueAt(2, 0),
                      lhs.valueAt(1, 0) * rhs.valueAt(0, 1) + lhs.valueAt(0, 1) * rhs.valueAt(1, 1) + lhs.valueAt(1, 2) * rhs.valueAt(2, 1),
                      lhs.valueAt(1, 0) * rhs.valueAt(0, 2) + lhs.valueAt(0, 1) * rhs.valueAt(1, 2) + lhs.valueAt(1, 2) * rhs.valueAt(2, 2),
                      lhs.valueAt(2, 0) * rhs.valueAt(0, 0) + lhs.valueAt(2, 1) * rhs.valueAt(1, 0) + lhs.valueAt(2, 2) * rhs.valueAt(2, 0),
                      lhs.valueAt(2, 0) * rhs.valueAt(0, 1) + lhs.valueAt(2, 1) * rhs.valueAt(1, 1) + lhs.valueAt(2, 2) * rhs.valueAt(2, 1),
                      lhs.valueAt(2, 0) * rhs.valueAt(0, 2) + lhs.valueAt(2, 1) * rhs.valueAt(1, 2) + lhs.valueAt(2, 2) * rhs.valueAt(2, 2));
}

FORCEINLINE float* value_pointer(MyFMatrix3 &mat) {
    return &mat.valueAt(0, 0);
}

FORCEINLINE const float* value_pointer(const MyFMatrix3 &mat) {
    return &mat.valueAt(0, 0);
}

// MyFMatrix4 implementation

FORCEINLINE MyFMatrix4::MyFMatrix4(void) {}

FORCEINLINE MyFMatrix4::~MyFMatrix4(void) {}

FORCEINLINE MyFMatrix4::MyFMatrix4(float value) {
    _value[0][0] = value; _value[0][1] = 0.0f; _value[0][2] = 0.0f; _value[0][3] = 0.0f;
    _value[1][0] = 0.0f; _value[1][1] = value;  _value[1][2] = 0.0f; _value[1][3] = 0.0f;
    _value[2][0] = 0.0f; _value[2][1] = 0.0f; _value[2][2] = value; _value[2][3] = 0.0f;
    _value[3][0] = 0.0f; _value[3][1] = 0.0f; _value[3][2] = 0.0f; _value[3][3] = value;
}

FORCEINLINE MyFMatrix4::MyFMatrix4(float in00, float in01, float in02, float in03,
                                   float in10, float in11, float in12, float in13,
                                   float in20, float in21, float in22, float in23,
                                   float in30, float in31, float in32, float in33) {
    _value[0][0] = in00; _value[0][1] = in01; _value[0][2] = in02; _value[0][3] = in03;
    _value[1][0] = in10; _value[1][1] = in11; _value[1][2] = in12; _value[1][3] = in13;
    _value[2][0] = in20; _value[2][1] = in21; _value[2][2] = in22; _value[2][3] = in23;
    _value[3][0] = in30; _value[3][1] = in31; _value[3][2] = in32; _value[3][3] = in33;
}

FORCEINLINE MyFMatrix4::MyFMatrix4(const MyFMatrix4 &other) {
    _value[0][0] = other._value[0][0];
    _value[0][1] = other._value[0][1];
    _value[0][2] = other._value[0][2];
    _value[0][3] = other._value[0][3];
    _value[1][0] = other._value[1][0];
    _value[1][1] = other._value[1][1];
    _value[1][2] = other._value[1][2];
    _value[1][3] = other._value[1][3];
    _value[2][0] = other._value[2][0];
    _value[2][1] = other._value[2][1];
    _value[2][2] = other._value[2][2];
    _value[2][3] = other._value[2][3];
    _value[3][0] = other._value[3][0];
    _value[3][1] = other._value[3][1];
    _value[3][2] = other._value[3][2];
    _value[3][3] = other._value[3][3];
}

FORCEINLINE MyFMatrix4::MyFMatrix4(const MyFMatrix4 &&other) {
    _value[0][0] = other._value[0][0];
    _value[0][1] = other._value[0][1];
    _value[0][2] = other._value[0][2];
    _value[0][3] = other._value[0][3];
    _value[1][0] = other._value[1][0];
    _value[1][1] = other._value[1][1];
    _value[1][2] = other._value[1][2];
    _value[1][3] = other._value[1][3];
    _value[2][0] = other._value[2][0];
    _value[2][1] = other._value[2][1];
    _value[2][2] = other._value[2][2];
    _value[2][3] = other._value[2][3];
    _value[3][0] = other._value[3][0];
    _value[3][1] = other._value[3][1];
    _value[3][2] = other._value[3][2];
    _value[3][3] = other._value[3][3];
}

FORCEINLINE MyFMatrix4::MyFMatrix4(const std::initializer_list<float> &il) {
    auto initIter(il.begin());
    auto initEnd(il.end());
    _value[0][0] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[0][1] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[0][2] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[0][3] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[1][0] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[1][1] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[1][2] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[1][3] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[2][0] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[2][1] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[2][2] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[2][3] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[3][0] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[3][1] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[3][2] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[3][3] = (initIter != initEnd) ? *(initIter++) : 0.0f;
}

FORCEINLINE MyFMatrix4& MyFMatrix4::operator=(const MyFMatrix4 &other) {
    MINE_ASSERT2(this != &other, "MyFMatrix4::operator=, same object");
    _value[0][0] = other._value[0][0];
    _value[0][1] = other._value[0][1];
    _value[0][2] = other._value[0][2];
    _value[0][3] = other._value[0][3];
    _value[1][0] = other._value[1][0];
    _value[1][1] = other._value[1][1];
    _value[1][2] = other._value[1][2];
    _value[1][3] = other._value[1][3];
    _value[2][0] = other._value[2][0];
    _value[2][1] = other._value[2][1];
    _value[2][2] = other._value[2][2];
    _value[2][3] = other._value[2][3];
    _value[3][0] = other._value[3][0];
    _value[3][1] = other._value[3][1];
    _value[3][2] = other._value[3][2];
    _value[3][3] = other._value[3][3];
    return *this;
}

FORCEINLINE MyFMatrix4& MyFMatrix4::operator=(const MyFMatrix4 &&other) {
    MINE_ASSERT2(this != &other, "MyFMatrix4::operator=, same object");
    _value[0][0] = other._value[0][0];
    _value[0][1] = other._value[0][1];
    _value[0][2] = other._value[0][2];
    _value[0][3] = other._value[0][3];
    _value[1][0] = other._value[1][0];
    _value[1][1] = other._value[1][1];
    _value[1][2] = other._value[1][2];
    _value[1][3] = other._value[1][3];
    _value[2][0] = other._value[2][0];
    _value[2][1] = other._value[2][1];
    _value[2][2] = other._value[2][2];
    _value[2][3] = other._value[2][3];
    _value[3][0] = other._value[3][0];
    _value[3][1] = other._value[3][1];
    _value[3][2] = other._value[3][2];
    _value[3][3] = other._value[3][3];
    return *this;
}

FORCEINLINE MyFMatrix4& MyFMatrix4::operator=(const std::initializer_list<float> &il) {
    auto initIter(il.begin());
    auto initEnd(il.end());
    _value[0][0] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[0][1] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[0][2] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[0][3] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[1][0] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[1][1] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[1][2] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[1][3] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[2][0] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[2][1] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[2][2] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[2][3] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[3][0] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[3][1] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[3][2] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    _value[3][3] = (initIter != initEnd) ? *(initIter++) : 0.0f;
    return *this;
}

FORCEINLINE bool MyFMatrix4::operator==(const MyFMatrix4 &other) const {
    return _value[0][0] == other._value[0][0] &&
    _value[0][1] == other._value[0][1] &&
    _value[0][2] == other._value[0][2] &&
    _value[0][3] == other._value[0][3] &&
    _value[1][0] == other._value[1][0] &&
    _value[1][1] == other._value[1][1] &&
    _value[1][2] == other._value[1][2] &&
    _value[1][3] == other._value[1][3] &&
    _value[2][0] == other._value[2][0] &&
    _value[2][1] == other._value[2][1] &&
    _value[2][2] == other._value[2][2] &&
    _value[2][3] == other._value[2][3] &&
    _value[3][0] == other._value[3][0] &&
    _value[3][1] == other._value[3][1] &&
    _value[3][2] == other._value[3][2] &&
    _value[3][3] == other._value[3][3];
}

FORCEINLINE bool MyFMatrix4::operator!=(const MyFMatrix4 &other) const {
    return _value[0][0] != other._value[0][0] ||
    _value[0][1] != other._value[0][1] ||
    _value[0][2] != other._value[0][2] ||
    _value[0][3] != other._value[0][3] ||
    _value[1][0] != other._value[1][0] ||
    _value[1][1] != other._value[1][1] ||
    _value[1][2] != other._value[1][2] ||
    _value[1][3] != other._value[1][3] ||
    _value[2][0] != other._value[2][0] ||
    _value[2][1] != other._value[2][1] ||
    _value[2][2] != other._value[2][2] ||
    _value[2][3] != other._value[2][3] ||
    _value[3][0] != other._value[3][0] ||
    _value[3][1] != other._value[3][1] ||
    _value[3][2] != other._value[3][2] ||
    _value[3][3] != other._value[3][3];
}

FORCEINLINE MyFMatrix4& MyFMatrix4::operator+=(const MyFMatrix4 &other) {
    _value[0][0] += other._value[0][0];
    _value[0][1] += other._value[0][1];
    _value[0][2] += other._value[0][2];
    _value[0][3] += other._value[0][3];
    _value[1][0] += other._value[1][0];
    _value[1][1] += other._value[1][1];
    _value[1][2] += other._value[1][2];
    _value[1][3] += other._value[1][3];
    _value[2][0] += other._value[2][0];
    _value[2][1] += other._value[2][1];
    _value[2][2] += other._value[2][2];
    _value[2][3] += other._value[2][3];
    _value[3][0] += other._value[3][0];
    _value[3][1] += other._value[3][1];
    _value[3][2] += other._value[3][2];
    _value[3][3] += other._value[3][3];
    return *this;
}

FORCEINLINE MyFMatrix4& MyFMatrix4::operator-=(const MyFMatrix4 &other) {
    _value[0][0] -= other._value[0][0];
    _value[0][1] -= other._value[0][1];
    _value[0][2] -= other._value[0][2];
    _value[0][3] -= other._value[0][3];
    _value[1][0] -= other._value[1][0];
    _value[1][1] -= other._value[1][1];
    _value[1][2] -= other._value[1][2];
    _value[1][3] -= other._value[1][3];
    _value[2][0] -= other._value[2][0];
    _value[2][1] -= other._value[2][1];
    _value[2][2] -= other._value[2][2];
    _value[2][3] -= other._value[2][3];
    _value[3][0] -= other._value[3][0];
    _value[3][1] -= other._value[3][1];
    _value[3][2] -= other._value[3][2];
    _value[3][3] -= other._value[3][3];
    return *this;
}

FORCEINLINE MyFMatrix4& MyFMatrix4::operator*=(float value) {
    _value[0][0] *= value;
    _value[0][1] *= value;
    _value[0][2] *= value;
    _value[0][3] *= value;
    _value[1][0] *= value;
    _value[1][1] *= value;
    _value[1][2] *= value;
    _value[1][3] *= value;
    _value[2][0] *= value;
    _value[2][1] *= value;
    _value[2][2] *= value;
    _value[2][3] *= value;
    _value[3][0] *= value;
    _value[3][1] *= value;
    _value[3][2] *= value;
    _value[3][3] *= value;
    return *this;
}

FORCEINLINE MyFMatrix4& MyFMatrix4::operator/=(float value) {
    MINE_ASSERT2(!MyMathUtil::zero(value), "MyFMatrix2::operator/=, value be 0");
    value = 1.0f/value;
    _value[0][0] *= value;
    _value[0][1] *= value;
    _value[0][2] *= value;
    _value[0][3] *= value;
    _value[1][0] *= value;
    _value[1][1] *= value;
    _value[1][2] *= value;
    _value[1][3] *= value;
    _value[2][0] *= value;
    _value[2][1] *= value;
    _value[2][2] *= value;
    _value[2][3] *= value;
    _value[3][0] *= value;
    _value[3][1] *= value;
    _value[3][2] *= value;
    _value[3][3] *= value;
    return *this;
}

FORCEINLINE MyFMatrix4& MyFMatrix4::operator*=(const MyFMatrix4 &other) {
    float out00 = _value[0][0] * other._value[0][0] + _value[0][1] * other._value[1][0] +
    _value[0][2] * other._value[2][0] + _value[0][3] * other._value[3][0];
    float out01 = _value[0][0] * other._value[0][1] + _value[0][1] * other._value[1][1] +
    _value[0][2] * other._value[2][1] + _value[0][3] * other._value[3][1];
    float out02 = _value[0][0] * other._value[0][2] + _value[0][1] * other._value[1][2] +
    _value[0][2] * other._value[2][2] + _value[0][3] * other._value[3][2];
    float out03 = _value[0][0] * other._value[0][3] + _value[0][1] * other._value[1][3] +
    _value[0][2] * other._value[2][3] + _value[0][3] * other._value[3][3];
    float out10 = _value[1][0] * other._value[0][0] + _value[1][1] * other._value[1][0] +
    _value[1][2] * other._value[2][0] + _value[1][3] * other._value[3][0];
    float out11 = _value[1][0] * other._value[0][1] + _value[1][1] * other._value[1][1] +
    _value[1][2] * other._value[2][1] + _value[1][3] * other._value[3][1];
    float out12 = _value[1][0] * other._value[0][2] + _value[1][1] * other._value[1][2] +
    _value[1][2] * other._value[2][2] + _value[1][3] * other._value[3][2];
    float out13 = _value[1][0] * other._value[0][3] + _value[1][1] * other._value[1][3] +
    _value[1][2] * other._value[2][3] + _value[1][3] * other._value[3][3];
    float out20 = _value[2][0] * other._value[0][0] + _value[2][1] * other._value[1][0] +
    _value[2][2] * other._value[2][0] + _value[2][3] * other._value[3][0];
    float out21 = _value[2][0] * other._value[0][1] + _value[2][1] * other._value[1][1] +
    _value[2][2] * other._value[2][1] + _value[2][3] * other._value[3][1];
    float out22 = _value[2][0] * other._value[0][2] + _value[2][1] * other._value[1][2] +
    _value[2][2] * other._value[2][2] + _value[2][3] * other._value[3][2];
    float out23 = _value[2][0] * other._value[0][3] + _value[2][1] * other._value[1][3] +
    _value[2][2] * other._value[2][3] + _value[2][3] * other._value[3][3];
    float out30 = _value[3][0] * other._value[0][0] + _value[3][1] * other._value[1][0] +
    _value[3][2] * other._value[2][0] + _value[3][3] * other._value[3][0];
    float out31 = _value[3][0] * other._value[0][1] + _value[3][1] * other._value[1][1] +
    _value[3][2] * other._value[2][1] + _value[3][3] * other._value[3][1];
    float out32 = _value[3][0] * other._value[0][2] + _value[3][1] * other._value[1][2] +
    _value[3][2] * other._value[2][2] + _value[3][3] * other._value[3][2];
    float out33 = _value[3][0] * other._value[0][3] + _value[3][1] * other._value[1][3] +
    _value[3][2] * other._value[2][3] + _value[3][3] * other._value[3][3];
    _value[0][0] = out00; _value[0][1] = out01; _value[0][2] = out02; _value[0][3] = out03;
    _value[1][0] = out10; _value[1][1] = out11; _value[1][2] = out12; _value[1][3] = out13;
    _value[2][0] = out20; _value[2][1] = out21; _value[2][2] = out22; _value[2][3] = out23;
    _value[3][0] = out30; _value[3][1] = out31; _value[3][2] = out32; _value[3][3] = out33;
    return *this;
}

FORCEINLINE float& MyFMatrix4::valueAt(int x, int y) {
    MINE_ASSERT2(0 <= x && x <= 3, "MyFMatrix4::valueAt, index(x) out of range");
    MINE_ASSERT2(0 <= y && y <= 3, "MyFMatrix4::valueAt, index(y) out of range");
    return _value[x][y];
}

FORCEINLINE const float& MyFMatrix4::valueAt(int x, int y) const {
    MINE_ASSERT2(0 <= x && x <= 3, "MyFMatrix4::valueAt, index(x) out of range");
    MINE_ASSERT2(0 <= y && y <= 3, "MyFMatrix4::valueAt, index(y) out of range");
    return _value[x][y];
}

FORCEINLINE float MyFMatrix4::determinant(void) const {
    float det01 = _value[2][2] * _value[3][3] - _value[2][3] * _value[3][2];
    float det23 = _value[2][1] * _value[3][3] - _value[2][3] * _value[3][1];
    float det45 = _value[2][1] * _value[3][2] - _value[2][2] * _value[3][1];
    float det67 = _value[2][0] * _value[3][3] - _value[2][3] * _value[3][0];
    float det89 = _value[2][0] * _value[3][2] - _value[2][2] * _value[3][0];
    float detab = _value[2][0] * _value[3][1] - _value[2][1] * _value[3][0];
    return _value[0][0] * (_value[1][1] * det01 -
                           _value[1][2] * det23 +
                           _value[1][3] * det45) -
    _value[0][1] * (_value[1][0] * det01 -
                    _value[1][2] * det67 +
                    _value[1][3] * det89) +
    _value[0][2] * (_value[1][0] * det23 -
                    _value[1][1] * det67 +
                    _value[1][3] * detab) -
    _value[0][3] * (_value[1][0] * det45 -
                    _value[1][1] * det89 +
                    _value[1][2] * detab);
}

FORCEINLINE bool MyFMatrix4::inversible(void) const {
    return !MyMathUtil::zero(determinant());
}

FORCEINLINE MyFMatrix4 operator-(const MyFMatrix4 &mat) {
    return MyFMatrix4(-mat.valueAt(0, 0), -mat.valueAt(0, 1), -mat.valueAt(0, 2), -mat.valueAt(0, 3),
                      -mat.valueAt(1, 0), -mat.valueAt(1, 1), -mat.valueAt(1, 2), -mat.valueAt(1, 3),
                      -mat.valueAt(2, 0), -mat.valueAt(2, 1), -mat.valueAt(2, 2), -mat.valueAt(2, 3),
                      -mat.valueAt(3, 0), -mat.valueAt(3, 1), -mat.valueAt(3, 2), -mat.valueAt(3, 3));
}

FORCEINLINE MyFMatrix4 operator+(const MyFMatrix4 &lhs, const MyFMatrix4 &rhs) {
    return MyFMatrix4(lhs.valueAt(0, 0) + rhs.valueAt(0, 0),
                      lhs.valueAt(0, 1) + rhs.valueAt(0, 1),
                      lhs.valueAt(0, 2) + rhs.valueAt(0, 2),
                      lhs.valueAt(0, 3) + rhs.valueAt(0, 3),
                      lhs.valueAt(1, 0) + rhs.valueAt(1, 0),
                      lhs.valueAt(1, 1) + rhs.valueAt(1, 1),
                      lhs.valueAt(1, 2) + rhs.valueAt(1, 2),
                      lhs.valueAt(1, 3) + rhs.valueAt(1, 3),
                      lhs.valueAt(2, 0) + rhs.valueAt(2, 0),
                      lhs.valueAt(2, 1) + rhs.valueAt(2, 1),
                      lhs.valueAt(2, 2) + rhs.valueAt(2, 2),
                      lhs.valueAt(2, 3) + rhs.valueAt(2, 3),
                      lhs.valueAt(3, 0) + rhs.valueAt(3, 0),
                      lhs.valueAt(3, 1) + rhs.valueAt(3, 1),
                      lhs.valueAt(3, 2) + rhs.valueAt(3, 2),
                      lhs.valueAt(3, 3) + rhs.valueAt(3, 3));
}

FORCEINLINE MyFMatrix4 operator-(const MyFMatrix4 &lhs, const MyFMatrix4 &rhs) {
    return MyFMatrix4(lhs.valueAt(0, 0) - rhs.valueAt(0, 0),
                      lhs.valueAt(0, 1) - rhs.valueAt(0, 1),
                      lhs.valueAt(0, 2) - rhs.valueAt(0, 2),
                      lhs.valueAt(0, 3) - rhs.valueAt(0, 3),
                      lhs.valueAt(1, 0) - rhs.valueAt(1, 0),
                      lhs.valueAt(1, 1) - rhs.valueAt(1, 1),
                      lhs.valueAt(1, 2) - rhs.valueAt(1, 2),
                      lhs.valueAt(1, 3) - rhs.valueAt(1, 3),
                      lhs.valueAt(2, 0) - rhs.valueAt(2, 0),
                      lhs.valueAt(2, 1) - rhs.valueAt(2, 1),
                      lhs.valueAt(2, 2) - rhs.valueAt(2, 2),
                      lhs.valueAt(2, 3) - rhs.valueAt(2, 3),
                      lhs.valueAt(3, 0) - rhs.valueAt(3, 0),
                      lhs.valueAt(3, 1) - rhs.valueAt(3, 1),
                      lhs.valueAt(3, 2) - rhs.valueAt(3, 2),
                      lhs.valueAt(3, 3) - rhs.valueAt(3, 3));
}

FORCEINLINE MyFMatrix4 operator*(const MyFMatrix4 &mat, float value) {
    return MyFMatrix4(mat.valueAt(0, 0) * value,
                      mat.valueAt(0, 1) * value,
                      mat.valueAt(0, 2) * value,
                      mat.valueAt(0, 3) * value,
                      mat.valueAt(1, 0) * value,
                      mat.valueAt(1, 1) * value,
                      mat.valueAt(1, 2) * value,
                      mat.valueAt(1, 3) * value,
                      mat.valueAt(2, 0) * value,
                      mat.valueAt(2, 1) * value,
                      mat.valueAt(2, 2) * value,
                      mat.valueAt(2, 3) * value,
                      mat.valueAt(3, 0) * value,
                      mat.valueAt(3, 1) * value,
                      mat.valueAt(3, 2) * value,
                      mat.valueAt(3, 3) * value);
}

FORCEINLINE MyFMatrix4 operator*(float value, const MyFMatrix4 &mat) {
    return MyFMatrix4(mat.valueAt(0, 0) * value,
                      mat.valueAt(0, 1) * value,
                      mat.valueAt(0, 2) * value,
                      mat.valueAt(0, 3) * value,
                      mat.valueAt(1, 0) * value,
                      mat.valueAt(1, 1) * value,
                      mat.valueAt(1, 2) * value,
                      mat.valueAt(1, 3) * value,
                      mat.valueAt(2, 0) * value,
                      mat.valueAt(2, 1) * value,
                      mat.valueAt(2, 2) * value,
                      mat.valueAt(2, 3) * value,
                      mat.valueAt(3, 0) * value,
                      mat.valueAt(3, 1) * value,
                      mat.valueAt(3, 2) * value,
                      mat.valueAt(3, 3) * value);
}

FORCEINLINE MyFMatrix4 operator/(const MyFMatrix4 &mat, float value) {
    MINE_ASSERT2(!MyMathUtil::zero(value), "operator/, value be zero");
    value = 1.0f/value;
    return MyFMatrix4(mat.valueAt(0, 0) * value,
                      mat.valueAt(0, 1) * value,
                      mat.valueAt(0, 2) * value,
                      mat.valueAt(0, 3) * value,
                      mat.valueAt(1, 0) * value,
                      mat.valueAt(1, 1) * value,
                      mat.valueAt(1, 2) * value,
                      mat.valueAt(1, 3) * value,
                      mat.valueAt(2, 0) * value,
                      mat.valueAt(2, 1) * value,
                      mat.valueAt(2, 2) * value,
                      mat.valueAt(2, 3) * value,
                      mat.valueAt(3, 0) * value,
                      mat.valueAt(3, 1) * value,
                      mat.valueAt(3, 2) * value,
                      mat.valueAt(3, 3) * value);
}

FORCEINLINE MyFMatrix4 operator*(const MyFMatrix4 &lhs, const MyFMatrix4 &rhs) {
    return MyFMatrix4(lhs.valueAt(0, 0) * rhs.valueAt(0, 0) + lhs.valueAt(0, 1) * rhs.valueAt(1, 0) +
                      lhs.valueAt(0, 2) * rhs.valueAt(2, 0) + lhs.valueAt(0, 3) * rhs.valueAt(3, 0),
                      lhs.valueAt(0, 0) * rhs.valueAt(0, 1) + lhs.valueAt(0, 1) * rhs.valueAt(1, 1) +
                      lhs.valueAt(0, 2) * rhs.valueAt(2, 1) + lhs.valueAt(0, 3) * rhs.valueAt(3, 1),
                      lhs.valueAt(0, 0) * rhs.valueAt(0, 2) + lhs.valueAt(0, 1) * rhs.valueAt(1, 2) +
                      lhs.valueAt(0, 2) * rhs.valueAt(2, 2) + lhs.valueAt(0, 3) * rhs.valueAt(3, 2),
                      lhs.valueAt(0, 0) * rhs.valueAt(0, 3) + lhs.valueAt(0, 1) * rhs.valueAt(1, 3) +
                      lhs.valueAt(0, 2) * rhs.valueAt(2, 3) + lhs.valueAt(0, 3) * rhs.valueAt(3, 3),
                      lhs.valueAt(1, 0) * rhs.valueAt(0, 0) + lhs.valueAt(1, 1) * rhs.valueAt(1, 0) +
                      lhs.valueAt(1, 2) * rhs.valueAt(2, 0) + lhs.valueAt(1, 3) * rhs.valueAt(3, 0),
                      lhs.valueAt(1, 0) * rhs.valueAt(0, 1) + lhs.valueAt(1, 1) * rhs.valueAt(1, 1) +
                      lhs.valueAt(1, 2) * rhs.valueAt(2, 1) + lhs.valueAt(1, 3) * rhs.valueAt(3, 1),
                      lhs.valueAt(1, 0) * rhs.valueAt(0, 2) + lhs.valueAt(1, 1) * rhs.valueAt(1, 2) +
                      lhs.valueAt(1, 2) * rhs.valueAt(2, 2) + lhs.valueAt(1, 3) * rhs.valueAt(3, 2),
                      lhs.valueAt(1, 0) * rhs.valueAt(0, 3) + lhs.valueAt(1, 1) * rhs.valueAt(1, 3) +
                      lhs.valueAt(1, 2) * rhs.valueAt(2, 3) + lhs.valueAt(1, 3) * rhs.valueAt(3, 3),
                      lhs.valueAt(2, 0) * rhs.valueAt(0, 0) + lhs.valueAt(2, 1) * rhs.valueAt(1, 0) +
                      lhs.valueAt(2, 2) * rhs.valueAt(2, 0) + lhs.valueAt(2, 3) * rhs.valueAt(3, 0),
                      lhs.valueAt(2, 0) * rhs.valueAt(0, 1) + lhs.valueAt(2, 1) * rhs.valueAt(1, 1) +
                      lhs.valueAt(2, 2) * rhs.valueAt(2, 1) + lhs.valueAt(2, 3) * rhs.valueAt(3, 1),
                      lhs.valueAt(2, 0) * rhs.valueAt(0, 2) + lhs.valueAt(2, 1) * rhs.valueAt(1, 2) +
                      lhs.valueAt(2, 2) * rhs.valueAt(2, 2) + lhs.valueAt(2, 3) * rhs.valueAt(3, 2),
                      lhs.valueAt(2, 0) * rhs.valueAt(0, 3) + lhs.valueAt(2, 1) * rhs.valueAt(1, 3) +
                      lhs.valueAt(2, 2) * rhs.valueAt(2, 3) + lhs.valueAt(2, 3) * rhs.valueAt(3, 3),
                      lhs.valueAt(3, 0) * rhs.valueAt(0, 0) + lhs.valueAt(3, 1) * rhs.valueAt(1, 0) +
                      lhs.valueAt(3, 2) * rhs.valueAt(2, 0) + lhs.valueAt(3, 3) * rhs.valueAt(3, 0),
                      lhs.valueAt(3, 0) * rhs.valueAt(0, 1) + lhs.valueAt(3, 1) * rhs.valueAt(1, 1) +
                      lhs.valueAt(3, 2) * rhs.valueAt(2, 1) + lhs.valueAt(3, 3) * rhs.valueAt(3, 1),
                      lhs.valueAt(3, 0) * rhs.valueAt(0, 2) + lhs.valueAt(3, 1) * rhs.valueAt(1, 2) +
                      lhs.valueAt(3, 2) * rhs.valueAt(2, 2) + lhs.valueAt(3, 3) * rhs.valueAt(3, 2),
                      lhs.valueAt(3, 0) * rhs.valueAt(0, 3) + lhs.valueAt(3, 1) * rhs.valueAt(1, 3) +
                      lhs.valueAt(3, 2) * rhs.valueAt(2, 3) + lhs.valueAt(3, 3) * rhs.valueAt(3, 3));
}

FORCEINLINE float* value_pointer(MyFMatrix4 &mat) {
    return &mat.valueAt(0, 0);
}

FORCEINLINE const float* value_pointer(const MyFMatrix4 &mat) {
    return &mat.valueAt(0, 0);
}

// basic operations of matrix
namespace {
    // swap matrix row
    template<class M, int D, int I>
    struct LinearMatrixSwapRowImpl {
        enum {
            Continue = I != D - 1,
            NextI = I + 1
        };
        
        static FORCEINLINE void eval(M &mat, int x, int y, int index) {
            MINE_ASSERT2(index <= D, "MatrixSwapRowImpl, index out of range");
            float temp = mat.valueAt(x, index);
            mat.valueAt(x, index) = mat.valueAt(y, index);
            mat.valueAt(y, index) = temp;
            ++index;
            if(D != index) {
                LinearMatrixSwapRowImpl<M, D * Continue, NextI * Continue>::eval(mat, x, y, index);
            }
        }
    };
    
    template<class M>
    struct LinearMatrixSwapRowImpl<M, 0, 0> {
        static FORCEINLINE void eval(M&, int, int, int) {}
    };
    
    template<class M, int D>
    FORCEINLINE void linearMatrixSwapRow(M &mat, int x, int y, int startIndex) {
        LinearMatrixSwapRowImpl<M, D, 0>::eval(mat, x, y, startIndex);
    }
    
    // multiply matrix row
    template<class M, int D, int I>
    struct LinearMatrixMultiplyRowImpl {
        enum {
            Continue = I != D - 1,
            NextI = I + 1
        };
        
        static FORCEINLINE void eval(M &mat, int x, float multiple, int index) {
            MINE_ASSERT2(index <= D, "MatrixMultiplyRowImpl, index out of range");
            mat.valueAt(x, index) *= multiple;
            ++index;
            if(D != index) {
                LinearMatrixMultiplyRowImpl<M, D * Continue,
                NextI * Continue>::eval(mat, x, multiple, index);
            }
        }
    };
    
    template<class M>
    struct LinearMatrixMultiplyRowImpl<M, 0, 0> {
        static FORCEINLINE void eval(M&, int, float, int) {}
    };
    
    template<class M, int D>
    FORCEINLINE void linearMatrixMultiplyRow(M &mat, int x, float multiple, int startIndex) {
        LinearMatrixMultiplyRowImpl<M, D, 0>::eval(mat, x, multiple, startIndex);
    }
    
    // substract matrix row, x -= y * multiple
    template<class M, int D, int I>
    struct LinearMatrixSubstractRowImpl {
        enum {
            Continue = I != D - 1,
            NextI = I + 1
        };
        
        static float temp;
        
        static FORCEINLINE void eval(M &mat, int x, int y, float multiple, int index) {
            MINE_ASSERT2(index <= D, "MatrixSubstractRowImpl, index out of range");
            mat.valueAt(x, index) -= mat.valueAt(y, index) * multiple;
            ++index;
            if(D != index) {
                LinearMatrixSubstractRowImpl<M, D * Continue,
                NextI * Continue>::eval(mat, x, y, multiple, index);
            }
        }
    };
    
    template<class M>
    struct LinearMatrixSubstractRowImpl<M, 0, 0> {
        static FORCEINLINE void eval(M&, int, int, float, int) {}
    };
    
    template<class M, int D>
    FORCEINLINE void linearMatrixSubstractRow(M &mat,
                                              int x,
                                              int y,
                                              float multiple,
                                              int startIndex) {
        LinearMatrixSubstractRowImpl<M, D, 0>::eval(mat, x, y, multiple, startIndex);
    }
    
    // swap matrix column
    template<class M, int D, int I>
    struct LinearMatrixSwapColumnImpl {
        enum {
            Continue = I != D - 1,
            NextI = I + 1
        };
        
        static FORCEINLINE void eval(M &mat, int x, int y, int index) {
            MINE_ASSERT2(index <= D, "MatrixSwapColumnImpl, index out of range");
            float temp = mat.valueAt(index, x);
            mat.valueAt(index, x) = mat.valueAt(index, y);
            mat.valueAt(index, y) = temp;
            ++index;
            if(D != index) {
                LinearMatrixSwapColumnImpl<M, D * Continue,
                NextI * Continue>::eval(mat, x, y, index);
            }
        }
    };
    
    template<class M>
    struct LinearMatrixSwapColumnImpl<M, 0, 0> {
        static FORCEINLINE void eval(M&, int, int, int) {}
    };
    
    template<class M, int D>
    FORCEINLINE void linearMatrixSwapColumn(M &mat, int x, int y, int startIndex) {
        LinearMatrixSwapColumnImpl<M, D, 0>::eval(mat, x, y, startIndex);
    }
    
    // multiply matrix column
    template<class M, int D, int I>
    struct LinearMatrixMultiplyColumnImpl {
        enum {
            Continue = I != D - 1,
            NextI = I + 1
        };
        
        static FORCEINLINE void eval(M &mat, int x, float multiple, int index) {
            MINE_ASSERT2(index <= D, "MatrixMultiplyColumnImpl, index out of range");
            mat.valueAt(index, x) *= multiple;
            ++index;
            if(D != index) {
                LinearMatrixMultiplyColumnImpl<M, D * Continue,
                NextI * Continue>::eval(mat, x, multiple, index);
            }
        }
    };
    
    template<class M>
    struct LinearMatrixMultiplyColumnImpl<M, 0, 0> {
        static FORCEINLINE void eval(M&, int, float, int) {}
    };
    
    template<class M, int D>
    FORCEINLINE void linearMatrixMultiplyColumn(M &mat, int x, float multiple, int startIndex) {
        LinearMatrixMultiplyColumnImpl<M, D, 0>::eval(mat, x, multiple, startIndex);
    }
    
    // substract matrix column, x -= y * multiple
    template<class M, int D, int I>
    struct LinearMatrixSubstractColumnImpl {
        enum {
            Continue = I != D - 1,
            NextI = I + 1
        };
        
        static FORCEINLINE void eval(M &mat, int x, int y, float multiple, int index) {
            MINE_ASSERT2(index <= D, "MatrixSubstractColumnImpl, index out of range");
            mat.valueAt(x, index) -= mat.valueAt(y, index) * multiple;
            ++index;
            if(D != index) {
                LinearMatrixSubstractColumnImpl<M, D * Continue,
                NextI * Continue>::eval(mat, x, y, multiple, index);
            }
        }
    };
    
    template<class M>
    struct LinearMatrixSubstractColumnImpl<M, 0, 0> {
        static FORCEINLINE void eval(M&, int, int, float, int) {}
    };
    
    template<class M, int D>
    FORCEINLINE void linearMatrixSubstractColumn(M &mat,
                                                 int x,
                                                 int y,
                                                 float multiple,
                                                 int startIndex) {
        LinearMatrixSubstractColumnImpl<M, D, 0>::eval(mat, x, y, multiple, startIndex);
    }
    
    // inverse matrix by gauss
    template<class M, int D, int C, int I>
    struct LinearMatrixInverseByGaussRowInnerImpl {
        enum {
            Continue = I != D - 1,
            NextI = I + 1
        };
        
        static FORCEINLINE void eval(M &mat, M &invMat) {
            if(I != C && !MyMathUtil::zero(mat.valueAt(I, C))) {
                linearMatrixSubstractRow<M, D>(invMat, I, C, mat.valueAt(I, C), 0);
                linearMatrixSubstractRow<M, D>(mat, I, C, mat.valueAt(I, C), C);
            }
            LinearMatrixInverseByGaussRowInnerImpl<M, Continue * D,
            Continue * C, Continue * NextI>::eval(mat, invMat);
        }
    };
    
    template<class M>
    struct LinearMatrixInverseByGaussRowInnerImpl<M, 0, 0, 0> {
        static FORCEINLINE void eval(M&, M&) {}
    };
    
    template<class M, int D, int C, int I>
    struct LinearMatrixInverseByGaussRowImpl {
        enum {
            Continue = I != D - 1,
            NextI = I + 1
        };
        
        static float dem;
        
        static FORCEINLINE void eval(M &mat, M &invMat, bool &inversible) {
            if(!MyMathUtil::zero(mat.valueAt(I, C))) {
                dem = 1.0f/mat.valueAt(I, C);
                if(!MyMathUtil::equal(dem, 1.0f)) {
                    linearMatrixMultiplyRow<M, D>(mat, I, dem, C);
                    linearMatrixMultiplyRow<M, D>(invMat, I, dem, 0);
                }
                if(I != C) {
                    linearMatrixSwapRow<M, D>(mat, I, C, C);
                    linearMatrixSwapRow<M, D>(invMat, I, C, 0);
                }
                LinearMatrixInverseByGaussRowInnerImpl<M, D, C, 0>::eval(mat, invMat);
                inversible = true;
                return;
            }
            LinearMatrixInverseByGaussRowImpl<M, Continue * D,
            Continue * C, Continue * NextI>::eval(mat, invMat, inversible);
        }
    };
    
    template<class M, int D, int C, int I>
    float LinearMatrixInverseByGaussRowImpl<M, D, C, I>::dem(0.0f);
    
    template<class M>
    struct LinearMatrixInverseByGaussRowImpl<M, 0, 0, 0> {
        static FORCEINLINE void eval(M &mat, M &invMat, bool &inversible) {
            inversible = false;
        }
    };
    
    template<class M, int D, int I>
    struct LinearMatrixInverseByGaussImpl {
        enum {
            Continue = I != D - 1,
            NextI = I + 1
        };
        
        static FORCEINLINE void eval(M &mat, M &invMat, bool &inversible) {
            LinearMatrixInverseByGaussRowImpl<M, D, I, I>::eval(mat, invMat, inversible);
            if(inversible) {
                LinearMatrixInverseByGaussImpl<M, Continue * D,
                Continue * NextI>::eval(mat, invMat, inversible);
            }
        }
    };
    
    template<class M>
    struct LinearMatrixInverseByGaussImpl<M, 0, 0> {
        static FORCEINLINE void eval(M &mat, M &invMat, bool &inversible) {}
    };
    
    template<class M>
    struct LinearMatrixInverseByGaussImpl<M, 1, 0> {
        static FORCEINLINE void eval(M &mat, M &invMat, bool &inversible) {
            if(!MyMathUtil::zero(mat.valueAt(0, 0))) {
                invMat.valueAt(0, 0) = 1.0f/mat.valueAt(0, 0);
                inversible = true;
            } else {
                inversible = false;
            }
        }
    };
    
    template<class M, int D>
    FORCEINLINE void linearMatrixInverseByGauss(M &implMat, M &invMat, bool &inversible) {
        LinearMatrixInverseByGaussImpl<M, D, 0>::eval(implMat, invMat, inversible);
    }
    
    template<class M, int D>
    FORCEINLINE bool metaInverseMatrix(const M &mat, M &invMat) {
        M implMat(mat);
        bool inversible;
        identityMatrix(invMat);
        linearMatrixInverseByGauss<M, D>(implMat, invMat, inversible);
        return inversible;
    }
    
    template<class M, int D>
    FORCEINLINE bool metaInverseMatrix(M &mat) {
        M implMat(mat), invMat(1.0f);
        bool inversible;
        linearMatrixInverseByGauss<M, D>(implMat, invMat, inversible);
        if(inversible) {
            mat = invMat;
        }
        return inversible;
    }
}

FORCEINLINE void zeroMatrix(MyFMatrix2 &mat) {
    mat.valueAt(0, 0) = 0.0f; mat.valueAt(0, 1) = 0.0f;
    mat.valueAt(1, 0) = 0.0f; mat.valueAt(1, 1) = 0.0f;
}

FORCEINLINE void identityMatrix(MyFMatrix2 &mat) {
    mat.valueAt(0, 0) = 1.0f; mat.valueAt(0, 1) = 0.0f;
    mat.valueAt(1, 0) = 0.0f; mat.valueAt(1, 1) = 1.0f;
}

FORCEINLINE void transposeMatrix(MyFMatrix2 &mat) {
    float tmp = mat.valueAt(0, 1);
    mat.valueAt(0, 1) = mat.valueAt(1, 0);
    mat.valueAt(1, 0) = tmp;
}

FORCEINLINE void transposeMatrix(const MyFMatrix2 &inMat, MyFMatrix2 &outMat) {
    outMat.valueAt(0, 0) = inMat.valueAt(0, 0); outMat.valueAt(0, 1) = inMat.valueAt(1, 0);
    outMat.valueAt(1, 0) = inMat.valueAt(0, 1); outMat.valueAt(1, 1) = inMat.valueAt(1, 1);
}

FORCEINLINE MyFMatrix2 transposeMatrix(const MyFMatrix2 &mat) {
    MyFMatrix2 ret;
    transposeMatrix(mat, ret);
    return ret;
}

FORCEINLINE bool inverseMatrix(const MyFMatrix2 &mat, MyFMatrix2 &invMat) {
    return metaInverseMatrix<MyFMatrix2, 2>(mat, invMat);
}

FORCEINLINE bool inverseMatrix(MyFMatrix2 &mat) {
    return metaInverseMatrix<MyFMatrix2, 2>(mat);
}

FORCEINLINE void zeroMatrix(MyFMatrix3 &mat) {
    mat.valueAt(0, 0) = 0.0f; mat.valueAt(0, 1) = 0.0f; mat.valueAt(0, 2) = 0.0f;
    mat.valueAt(1, 0) = 0.0f; mat.valueAt(1, 1) = 0.0f; mat.valueAt(1, 1) = 0.0f;
    mat.valueAt(2, 0) = 0.0f; mat.valueAt(2, 1) = 0.0f; mat.valueAt(2, 2) = 0.0f;
}

FORCEINLINE void identityMatrix(MyFMatrix3 &mat) {
    mat.valueAt(0, 0) = 1.0f; mat.valueAt(0, 1) = 0.0f; mat.valueAt(0, 2) = 0.0f;
    mat.valueAt(1, 0) = 0.0f; mat.valueAt(1, 1) = 1.0f; mat.valueAt(1, 2) = 0.0f;
    mat.valueAt(2, 0) = 0.0f; mat.valueAt(2, 1) = 0.0f; mat.valueAt(2, 2) = 1.0f;
}

FORCEINLINE void transposeMatrix(MyFMatrix3 &mat) {
    float tmp = mat.valueAt(0, 1);
    mat.valueAt(0, 1) = mat.valueAt(1, 0);
    mat.valueAt(1, 0) = tmp;
    tmp = mat.valueAt(0, 2);
    mat.valueAt(0, 2) = mat.valueAt(2, 0);
    mat.valueAt(2, 0) = tmp;
    tmp = mat.valueAt(1, 2);
    mat.valueAt(1, 2) = mat.valueAt(2, 1);
    mat.valueAt(2, 1) = tmp;
}

FORCEINLINE void transposeMatrix(const MyFMatrix3 &inMat, MyFMatrix3 &outMat) {
    outMat.valueAt(0, 0) = inMat.valueAt(0, 0);
    outMat.valueAt(0, 1) = inMat.valueAt(1, 0);
    outMat.valueAt(0, 2) = inMat.valueAt(2, 0);
    outMat.valueAt(1, 0) = inMat.valueAt(0, 1);
    outMat.valueAt(1, 1) = inMat.valueAt(1, 1);
    outMat.valueAt(1, 2) = inMat.valueAt(2, 1);
    outMat.valueAt(2, 0) = inMat.valueAt(0, 2);
    outMat.valueAt(2, 1) = inMat.valueAt(1, 2);
    outMat.valueAt(2, 2) = inMat.valueAt(2, 2);
}

FORCEINLINE MyFMatrix3 transposeMatrix(const MyFMatrix3 &mat) {
    MyFMatrix3 ret;
    transposeMatrix(mat, ret);
    return ret;
}

FORCEINLINE bool inverseMatrix(MyFMatrix3 &mat, MyFMatrix3 &invMat) {
    return metaInverseMatrix<MyFMatrix3, 3>(mat, invMat);
}

FORCEINLINE bool inverseMatrix(MyFMatrix3 &mat) {
    return metaInverseMatrix<MyFMatrix3, 3>(mat);
}

FORCEINLINE void zeroMatrix(MyFMatrix4 &mat) {
    mat.valueAt(0, 0) = 0.0f; mat.valueAt(0, 1) = 0.0f; mat.valueAt(0, 2) = 0.0f; mat.valueAt(0, 3) = 0.0f;
    mat.valueAt(1, 0) = 0.0f; mat.valueAt(1, 1) = 0.0f; mat.valueAt(1, 2) = 0.0f; mat.valueAt(1, 3) = 0.0f;
    mat.valueAt(2, 0) = 0.0f; mat.valueAt(2, 1) = 0.0f; mat.valueAt(2, 2) = 0.0f; mat.valueAt(2, 3) = 0.0f;
    mat.valueAt(3, 0) = 0.0f; mat.valueAt(3, 1) = 0.0f; mat.valueAt(3, 2) = 0.0f; mat.valueAt(3, 3) = 0.0f;
}

FORCEINLINE void identityMatrix(MyFMatrix4 &mat) {
    mat.valueAt(0, 0) = 1.0f; mat.valueAt(0, 1) = 0.0f; mat.valueAt(0, 2) = 0.0f; mat.valueAt(0, 3) = 0.0f;
    mat.valueAt(1, 0) = 0.0f; mat.valueAt(1, 1) = 1.0f; mat.valueAt(1, 2) = 0.0f; mat.valueAt(1, 3) = 0.0f;
    mat.valueAt(2, 0) = 0.0f; mat.valueAt(2, 1) = 0.0f; mat.valueAt(2, 2) = 1.0f; mat.valueAt(2, 3) = 0.0f;
    mat.valueAt(3, 0) = 0.0f; mat.valueAt(3, 1) = 0.0f; mat.valueAt(3, 2) = 0.0f; mat.valueAt(3, 3) = 1.0f;
}

FORCEINLINE void transposeMatrix(MyFMatrix4 &mat) {
    float tmp = mat.valueAt(0, 1);
    mat.valueAt(0, 1) = mat.valueAt(1, 0);
    mat.valueAt(1, 0) = tmp;
    tmp = mat.valueAt(0, 2);
    mat.valueAt(0, 2) = mat.valueAt(2, 0);
    mat.valueAt(2, 0) = tmp;
    tmp = mat.valueAt(0, 3);
    mat.valueAt(0, 3) = mat.valueAt(3, 0);
    mat.valueAt(3, 0) = tmp;
    tmp = mat.valueAt(1, 2);
    mat.valueAt(1, 2) = mat.valueAt(2, 1);
    mat.valueAt(2, 1) = tmp;
    tmp = mat.valueAt(1, 3);
    mat.valueAt(1, 3) = mat.valueAt(3, 1);
    mat.valueAt(3, 1) = tmp;
    tmp = mat.valueAt(2, 3);
    mat.valueAt(2, 3) = mat.valueAt(3, 2);
    mat.valueAt(3, 2) = tmp;
}

FORCEINLINE void transposeMatrix(const MyFMatrix4 &inMat, MyFMatrix4 &outMat) {
    outMat.valueAt(0, 0) = inMat.valueAt(0, 0);
    outMat.valueAt(0, 1) = inMat.valueAt(1, 0);
    outMat.valueAt(0, 2) = inMat.valueAt(2, 0);
    outMat.valueAt(0, 3) = inMat.valueAt(3, 0);
    outMat.valueAt(1, 0) = inMat.valueAt(0, 1);
    outMat.valueAt(1, 1) = inMat.valueAt(1, 1);
    outMat.valueAt(1, 2) = inMat.valueAt(2, 1);
    outMat.valueAt(1, 3) = inMat.valueAt(3, 1);
    outMat.valueAt(2, 0) = inMat.valueAt(0, 2);
    outMat.valueAt(2, 1) = inMat.valueAt(1, 2);
    outMat.valueAt(2, 2) = inMat.valueAt(2, 2);
    outMat.valueAt(2, 3) = inMat.valueAt(3, 2);
    outMat.valueAt(3, 0) = inMat.valueAt(0, 3);
    outMat.valueAt(3, 1) = inMat.valueAt(1, 3);
    outMat.valueAt(3, 2) = inMat.valueAt(2, 3);
    outMat.valueAt(3, 3) = inMat.valueAt(3, 3);
}

FORCEINLINE MyFMatrix4 transposeMatrix(const MyFMatrix4 &mat) {
    MyFMatrix4 ret;
    transposeMatrix(mat, ret);
    return ret;
}

FORCEINLINE bool inverseMatrix(const MyFMatrix4 &mat, MyFMatrix4 &invMat) {
    return metaInverseMatrix<MyFMatrix4, 4>(mat, invMat);
}

FORCEINLINE bool inverseMatrix(MyFMatrix4 &mat) {
    return metaInverseMatrix<MyFMatrix4, 4>(mat);
}

FORCEINLINE bool matrixOrthogonal(const MyFMatrix3 &mat) {
    return MyMathUtil::identity(mat.valueAt(0, 0) * mat.valueAt(0, 0) +
                                mat.valueAt(1, 0) * mat.valueAt(1, 0) + mat.valueAt(2, 0) * mat.valueAt(2, 0)) &&
    MyMathUtil::identity(mat.valueAt(0, 1) * mat.valueAt(0, 1) +
                         mat.valueAt(1, 1) * mat.valueAt(1, 1) + mat.valueAt(2, 1) * mat.valueAt(2, 1)) &&
    MyMathUtil::identity(mat.valueAt(0, 2) * mat.valueAt(0, 2) +
                         mat.valueAt(1, 2) * mat.valueAt(1, 2) + mat.valueAt(2, 2) * mat.valueAt(2, 2)) &&
    MyMathUtil::zero(mat.valueAt(0, 0) * mat.valueAt(0, 1) +
                            mat.valueAt(1, 0) * mat.valueAt(1, 1) + mat.valueAt(2, 0) * mat.valueAt(2, 1)) &&
    MyMathUtil::zero(mat.valueAt(0, 0) * mat.valueAt(0, 2) +
                     mat.valueAt(1, 0) * mat.valueAt(1, 2) + mat.valueAt(2, 0) * mat.valueAt(2, 2)) &&
    MyMathUtil::zero(mat.valueAt(0, 1) * mat.valueAt(0, 2) +
                     mat.valueAt(1, 1) * mat.valueAt(1, 2) + mat.valueAt(2, 1) * mat.valueAt(2, 2));
    
}

MINE_NAMESPACE_END
