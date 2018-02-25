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

constexpr int MyFMatrix2::kDimension(2);
const MyFMatrix2 MyFMatrix2::kIdentity(1.0f, 0.0f, 0.0f, 1.0f);
const MyFMatrix2 MyFMatrix2::kZero(0.0f, 0.0f, 0.0f, 0.0f);

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
    _value[0][0] = other._value[0][0];
    _value[0][1] = other._value[0][1];
    _value[1][0] = other._value[1][0];
    _value[1][1] = other._value[1][1];
    return *this;
}

FORCEINLINE MyFMatrix2& MyFMatrix2::operator=(const MyFMatrix2 &&other) {
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

/*
FORCEINLINE float& MyFMatrix2::valueAt(constexpr int x, constexpr int y) {
    MINE_ASSERT2(0 <= x && x <= 1, "MyFMatrix2::valueAt, index(x) out of range");
    MINE_ASSERT2(0 <= y && y <= 1, "MyFMatrix2::valueAt, index(y) out of range");
    return _value[x][y];
}

FORCEINLINE const float& MyFMatrix2::valueAt(constexpr int x, constexpr int y) const {
    MINE_ASSERT2(0 <= x && x <= 1, "MyFMatrix2::valueAt, index(x) out of range");
    MINE_ASSERT2(0 <= y && y <= 1, "MyFMatrix2::valueAt, index(y) out of range");
    return _value[x][y];
}
*/

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

FORCEINLINE void zeroMatrix(MyFMatrix2 &mat) {
    mat.valueAt(0, 0) = 0.0f; mat.valueAt(0, 1) = 0.0f;
    mat.valueAt(1, 0) = 0.0f; mat.valueAt(1, 1) = 0.0f;
}

FORCEINLINE void identityMatrix(MyFMatrix2 &mat) {
    mat.valueAt(0, 0) = 1.0f; mat.valueAt(0, 1) = 0.0f;
    mat.valueAt(1, 0) = 0.0f; mat.valueAt(1, 1) = 1.0f;
}

FORCEINLINE MyFMatrix2 transposeMatrix(const MyFMatrix2 &mat) {
    return MyFMatrix2(mat.valueAt(0, 0), mat.valueAt(1, 0),
                      mat.valueAt(0, 1), mat.valueAt(1, 1));
}

FORCEINLINE MyFMatrix2& transposeMatrixSelf(MyFMatrix2 &mat) {
    float tmp = mat.valueAt(0, 1);
    mat.valueAt(0, 1) = mat.valueAt(1, 0);
    mat.valueAt(1, 0) = tmp;
    return mat;
}

FORCEINLINE MyFMatrix2 inverseMatrix(const MyFMatrix2 &mat) {
    float det = mat.determinant();
    MyFMatrix2 ret;
    if(!MyMathUtil::zero(det)) {
        det = 1.0f/det;
        ret.valueAt(0, 0) = mat.valueAt(1, 1) * det;
        ret.valueAt(0, 1) = mat.valueAt(1, 0) * det;
        ret.valueAt(1, 0) = mat.valueAt(0, 1) * det;
        ret.valueAt(1, 1) = mat.valueAt(0, 0) * det;
    } else {
        zeroMatrix(ret);
    }
    return ret;
}

FORCEINLINE MyFMatrix2& inverseMatrixSelf(MyFMatrix2 &mat) {
    float det = mat.determinant();
    if(!MyMathUtil::zero(det)) {
        det = 1.0f/det;
        float tmp = mat.valueAt(0, 0);
        mat.valueAt(0, 0) = mat.valueAt(1, 1) * det;
        mat.valueAt(1, 1) = tmp * det;
        tmp = mat.valueAt(0, 1);
        mat.valueAt(0, 1) = mat.valueAt(1, 0) * det;
        mat.valueAt(1, 0) = tmp * det;
    }
    return mat;
}

FORCEINLINE float* value_pointer(MyFMatrix2 &mat) {
    return &mat.valueAt(0, 0);
}

FORCEINLINE const float* value_pointer(const MyFMatrix2 &mat) {
    return &mat.valueAt(0, 0);
}

// MyFMatrix3 implementation

constexpr int MyFMatrix2::kDimension(3);
const MyFMatrix3 MyFMatrix3::kIdentity(1.0f, 0.0f, 0.0f,
                                       0.0f, 1.0f, 0.0f,
                                       0.0f, 0.0f, 1.0f);
const MyFMatrix3 MyFMatrix3::kZero(0.0f, 0.0f, 0.0f,
                                       0.0f, 0.0f, 0.0f,
                                       0.0f, 0.0f, 0.0f);

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

/*
 FORCEINLINE float& MyFMatrix2::valueAt(constexpr int x, constexpr int y) {
 MINE_ASSERT2(0 <= x && x <= 1, "MyFMatrix2::valueAt, index(x) out of range");
 MINE_ASSERT2(0 <= y && y <= 1, "MyFMatrix2::valueAt, index(y) out of range");
 return _value[x][y];
 }
 
 FORCEINLINE const float& MyFMatrix2::valueAt(constexpr int x, constexpr int y) const {
 MINE_ASSERT2(0 <= x && x <= 1, "MyFMatrix2::valueAt, index(x) out of range");
 MINE_ASSERT2(0 <= y && y <= 1, "MyFMatrix2::valueAt, index(y) out of range");
 return _value[x][y];
 }
 */

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

FORCEINLINE MyFMatrix3 transposeMatrix(const MyFMatrix3 &mat) {
    return MyFMatrix3(mat.valueAt(0, 0), mat.valueAt(1, 0), mat.valueAt(2, 0),
                      mat.valueAt(0, 1), mat.valueAt(1, 1), mat.valueAt(2, 1),
                      mat.valueAt(0, 2), mat.valueAt(1, 2), mat.valueAt(2, 2));
}

FORCEINLINE MyFMatrix3& transposeMatrixSelf(MyFMatrix3 &mat) {
    float tmp = mat.valueAt(0, 1);
    mat.valueAt(0, 1) = mat.valueAt(1, 0);
    mat.valueAt(1, 0) = tmp;
    tmp = mat.valueAt(0, 2);
    mat.valueAt(0, 2) = mat.valueAt(2, 0);
    mat.valueAt(2, 0) = tmp;
    tmp = mat.valueAt(1, 2);
    mat.valueAt(1, 2) = mat.valueAt(2, 1);
    mat.valueAt(2, 1) = tmp;
    return mat;
}

FORCEINLINE MyFMatrix3 inverseMatrix(const MyFMatrix3 &mat) {
    float det00 = mat.valueAt(1, 1) * mat.valueAt(2, 2) - mat.valueAt(1, 2) * mat.valueAt(2, 1);
    float det01 = mat.valueAt(1, 0) * mat.valueAt(2, 2) - mat.valueAt(1, 2) * mat.valueAt(2, 0);
    float det02 = mat.valueAt(1, 0) * mat.valueAt(2, 1) - mat.valueAt(1, 1) * mat.valueAt(2, 0);
    float det = mat.valueAt(0, 0) * det00 - mat.valueAt(0, 1) * det01 + mat.valueAt(0, 2) * det02;
    
    MyFMatrix3 ret;
    if(!MyMathUtil::zero(det)) {
        float det10 = mat.valueAt(0, 1) * mat.valueAt(2, 2) - mat.valueAt(0, 2) * mat.valueAt(2, 1);
        float det11 = mat.valueAt(0, 0) * mat.valueAt(2, 2) - mat.valueAt(0, 2) * mat.valueAt(2, 0);
        float det12 = mat.valueAt(0, 0) * mat.valueAt(2, 1) - mat.valueAt(0, 1) * mat.valueAt(2, 0);
        float det20 = mat.valueAt(0, 1) * mat.valueAt(1, 2) - mat.valueAt(0, 2) * mat.valueAt(1, 1);
        float det21 = mat.valueAt(0, 0) * mat.valueAt(1, 2) - mat.valueAt(0, 2) * mat.valueAt(1, 0);
        float det22 = mat.valueAt(0, 0) * mat.valueAt(1, 1) - mat.valueAt(0, 1) * mat.valueAt(1, 0);
        
        det = 1.0f/det;
        ret.valueAt(0, 0) = det00* det; ret.valueAt(0, 1) = -det01 * det; ret.valueAt(0, 2) = det02 * det;
        ret.valueAt(1, 0) = -det10 * det; ret.valueAt(1, 1) = det11 * det; ret.valueAt(1, 2) = -det12 * det;
        ret.valueAt(2, 0) = det20 * det; ret.valueAt(2, 1) = -det21 * det; ret.valueAt(2, 2) = det22 * det;
    } else {
        zeroMatrix(ret);
    }
    
    return ret;
}

FORCEINLINE MyFMatrix3& inverseMatrixSelf(MyFMatrix3 &mat) {
    float det00 = mat.valueAt(1, 1) * mat.valueAt(2, 2) - mat.valueAt(1, 2) * mat.valueAt(2, 1);
    float det01 = mat.valueAt(1, 0) * mat.valueAt(2, 2) - mat.valueAt(1, 2) * mat.valueAt(2, 0);
    float det02 = mat.valueAt(1, 0) * mat.valueAt(2, 1) - mat.valueAt(1, 1) * mat.valueAt(2, 0);
    float det = mat.valueAt(0, 0) * det00 - mat.valueAt(0, 1) * det01 + mat.valueAt(0, 2) * det02;

    if(!MyMathUtil::zero(det)) {
        float det10 = mat.valueAt(0, 1) * mat.valueAt(2, 2) - mat.valueAt(0, 2) * mat.valueAt(2, 1);
        float det11 = mat.valueAt(0, 0) * mat.valueAt(2, 2) - mat.valueAt(0, 2) * mat.valueAt(2, 0);
        float det12 = mat.valueAt(0, 0) * mat.valueAt(2, 1) - mat.valueAt(0, 1) * mat.valueAt(2, 0);
        float det20 = mat.valueAt(0, 1) * mat.valueAt(1, 2) - mat.valueAt(0, 2) * mat.valueAt(1, 1);
        float det21 = mat.valueAt(0, 0) * mat.valueAt(1, 2) - mat.valueAt(0, 2) * mat.valueAt(1, 0);
        float det22 = mat.valueAt(0, 0) * mat.valueAt(1, 1) - mat.valueAt(0, 1) * mat.valueAt(1, 0);
        
        det = 1.0f/det;
        mat.valueAt(0, 0) = det00* det; mat.valueAt(0, 1) = -det01 * det; mat.valueAt(0, 2) = det02 * det;
        mat.valueAt(1, 0) = -det10 * det; mat.valueAt(1, 1) = det11 * det; mat.valueAt(1, 2) = -det12 * det;
        mat.valueAt(2, 0) = det20 * det; mat.valueAt(2, 1) = -det21 * det; mat.valueAt(2, 2) = det22 * det;
    }
    
    return mat;
}

FORCEINLINE float* value_pointer(MyFMatrix3 &mat) {
    return &mat.valueAt(0, 0);
}

FORCEINLINE const float* value_pointer(const MyFMatrix3 &mat) {
    return &mat.valueAt(0, 0);
}

// MyFMatrix4 implementation

constexpr int MyFMatrix2::kDimension(4);
const MyFMatrix4 MyFMatrix4::kIdentity(1.0f, 0.0f, 0.0f, 0.0f,
                                       0.0f, 1.0f, 0.0f, 0.0f,
                                       0.0f, 0.0f, 1.0f, 0.0f,
                                       0.0f, 0.0f, 0.0f, 1.0f);
const MyFMatrix4 MyFMatrix4::kZero(0.0f, 0.0f, 0.0f, 0.0f,
                                   0.0f, 0.0f, 0.0f, 0.0f,
                                   0.0f, 0.0f, 0.0f, 0.0f,
                                   0.0f, 0.0f, 0.0f, 0.0f);

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

/*
 FORCEINLINE float& MyFMatrix2::valueAt(constexpr int x, constexpr int y) {
 MINE_ASSERT2(0 <= x && x <= 1, "MyFMatrix2::valueAt, index(x) out of range");
 MINE_ASSERT2(0 <= y && y <= 1, "MyFMatrix2::valueAt, index(y) out of range");
 return _value[x][y];
 }
 
 FORCEINLINE const float& MyFMatrix2::valueAt(constexpr int x, constexpr int y) const {
 MINE_ASSERT2(0 <= x && x <= 1, "MyFMatrix2::valueAt, index(x) out of range");
 MINE_ASSERT2(0 <= y && y <= 1, "MyFMatrix2::valueAt, index(y) out of range");
 return _value[x][y];
 }
 */

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

FORCEINLINE MyFMatrix4 transposeMatrix(const MyFMatrix4 &mat) {
    return MyFMatrix4(mat.valueAt(0, 0), mat.valueAt(1, 0), mat.valueAt(2, 0), mat.valueAt(3, 0),
                      mat.valueAt(0, 1), mat.valueAt(1, 1), mat.valueAt(2, 1), mat.valueAt(3, 1),
                      mat.valueAt(0, 2), mat.valueAt(1, 2), mat.valueAt(2, 2), mat.valueAt(3, 2),
                      mat.valueAt(0, 3), mat.valueAt(1, 3), mat.valueAt(2, 3), mat.valueAt(3, 3));
}

FORCEINLINE MyFMatrix4& transposeMatrixSelf(MyFMatrix4 &mat) {
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
    return mat;
}

// [P , E]P^-1 = [E, P^-1]
FORCEINLINE MyFMatrix4 inverseMatrix(const MyFMatrix4 &mat) {
    MyFMatrix4 media(mat), ret(1.0f);
    float dem, tmp;
    
    // first column
    if(!MyMathUtil::zero(mat.valueAt(0, 0))) {
        // do nothing
    } else if(!MyMathUtil::zero(mat.valueAt(1, 0))) {
        media.valueAt(0, 0) = media.valueAt(1, 0);
        media.valueAt(1, 0) = 0.0f;
        tmp = media.valueAt(0, 1);
        media.valueAt(0, 1) = media.valueAt(1, 1);
        media.valueAt(1, 1) = tmp;
        tmp = media.valueAt(0, 2);
        media.valueAt(0, 2) = media.valueAt(1, 2);
        media.valueAt(1, 2) = tmp;
        tmp = media.valueAt(0, 3);
        media.valueAt(0, 3) = media.valueAt(1, 3);
        media.valueAt(1, 3) = tmp;
        
        ret.valueAt(0, 0) = 0.0f;
        ret.valueAt(0, 1) = 1.0f;
        ret.valueAt(1, 0) = 1.0f;
        ret.valueAt(1, 1) = 0.0f;
    } else if(!MyMathUtil::zero(mat.valueAt(2, 0))) {
        media.valueAt(0, 0) = media.valueAt(2, 0);
        media.valueAt(2, 0) = 0.0f;
        tmp = media.valueAt(0, 1);
        media.valueAt(0, 1) = media.valueAt(2, 1);
        media.valueAt(2, 1) = tmp;
        tmp = media.valueAt(0, 2);
        media.valueAt(0, 2) = media.valueAt(2, 2);
        media.valueAt(2, 2) = tmp;
        tmp = media.valueAt(0, 3);
        media.valueAt(0, 3) = media.valueAt(2, 3);
        media.valueAt(2, 3) = tmp;
        
        ret.valueAt(0, 0) = 0.0f;
        ret.valueAt(0, 2) = 1.0f;
        ret.valueAt(2, 0) = 1.0f;
        ret.valueAt(2, 2) = 0.0f;
    } else if(!MyMathUtil::zero(mat.valueAt(3, 0))) {
        media.valueAt(0, 0) = media.valueAt(3, 0);
        media.valueAt(3, 0) = 0.0f;
        tmp = media.valueAt(0, 1);
        media.valueAt(0, 1) = media.valueAt(3, 1);
        media.valueAt(3, 1) = tmp;
        tmp = media.valueAt(0, 2);
        media.valueAt(0, 2) = media.valueAt(3, 2);
        media.valueAt(3, 2) = tmp;
        tmp = media.valueAt(0, 3);
        media.valueAt(0, 3) = media.valueAt(3, 3);
        media.valueAt(3, 3) = tmp;
        
        ret.valueAt(0, 0) = 0.0f;
        ret.valueAt(0, 3) = 1.0f;
        ret.valueAt(3, 0) = 1.0f;
        ret.valueAt(3, 3) = 0.0f;
    } else {
        return MyFMatrix4::kZero;
    }
    dem = 1.0f/media.valueAt(0, 0);
    
    return ret;
}

FORCEINLINE MyFMatrix4& inverseMatrixSelf(MyFMatrix4 &mat) {
    float det00 = mat.valueAt(1, 1) * mat.valueAt(2, 2) - mat.valueAt(1, 2) * mat.valueAt(2, 1);
    float det01 = mat.valueAt(1, 0) * mat.valueAt(2, 2) - mat.valueAt(1, 2) * mat.valueAt(2, 0);
    float det02 = mat.valueAt(1, 0) * mat.valueAt(2, 1) - mat.valueAt(1, 1) * mat.valueAt(2, 0);
    float det = mat.valueAt(0, 0) * det00 - mat.valueAt(0, 1) * det01 + mat.valueAt(0, 2) * det02;
    
    if(!MyMathUtil::zero(det)) {
        float det10 = mat.valueAt(0, 1) * mat.valueAt(2, 2) - mat.valueAt(0, 2) * mat.valueAt(2, 1);
        float det11 = mat.valueAt(0, 0) * mat.valueAt(2, 2) - mat.valueAt(0, 2) * mat.valueAt(2, 0);
        float det12 = mat.valueAt(0, 0) * mat.valueAt(2, 1) - mat.valueAt(0, 1) * mat.valueAt(2, 0);
        float det20 = mat.valueAt(0, 1) * mat.valueAt(1, 2) - mat.valueAt(0, 2) * mat.valueAt(1, 1);
        float det21 = mat.valueAt(0, 0) * mat.valueAt(1, 2) - mat.valueAt(0, 2) * mat.valueAt(1, 0);
        float det22 = mat.valueAt(0, 0) * mat.valueAt(1, 1) - mat.valueAt(0, 1) * mat.valueAt(1, 0);
        
        det = 1.0f/det;
        mat.valueAt(0, 0) = det00* det; mat.valueAt(0, 1) = -det01 * det; mat.valueAt(0, 2) = det02 * det;
        mat.valueAt(1, 0) = -det10 * det; mat.valueAt(1, 1) = det11 * det; mat.valueAt(1, 2) = -det12 * det;
        mat.valueAt(2, 0) = det20 * det; mat.valueAt(2, 1) = -det21 * det; mat.valueAt(2, 2) = det22 * det;
    }
    
    return mat;
}

FORCEINLINE float* value_pointer(MyFMatrix4 &mat) {
    return &mat.valueAt(0, 0);
}

FORCEINLINE const float* value_pointer(const MyFMatrix4 &mat) {
    return &mat.valueAt(0, 0);
}

MINE_NAMESPACE_END
