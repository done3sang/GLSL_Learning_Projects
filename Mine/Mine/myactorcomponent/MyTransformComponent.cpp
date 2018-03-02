//
//  MyTransformComponent.cpp
//  Mine
//
//  Created by xy on 27/02/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//


#include "MyVector.hpp"
#include "MyMatrix.hpp"
#include "MyQuaternion.hpp"
#include "MyCoordinate.hpp"
#include "MyTemplate.hpp"
#include "MyActorComponent.hpp"
#include "MyTransformComponent.hpp"

MINE_NAMESPACE_BEGIN

MyTransformComponent* MyTransformComponent::create(void) {
    MyTransformComponent *transform = new MyTransformComponent();
    transform->objectName("MyTransformComponent");
    return transform;
}

MyTransformComponent* MyTransformComponent::createWithPosition(const MyFVector3 &pos) {
    MyTransformComponent *transform = new MyTransformComponent(pos);
    transform->objectName("MyTransformComponent");
    return transform;
}

MINE_NAMESPACE_END
