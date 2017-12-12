//
//  MySpotLight.cpp
//  MyGLSL
//
//  Created by xy on 12/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <glm/glm.hpp>
#include "MyTemplate.hpp"
#include "MyActorComponent.hpp"
#include "MyActor.hpp"
#include "MyLightComponent.hpp"
#include "MySpotLightComponent.hpp"
#include "MySpotLight.hpp"

MINE_NAMESPACE_BEGIN

MySpotLight* MySpotLight::create(void) {
    MySpotLight *actor = new MySpotLight;
    actor->refName("MySpotLight");
    return actor;
}

MySpotLight::MySpotLight(void) {
    addComponent(MySpotLightComponent::create());
}

MINE_NAMESPACE_END
