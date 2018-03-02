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

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyActorComponent;
class MyFVector3;
class MyFMatrix4;
class MyFQuaternion;
class MyCoordinate;

class MyTransformComponent final: public MyActorComponent {
public:
    static MyTransformComponent* create(void);
    static MyTransformComponent* createWithPosition(const MyFVector3 &pos);
    
public:
    FORCEINLINE const MyFVector3& position(void) { return _position; }
    FORCEINLINE void position(const MyFVector3 &pos) { _position = pos; }
    
    FORCEINLINE const MyFVector3& scale(void) const { return _scale; }
    FORCEINLINE void scale(const MyFVector3 &scale) { _scale = scale; }
    
private:
    FORCEINLINE MyTransformComponent(void):
    MyActorComponent(MyActorComponent::kComponentTypeTransform,
                     MyActorComponent::kComponentGroupTransform),
    _position(0.0f),
    _scale(1.0f) {}
    FORCEINLINE MyTransformComponent(const MyFVector3 &pos):
    MyActorComponent(MyActorComponent::kComponentTypeTransform,
                     MyActorComponent::kComponentGroupTransform),
    _position(pos),
    _scale(1.0f) {}
    FORCEINLINE ~MyTransformComponent(void) {}
    
    MyFVector3 _position;
    MyFVector3 _scale;
    MyFQuaternion _rotation;
    MyFVector3 _forward;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyTransformComponent_hpp */
