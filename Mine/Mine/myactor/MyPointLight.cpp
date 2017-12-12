//
//  MyPointLight.cpp
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
#include "MyPointLightComponent.hpp"
#include "MyPointLight.hpp"

MINE_NAMESPACE_BEGIN

MyPointLight* MyPointLight::create(void) {
    MyPointLight *actor = new MyPointLight;
    actor->refName("MyPointLight");
    return actor;
}

MyPointLight::MyPointLight(void) {
    addComponent(MyPointLightComponent::create());
}

MINE_NAMESPACE_END
