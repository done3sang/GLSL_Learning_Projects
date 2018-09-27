//
//  MySpotLight.cpp
//  MyGLSL
//
//  Created by xy on 12/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyVector.hpp"
#include "MyObject.hpp"
#include "MyActorComponent.hpp"
#include "MyActor.hpp"
#include "MyProgram.hpp"
#include "MyLightActor.hpp"
#include "MyLightComponent.hpp"
#include "MySpotLightComponent.hpp"
#include "MySpotLight.hpp"

MINE_NAMESPACE_BEGIN

MySpotLight* MySpotLight::createWithName(const std::string &name) {
    MySpotLight *light = new MySpotLight;
    light->actorName(name);
    light->objectName(name);
    pushWorldLight(light);
    return light;
}

MySpotLight::MySpotLight(void) {
    _lightComponent = MySpotLightComponent::create();
    addComponent(_lightComponent);
}

void MySpotLight::bindProgram(MyProgram *prog) {
    //prog->uniformVector4("lightInfo.position", glm::vec4(0.0f, 10.0f, 0.0f, 1.0f));
    //prog->uniformVector3("lightInfo.color", _lightComponent->lightColor());
    //prog->uniformFloat("lightInfo.intensity", _lightComponent->lightIntensity());
    prog->uniformFloat("lightInfo.ambientFactor", 0.01);
    //prog->uniformBool("lightInfo.ambientEnabled", _lightComponent->ambientEnabled());
    //prog->uniformBool("lightInfo.diffuseEnabled", _lightComponent->diffuseEnabled());
    //prog->uniformBool("lightInfo.specularEnabled", _lightComponent->specularEnabled());
    prog->uniformFloat("lightInfo.attenuationDistance", _lightComponent->attenuationDistance());
    prog->uniformBool("lightInfo.spotlight", true);
    //prog->uniformVector3("lightInfo.direction", glm::vec3(0.0f, -1.0f, 0.0f));
    prog->uniformFloat("lightInfo.attenuationExponent", _lightComponent->attenuationExponent());
    prog->uniformFloat("lightInfo.cutoff", _lightComponent->cutoff());
}

MINE_NAMESPACE_END
