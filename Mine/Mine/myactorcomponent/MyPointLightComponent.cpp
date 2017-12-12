//
//  MyPointLightComponent.cpp
//  MyGLSL
//
//  Created by xy on 11/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <glm/glm.hpp>
#include "MyTemplate.hpp"
#include "MyActorComponent.hpp"
#include "MyLightComponent.hpp"
#include "MyPointLightComponent.hpp"

MINE_NAMESPACE_BEGIN

MyPointLightComponent* MyPointLightComponent::create(void) {
    MyPointLightComponent *light = new MyPointLightComponent;
    light->refName("MyPointLightComponent");
    return light;
}

MINE_NAMESPACE_END
