//
//  MyTransformComponent.cpp
//  Mine
//
//  Created by xy on 27/02/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//


#include "MyVector.hpp"
#include "MyMatrix.hpp"
#include "MyCoordinate.hpp"
#include "MyTemplate.hpp"
#include "MyActorComponent.hpp"
#include "MyTransformComponent.hpp"

MINE_NAMESPACE_BEGIN

MyTransformComponent* MyTransformComponent::create(void) {
    MyTransformComponent *transform = new MyTransformComponent();
    transform->refName("MyTransformComponent");
    return transform;
}

MyTransformComponent* MyTransformComponent::createWithPosition(const MyFVector3 &pos) {
    MyTransformComponent *transform = new MyTransformComponent(pos);
    transform->refName("MyTransformComponent");
    return transform;
}

MINE_NAMESPACE_END
