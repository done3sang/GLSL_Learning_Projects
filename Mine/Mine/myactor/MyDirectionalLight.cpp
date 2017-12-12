//
//  MyDirectionalLight.cpp
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
#include "MyActor.hpp"
#include "MyDirectionalLight.hpp"

MINE_NAMESPACE_BEGIN

MyDirectionalLight* MyDirectionalLight::create(void) {
    MyDirectionalLight *actor = new MyDirectionalLight();
    actor->refName("MyDirectionalLight");
    return actor;
}

MyDirectionalLight::MyDirectionalLight(void) {
    addComponent(MyDirectionalLightComponent::create());
}

MINE_NAMESPACE_END
