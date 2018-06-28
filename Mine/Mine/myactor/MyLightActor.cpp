//
//  MyLightActor.cpp
//  Mine
//
//  Created by xy on 03/01/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#include "MyObject.hpp"
#include "MyProgram.hpp"
#include "MyActorComponent.hpp"
#include "MyActor.hpp"
#include "MyLightActor.hpp"

MINE_NAMESPACE_BEGIN

MyLightActor::MyLightActor(void) {
    pushScenarioLight(this);
}

MyLightActor::~MyLightActor(void) {
    popScenarioLight(this);
}

MINE_NAMESPACE_END
