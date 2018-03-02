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
    FORCEINLINE int attenuationType(void) const { return _attenuationType; }
    FORCEINLINE void attenuationType(int type) { _attenuationType = type; }
    
    FORCEINLINE float attenuationDistance(void) const { return _attenuationDistance; }
    FORCEINLINE void attenuationDistance(float dist) { _attenuationDistance = dist; }
    
private:
    explicit
    FORCEINLINE MyPointLightComponent(void):
    MyLightComponent(MyActorComponent::kComponentTypePointLight),
    _attenuationDistance(100.0f), _attenuationType(MyLightComponent::kLightAttenuationQuadratic) {}
    FORCEINLINE ~MyPointLightComponent(void) {}
    
    float _attenuationDistance;
    int _attenuationType;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyPointLightComponent_hpp */
