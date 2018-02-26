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
    _axisX = other._axisX;
    _axisY = other._axisY;
    _axisZ = other._axisZ;
    _coordinateMatrix = other._coordinateMatrix;
    return *this;
}

FORCEINLINE MyCoordinate& MyCoordinate::operator=(const MyCoordinate &&other) {
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

MINE_NAMESPACE_END
