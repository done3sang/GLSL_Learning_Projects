//
//  MyDirectionalLightComponent.cpp
//  MyGLSL
//
//  Created by xy on 12/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <glm/glm.hpp>
#include "MyTemplate.hpp"
#include "MyActorComponent.hpp"
#include "MyLightComponent.hpp"
#include "MyDirectionalLightComponent.hpp"

MINE_NAMESPACE_BEGIN

MyDirectionalLightComponent* MyDirectionalLightComponent::create(void) {
    MyDirectionalLightComponent *light = new MyDirectionalLightComponent;
    light->objectName("MyDirectionalLightComponent");
    return light;
}

MINE_NAMESPACE_END
