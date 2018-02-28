//
//  MyCoordinate.inl
//  Mine
//
//  Created by xy on 26/02/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

MINE_NAMESPACE_BEGIN

FORCEINLINE MyCoordinate::MyCoordinate(void):
_axisX(1.0f, 0.0f, 0.0f),
_axisY(0.0f, 1.0f, 0.0f),
_axisZ(0.0f, 0.0f, 1.0f),
_coordinateMatrix(1.0f) {}

FORCEINLINE MyCoordinate::~MyCoordinate(void) {}

FORCEINLINE MyCoordinate::MyCoordinate(const MyFVector3 &inX,
                                       const MyFVector3 &inY,
                                       const MyFVector3 &inZ):
_axisX(inX),
_axisY(inY),
_axisZ(inZ),
_coordinateMatrix(inX.x, inY.x, inZ.x,
                  inX.y, inY.y, inZ.y,
                  inX.z, inY.z, inZ.z) {}

FORCEINLINE MyCoordinate::MyCoordinate(const MyCoordinate &coord):
_axisX(coord._axisX),
_axisY(coord._axisY),
_axisZ(coord._axisZ) {}

FORCEINLINE MyCoordinate& MyCoordinate::operator=(const MyCoordinate &other) {
    MINE_ASSERT2(this != &other, "MyCoordinate::operator=, same object");
    _axisX = other._axisX;
    _axisY = other._axisY;
    _axisZ = other._axisZ;
    _coordinateMatrix = other._coordinateMatrix;
    return *this;
}

FORCEINLINE MyCoordinate& MyCoordinate::operator=(const MyCoordinate &&other) {
    MINE_ASSERT2(this != &other, "MyCoordinate::operator=, same object");
    _axisX = other._axisX;
    _axisY = other._axisY;
    _axisZ = other._axisZ;
    _coordinateMatrix = other._coordinateMatrix;
    return *this;
}

FORCEINLINE bool MyCoordinate::operator==(const MyCoordinate &other) {
    return _coordinateMatrix == other._coordinateMatrix;
}

FORCEINLINE bool MyCoordinate::operator!=(const MyCoordinate &other) {
    return _coordinateMatrix != other._coordinateMatrix;
}

FORCEINLINE const MyFVector3& MyCoordinate::axisX(void) const {
    return _axisX;
}

FORCEINLINE const MyFVector3& MyCoordinate::axisY(void) const {
    return _axisY;
}

FORCEINLINE const MyFVector3& MyCoordinate::axisZ(void) const {
    return _axisZ;
}

FORCEINLINE const MyFMatrix3& MyCoordinate::coordinateMatrix(void) const {
    return _coordinateMatrix;
}

FORCEINLINE void MyCoordinate::assignCoordinate(const MyFVector3 &inX,
                                                const MyFVector3 &inY,
                                                const MyFVector3 &inZ) {
    _axisX = inX;
    _axisY = inY;
    _axisZ = inZ;
    _coordinateMatrix.valueAt(0, 0) = inX.x;
    _coordinateMatrix.valueAt(1, 0) = inX.y;
    _coordinateMatrix.valueAt(2, 0) = inX.z;
    _coordinateMatrix.valueAt(0, 1) = inY.x;
    _coordinateMatrix.valueAt(1, 1) = inY.y;
    _coordinateMatrix.valueAt(2, 1) = inY.z;
    _coordinateMatrix.valueAt(0, 2) = inZ.x;
    _coordinateMatrix.valueAt(1, 2) = inZ.y;
    _coordinateMatrix.valueAt(2, 2) = inZ.z;
}

FORCEINLINE bool MyCoordinate::validate(void) const {
    return MyMathUtil::identity(dotProduct(_axisX, _axisX)) &&
    MyMathUtil::identity(dotProduct(_axisY, _axisY)) &&
    MyMathUtil::identity(dotProduct(_axisZ, _axisZ)) &&
    MyMathUtil::zero(dotProduct(_axisX, _axisY)) &&
    MyMathUtil::zero(dotProduct(_axisY, _axisZ)) &&
    MyMathUtil::zero(dotProduct(_axisZ, _axisX));
}

// orthogonalization by Schmidt
FORCEINLINE void MyCoordinate::correct(void) {
    schmidtVector(_axisX, _axisY, _axisZ);
}

// MyCoordinateTransition implementation
FORCEINLINE MyCoordinateTransition::MyCoordinateTransition(void):
_coordinateA(nullptr),
_coordinateB(nullptr) {}

FORCEINLINE MyCoordinateTransition::~MyCoordinateTransition(void) {}

FORCEINLINE MyCoordinateTransition::MyCoordinateTransition(const MyCoordinate &coordA,
                                                           const MyCoordinate &coordB):
_coordinateA(nullptr),
_coordinateB(nullptr) {
    constructTransition(coordA, coordB);
}

FORCEINLINE MyCoordinateTransition::MyCoordinateTransition(const MyCoordinateTransition &other):
_coordinateA(other._coordinateA),
_coordinateB(other._coordinateB),
_forwardMatrix(other._forwardMatrix),
_backwardMatrix(other._backwardMatrix)  {}

FORCEINLINE MyCoordinateTransition::MyCoordinateTransition(const MyCoordinateTransition &&other):
_coordinateA(other._coordinateA),
_coordinateB(other._coordinateB),
_forwardMatrix(other._forwardMatrix),
_backwardMatrix(other._backwardMatrix) {}

FORCEINLINE MyCoordinateTransition& MyCoordinateTransition::operator=(const MyCoordinateTransition &other) {
    _coordinateA = other._coordinateA;
    _coordinateB = other._coordinateB;
    _forwardMatrix = other._forwardMatrix;
    _backwardMatrix = other._backwardMatrix;
    return *this;
}

FORCEINLINE MyCoordinateTransition& MyCoordinateTransition::operator=(const MyCoordinateTransition &&other) {
    _coordinateA = other._coordinateA;
    _coordinateB = other._coordinateB;
    _forwardMatrix = other._forwardMatrix;
    _backwardMatrix = other._backwardMatrix;
    return *this;
}

FORCEINLINE bool MyCoordinateTransition::operator==(const MyCoordinateTransition &other) const {
    return _coordinateA == other._coordinateA &&
    _coordinateB == other._coordinateB &&
    _forwardMatrix == other._forwardMatrix &&
    _backwardMatrix == other._backwardMatrix;
}

FORCEINLINE bool MyCoordinateTransition::operator!=(const MyCoordinateTransition &other) const {
    return _coordinateA != other._coordinateA ||
    _coordinateB != other._coordinateB ||
    _forwardMatrix == other._forwardMatrix ||
    _backwardMatrix == other._backwardMatrix;
}

FORCEINLINE void MyCoordinateTransition::constructTransition(const MyCoordinate &coordA,
                                                             const MyCoordinate &coordB) {
    _coordinateA = &coordA;
    _coordinateB = &coordB;
    transposeMatrix(coordA.coordinateMatrix(), _forwardMatrix);
    _forwardMatrix *= coordB.coordinateMatrix();
    transposeMatrix(_forwardMatrix, _backwardMatrix);
}

FORCEINLINE const MyFMatrix3& MyCoordinateTransition::forwardMatrix(void) const {
    MINE_ASSERT2(validate(), "MyCoordinateTransition::forwardMatrix, not prepared");
    return _forwardMatrix;
}

FORCEINLINE const MyFMatrix3& MyCoordinateTransition::backwardMatrix(void) const {
    MINE_ASSERT2(validate(), "MyCoordinateTransition::backwardMatrix, not prepared");
    return _backwardMatrix;
}

FORCEINLINE bool MyCoordinateTransition::validate(void) const {
    return _coordinateA && _coordinateB &&
    _coordinateA->validate() && _coordinateB->validate();
}

MINE_NAMESPACE_END
