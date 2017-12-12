//
//  MyDirectoinalLight.cpp
//  MyGLSL
//
//  Created by xy on 11/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <glm/glm.hpp>
#include "MyTemplate.hpp"
#include "MyActor.hpp"
#include "MyLight.hpp"
#include "MyDirectoinalLight.hpp"

MINE_NAMESPACE_BEGIN

MyDirectionalLight* MyDirectionalLight::createWithName(const std::string &lightName) {
    MyDirectionalLight *light = new MyDirectionalLight(lightName);
    light->refName("MyDirectionalLight");
    return light;
}


MINE_NAMESPACE_END
