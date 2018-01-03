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
#include "MyProgram.hpp"
#include "MyActor.hpp"
#include "MyLightActor.hpp"
#include "MyDirectionalLight.hpp"

MINE_NAMESPACE_BEGIN

MyDirectionalLight* MyDirectionalLight::create(void) {
    MyDirectionalLight *light = new MyDirectionalLight();
    light->refName("MyDirectionalLight");
    pushScenarioLight(light);
    return light;
}

MyDirectionalLight::MyDirectionalLight(void) {
    lightComponent = MyDirectionalLightComponent::create();
    addComponent(lightComponent);
}

void MyDirectionalLight::bindProgram(Mine::MyProgram *prog) {
    prog->uniformVector4("lightInfo.position", glm::vec4(1.0f, 1.0f, -1.0f, 0.0f));
    prog->uniformVector3("lightInfo.color", lightComponent->lightColor());
    prog->uniformFloat("lightInfo.intensity", lightComponent->lightIntensity());
    prog->uniformFloat("lightInfo.ambientFactor", 0.01);
    prog->uniformBool("lightInfo.ambientEnabled", lightComponent->ambientEnabled());
    prog->uniformBool("lightInfo.diffuseEnabled", lightComponent->diffuseEnabled());
    prog->uniformBool("lightInfo.specularEnabled", lightComponent->specularEnabled());
}

MINE_NAMESPACE_END
