//
//  MyTransformComponent.cpp
//  Mine
//
//  Created by xy on 25/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "MyTemplate.hpp"
#include "MyActorComponent.hpp"
#include "MyTransformComponent.hpp"

MINE_NAMESPACE_BEGIN

MyTransformComponent* MyTransformComponent::create(void) {
    MyTransformComponent *transform = new MyTransformComponent();
    transform->refName("MyTransformComponent");
    return transform;
}

MyTransformComponent* MyTransformComponent::createWithPosition(const glm::vec3 &pos) {
    MyTransformComponent *transform = new MyTransformComponent(pos);
    transform->refName("MyTransformComponent");
    return transform;
}

const glm::mat4& MyTransformComponent::transformMatrix(void) {
    _transformMatrix = glm::translate(glm::mat4(1.0f), _position);
    return _transformMatrix;
}

MINE_NAMESPACE_END
