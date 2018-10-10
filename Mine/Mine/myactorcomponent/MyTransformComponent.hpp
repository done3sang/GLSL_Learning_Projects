//
//  MyTransformComponent.hpp
//  Mine
//
//  Created by xy on 25/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyTransformComponent_hpp
#define MyTransformComponent_hpp

#include "MyPrecompiled.hpp"
//#include "MyVector.hpp"
#include "../mymath/MyVector.hpp"
//#include "MyMatrix.hpp"
//#include "MyCoordinate.hpp"
#include "../mymath/MyTransformation.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyActorComponent;
class MyFVector3;
class MyFMatrix4;
class MyFQuaternion;
class MyCoordinate;
class MyTransformation;

class MyTransformComponent final: public MyActorComponent {
public:
    static MyTransformComponent* create(void);
    static MyTransformComponent* createWithPosition(const MyFVector3 &pos);
    
public:
    FORCEINLINE const MyFVector3& position(void) { return _position; }
    FORCEINLINE void position(const MyFVector3 &pos) { _position = pos; update(); }
    
    FORCEINLINE const MyFVector3& scale(void) const { return _scale; }
    FORCEINLINE void scale(const MyFVector3 &scale) { _scale = scale; update(); }
    
    FORCEINLINE const MyFQuaternion& rotation(void) const { return _rotation; }
    FORCEINLINE const MyFMatrix4& transformMatrix(void) const { return _transformMatrix; }
    
    FORCEINLINE const MyFVector3& right(void) const { return _right; }
    FORCEINLINE const MyFVector3& up(void) const { return _up; }
    FORCEINLINE const MyFVector3& forward(void) const { return _forward; }
    
    FORCEINLINE void rotateByAxisX(float radius) {
        MyTransformation::rotateQuaternionByAxisX(_rotation, radius);
        update();
    }
    FORCEINLINE void rotateByAxisY(float radius) {
        MyTransformation::rotateQuaternionByAxisY(_rotation, radius);
        update();
    }
    FORCEINLINE void rotateByAxisZ(float radius) {
        MyTransformation::rotateQuaternionByAxisZ(_rotation, radius);
        update();
    }
    FORCEINLINE void rotateByAxis(const MyFVector3 & vec, float radius) {
        MyTransformation::rotateQuaternionByAxis(_rotation, vec, radius);
        update();
    }
    
    FORCEINLINE void transformWorldToLocal(const MyFVector3 &worldVec,
                                           MyFVector3 &localVec) {
        MyTransformation::quaternionVectorBackward(_rotation, worldVec, localVec);
        localVec.x /= _scale.x;
        localVec.y /= _scale.y;
        localVec.z /= _scale.z;
        localVec -= _position;
    }
    FORCEINLINE void transformLocalToWorld(const MyFVector3 &localVec,
                                           MyFVector3 &worldVec) {
        MyTransformation::quaternionVectorForward(_rotation, localVec, worldVec);
        worldVec.x *= _scale.x;
        worldVec.y *= _scale.y;
        worldVec.z *= _scale.z;
        worldVec += _position;
    }
    
private:
    FORCEINLINE MyTransformComponent(void):
    MyActorComponent(MyActorComponent::kComponentTypeTransform,
                     MyActorComponent::kComponentGroupTransform),
    _position(0.0f),
    _scale(1.0f),
    _rotation(1.0f),
    _transformMatrix(1.0f) {}
    FORCEINLINE MyTransformComponent(const MyFVector3 &pos):
    MyActorComponent(MyActorComponent::kComponentTypeTransform,
                     MyActorComponent::kComponentGroupTransform),
    _position(pos),
    _scale(1.0f),
    _rotation(1.0f),
    _transformMatrix(1.0f) {}
    FORCEINLINE ~MyTransformComponent(void) {}
    
    MyFVector3 _position;
    MyFVector3 _scale;
    MyFQuaternion _rotation;
    MyFMatrix4 _transformMatrix;
    MyFVector3 _right;
    MyFVector3 _up;
    MyFVector3 _forward;
    
    FORCEINLINE void update(void) {
        normalizeQuaternion(_rotation);
        MyTransformation::quaternionToMatrix(_rotation, _transformMatrix);
        _right.x = _transformMatrix.valueAt(0, 0);
        _right.y = _transformMatrix.valueAt(1, 0);
        _right.z = _transformMatrix.valueAt(2, 0);
        _up.x = _transformMatrix.valueAt(0, 1);
        _up.y = _transformMatrix.valueAt(1, 1);
        _up.z = _transformMatrix.valueAt(2, 1);
        _forward.x = -_transformMatrix.valueAt(0, 2);
        _forward.y = -_transformMatrix.valueAt(1, 2);
        _forward.z = -_transformMatrix.valueAt(2, 2);
        MyTransformation::scaleMatrix(_transformMatrix, _scale);
        MyTransformation::translateMatrix(_transformMatrix, _position);
    }
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyTransformComponent_hpp */
