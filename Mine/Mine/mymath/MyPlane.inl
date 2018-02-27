//
//  MyPlane.inl
//  Mine
//
//  Created by xy on 27/02/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#include "MyVector.hpp"
#include "MyMathUtil.hpp"

MINE_NAMESPACE_BEGIN

FORCEINLINE MyPlane::MyPlane(void) {}

FORCEINLINE MyPlane::MyPlane(const MyFVector3 &norm, float dist):
_normal(norm),
_distance(dist) {}

FORCEINLINE MyPlane::MyPlane(const MyPlane &other):
_normal(other._normal),
_distance(other._distance) {}

FORCEINLINE MyPlane& MyPlane::operator=(const MyPlane &other) {
    MINE_ASSERT2(this != &other, "MyPlane::operator=, same object");
    _normal = other._normal;
    _distance = other._distance;
    return *this;
}

FORCEINLINE MyPlane& MyPlane::operator=(const MyPlane &&other) {
    MINE_ASSERT2(this != &other, "MyPlane::operator=, same object");
    _normal = other._normal;
    _distance = other._distance;
    return *this;
}

FORCEINLINE bool MyPlane::operator==(const MyPlane &other) const {
    return _normal == other._normal && MyMathUtil::equal(_distance, other._distance);
}

FORCEINLINE bool MyPlane::operator!=(const MyPlane &other) const {
    return _normal != other._normal || !MyMathUtil::equal(_distance, other._distance);
}

FORCEINLINE const MyFVector3& MyPlane::normal(void) const {
    return _normal;
}

FORCEINLINE void MyPlane::normal(const MyFVector3 &norm) {
    normalizeVector(norm, _normal);
}

FORCEINLINE float MyPlane::distance(void) const {
    return _distance;
}

FORCEINLINE void MyPlane::distance(float dist) {
    _distance = dist;
}

FORCEINLINE int MyPlane::pointOnPlane(const MyFVector3 &vec) const {
    float dist = dotProduct(vec, _normal) - _distance;
    return MyMathUtil::zero(dist) ? 0 : (dist > 0 ? 1 : -1);
}

// q = p + kn, dot(q, n) = pn + k = d -> k = d - pn
FORCEINLINE void MyPlane::closestPointOnPlane(const MyFVector3 &inVec, MyFVector3 &outVec) const {
    float k = _distance - dotProduct(inVec, _normal);
    outVec.x = inVec.x + k * _normal.x;
    outVec.y = inVec.y + k * _normal.y;
    outVec.z = inVec.z + k * _normal.z;
}

MINE_NAMESPACE_END
