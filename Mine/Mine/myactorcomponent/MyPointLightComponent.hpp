//
//  MyPointLightComponent.hpp
//  MyGLSL
//
//  Created by xy on 11/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyPointLightComponent_hpp
#define MyPointLightComponent_hpp

#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyActorComponent;
class MyLightComponent;

class MyPointLightComponent: public MyLightComponent {
public:
    static MyPointLightComponent* create(void);
    
public:
    int attenuationType(void) const { return _attenuationType; }
    void attenuationType(int type) { _attenuationType = type; }
    
    float attenuationDistance(void) const { return _attenuationDistance; }
    void attenuationDistance(float dist) { _attenuationDistance = dist; }
    
private:
    explicit
    MyPointLightComponent(void):
    MyLightComponent(MyActorComponent::kComponentTypePointLight, "Point Light"),
    _attenuationDistance(100.0f), _attenuationType(MyLightComponent::kLightAttenuationQuadratic) {}
    ~MyPointLightComponent(void) {}
    
    float _attenuationDistance;
    int _attenuationType;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyPointLightComponent_hpp */
