//
//  MyActorComponent.cpp
//  MyGLSL
//
//  Created by xy on 11/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyTemplate.hpp"
#include "MyActorComponent.hpp"

MINE_NAMESPACE_BEGIN

const int MyActorComponent::kComponentTypeNone = 0;
const int MyActorComponent::kComponentTypeMaterial = 1;
const int MyActorComponent::kComponentTypeDirectionalLight = 2;
const int MyActorComponent::kComponentTypePointLight = 3;
const int MyActorComponent::kComponentTypeSpotLight = 4;

const int MyActorComponent::kComponentGroupNone = 0;
const int MyActorComponent::kComponentGroupMaterial = 1;
const int MyActorComponent::kComponentGroupLight = 2;

MINE_NAMESPACE_END
