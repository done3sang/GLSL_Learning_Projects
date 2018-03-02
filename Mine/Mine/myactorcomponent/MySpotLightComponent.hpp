//
//  MySpotLightComponent.hpp
//  MyGLSL
//
//  Created by xy on 12/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MySpotLightComponent_hpp
#define MySpotLightComponent_hpp

#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyActorComponent;
class MyLightComponent;

class MySpotLightComponent: public MyLightComponent {
public:
    static MySpotLightComponent* create(void);
    
public:
    FORCEINLINE int attenuationType(void) const { return _attenuationType; }
    FORCEINLINE void attenuationType(int type) { _attenuationType = type; }
    
    FORCEINLINE float attenuationDistance(void) const { return _attenuationDistance; }
    FORCEINLINE void attenuationDistance(float dist) { _attenuationDistance = dist; }
    
    FORCEINLINE float attenuationExponent(void) const { return _attenuationExponent; }
    FORCEINLINE void attenuationExponent(float exp) { _attenuationExponent = exp; }
    
    FORCEINLINE float cutoff(void) const { return _cutoff; }
    FORCEINLINE void cutoff(float coneCos) { _cutoff = coneCos; }
    
private:
    explicit
    FORCEINLINE MySpotLightComponent(void):
    MyLightComponent(MyActorComponent::kComponentTypePointLight),
    _cutoff(0.5f), _attenuationDistance(100.0f), _attenuationType(MyLightComponent::kLightAttenuationQuadratic) {}
    FORCEINLINE ~MySpotLightComponent(void) {}
    
    float _cutoff;
    float _attenuationDistance;
    float _attenuationExponent;
    int _attenuationType;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MySpotLightComponent_hpp */
