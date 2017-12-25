//
//  MyTransformComponent.hpp
//  Mine
//
//  Created by xy on 25/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyTransformComponent_hpp
#define MyTransformComponent_hpp

#include <glm/fwd.hpp>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyActorComponent;

class MyTransformComponent: public MyActorComponent {
public:
    static MyTransformComponent* create(void);
    static MyTransformComponent* createWithPosition(const glm::vec3 &pos);
    
public:
    const glm::vec3& position(void) { return _position; }
    void position(const glm::vec3 &pos) { _position = pos; }
    
    const glm::vec3& scale(void) { return _scale; }
    void scale(const glm::vec3 scale) { _scale = scale; }
    
    const glm::mat4& transformMatrix(void);
    
private:
    MyTransformComponent(void):
    MyActorComponent(MyActorComponent::kComponentTypeTransform,
                     "Transform", MyActorComponent::kComponentGroupTransform),
    _scale(1.0f), _right(1.0f, 0.0f, 0.0f),
    _up(0.0f, 1.0, 0.0f), _backward(0.0f, 0.0f, 1.0f),
    _transformMatrix(1.0f) {}
    MyTransformComponent(const glm::vec3 &pos):
    MyActorComponent(MyActorComponent::kComponentTypeTransform,
                     "Transform", MyActorComponent::kComponentGroupTransform),
    _position(pos), _scale(1.0f), _right(1.0f, 0.0f, 0.0f),
    _up(0.0f, 1.0, 0.0f), _backward(0.0f, 0.0f, 1.0f),
    _transformMatrix(1.0f) {}
    ~MyTransformComponent(void) {}
    
    glm::vec3 _position;
    glm::vec3 _scale;
    glm::vec3 _right;
    glm::vec3 _up;
    glm::vec3 _backward;
    glm::mat4 _transformMatrix;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyTransformComponent_hpp */
