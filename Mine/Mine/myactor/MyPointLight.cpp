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
#include "MyProgram.hpp"
#include "MyLightActor.hpp"
#include "MyLightComponent.hpp"
#include "MyPointLightComponent.hpp"
#include "MyPointLight.hpp"

MINE_NAMESPACE_BEGIN

MyPointLight* MyPointLight::create(void) {
    MyPointLight *light = new MyPointLight();
    light->refName("MyPointLight");
    pushScenarioLight(light);
    return light;
}

MyPointLight::MyPointLight(void) {
    lightComponent = MyPointLightComponent::create();
    addComponent(lightComponent);
}

void MyPointLight::bindProgram(MyProgram *prog) {
    prog->uniformVector4("lightInfo.position", glm::vec4(0.0f, 10.0f, 0.0f, 1.0f));
    prog->uniformVector3("lightInfo.color", lightComponent->lightColor());
    prog->uniformFloat("lightInfo.intensity", lightComponent->lightIntensity());
    prog->uniformFloat("lightInfo.ambientFactor", 0.01);
    prog->uniformBool("lightInfo.ambientEnabled", lightComponent->ambientEnabled());
    prog->uniformBool("lightInfo.diffuseEnabled", lightComponent->diffuseEnabled());
    prog->uniformBool("lightInfo.specularEnabled", lightComponent->specularEnabled());
    prog->uniformFloat("lightInfo.attenuationDistance", lightComponent->attenuationDistance());
    prog->uniformBool("lightInfo.spotlight", false);
}

MINE_NAMESPACE_END
