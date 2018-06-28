//
//  MySpotLightComponent.cpp
//  MyGLSL
//
//  Created by xy on 12/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyVector.hpp"
#include "MyObject.hpp"
#include "MyActorComponent.hpp"
#include "MyLightComponent.hpp"
#include "MySpotLightComponent.hpp"

MINE_NAMESPACE_BEGIN

MySpotLightComponent* MySpotLightComponent::create(void) {
    MySpotLightComponent *light = new MySpotLightComponent;
    light->objectName("MySpotLightComponent");
    return light;
}

MINE_NAMESPACE_END
