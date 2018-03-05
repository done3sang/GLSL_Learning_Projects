//
//  MyPointLightComponent.cpp
//  MyGLSL
//
//  Created by xy on 11/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyVector.hpp"
#include "MyTemplate.hpp"
#include "MyActorComponent.hpp"
#include "MyLightComponent.hpp"
#include "MyPointLightComponent.hpp"

MINE_NAMESPACE_BEGIN

MyPointLightComponent* MyPointLightComponent::create(void) {
    MyPointLightComponent *light = new MyPointLightComponent;
    light->objectName("MyPointLightComponent");
    return light;
}

MINE_NAMESPACE_END
