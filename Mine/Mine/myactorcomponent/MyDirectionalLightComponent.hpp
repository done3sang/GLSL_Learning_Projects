//
//  MyDirectionalLightComponent.hpp
//  MyGLSL
//
//  Created by xy on 12/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyDirectionalLightComponent_hpp
#define MyDirectionalLightComponent_hpp

#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyActorComponent;
class MyLightComponent;

class MyDirectionalLightComponent: public MyLightComponent {
public:
    static MyDirectionalLightComponent* create(void);
    
private:
    explicit
    MyDirectionalLightComponent(void):
    MyLightComponent(MyActorComponent::kComponentTypeDirectionalLight, "Directional Light") {}
    ~MyDirectionalLightComponent(void) {}
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyDirectionalLightComponent_hpp */
