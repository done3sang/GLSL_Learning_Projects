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
class MyCoordinate;

class MyTransformComponent: public MyActorComponent {
public:
    static MyTransformComponent* create(void);
    static MyTransformComponent* createWithPosition(const MyFVector3 &pos);
    
public:
    const MyFVector3& position(void);
    void position(const MyFVector3 &pos);
    
    const MyFVector3& scale(void) const;
    void scale(const MyFVector3 &scale);
    
private:
    MyTransformComponent(void):
    MyActorComponent(MyActorComponent::kComponentTypeTransform,
                     "Transform", MyActorComponent::kComponentGroupTransform),
    _position(0.0f), _scale(1.0f) {}
    MyTransformComponent(const MyFVector3 &pos):
    MyActorComponent(MyActorComponent::kComponentTypeTransform,
                     "Transform", MyActorComponent::kComponentGroupTransform),
    _position(pos), _scale(1.0f) {}
    ~MyTransformComponent(void) {}
    
    MyFVector3 _position;
    MyFVector3 _scale;
    MyCoordinate _coordinate;
    MyFVector3 _forward;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#include "MyTransformComponent.inl"

#endif /* MyTransformComponent_hpp */
