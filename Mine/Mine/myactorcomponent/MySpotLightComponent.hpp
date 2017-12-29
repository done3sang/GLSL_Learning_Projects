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
    int attenuationType(void) const { return _attenuationType; }
    void attenuationType(int type) { _attenuationType = type; }
    
    float attenuationDistance(void) const { return _attenuationDistance; }
    void attenuationDistance(float dist) { _attenuationDistance = dist; }
    
    float attenuationExponent(void) const { return _attenuationExponent; }
    void attenuationExponent(float exp) { _attenuationExponent = exp; }
    
    float cutoff(void) const { return _cutoff; }
    void cutoff(float coneCos) { _cutoff = coneCos; }
    
private:
    explicit
    MySpotLightComponent(void):
    MyLightComponent(MyActorComponent::kComponentTypePointLight, "Point Light"),
    _cutoff(0.5f), _attenuationDistance(100.0f), _attenuationType(MyLightComponent::kLightAttenuationQuadratic) {}
    ~MySpotLightComponent(void) {}
    
    float _cutoff;
    float _attenuationDistance;
    float _attenuationExponent;
    int _attenuationType;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MySpotLightComponent_hpp */
