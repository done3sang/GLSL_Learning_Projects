//
//  MyLightComponent.cpp
//  MyGLSL
//
//  Created by xy on 11/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <glm/glm.hpp>
#include "MyTemplate.hpp"
#include "MyActorComponent.hpp"
#include "MyLightComponent.hpp"

MINE_NAMESPACE_BEGIN

const int MyLightComponent::kLightAttenuationNone = 0;
const int MyLightComponent::kLightAttenuationConstant = 1;
const int MyLightComponent::kLightAttenuationLinear = 2;
const int MyLightComponent::kLightAttenuationQuadratic = 3;
const int MyLightComponent::kLightAttenuationExponent = 4;

MINE_NAMESPACE_END
