//
//  MySpotLightComponent.cpp
//  MyGLSL
//
//  Created by xy on 12/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <glm/glm.hpp>
#include "MyTemplate.hpp"
#include "MyActorComponent.hpp"
#include "MyLightComponent.hpp"
#include "MySpotLightComponent.hpp"

MINE_NAMESPACE_BEGIN

MySpotLightComponent* MySpotLightComponent::create(void) {
    MySpotLightComponent *light = new MySpotLightComponent;
    light->refName("MySpotLightComponent");
    return light;
}

MINE_NAMESPACE_END
