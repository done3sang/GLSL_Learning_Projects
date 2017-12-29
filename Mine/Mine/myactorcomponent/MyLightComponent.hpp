//
//  MyLightComponent.hpp
//  MyGLSL
//
//  Created by xy on 11/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyLightComponent_hpp
#define MyLightComponent_hpp

#include <string>
#include <glm/fwd.hpp>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyActorComponent;

class MyLightComponent: public MyActorComponent {
public:
    static const int kLightAttenuationNone;
    static const int kLightAttenuationConstant;
    static const int kLightAttenuationLinear;
    static const int kLightAttenuationQuadratic;
    static const int kLightAttenuationExponent;
    
public:
    void lightIntensity(float intensity) { _lightIntensity = intensity; }
    float lightIntensity(void) const { return _lightIntensity; }
    
    //void ambientFactor(float factor) { _ambientFactor = factor; }
    //float ambientFactor(void) const { return _ambientFactor; }
    
    void lightColor(const glm::vec3 &color) { _lightColor = color; }
    const glm::vec3& lightColor(void) const { return _lightColor; }
    
    void ambientEnabled(bool enabled = true) { _ambientEnabled = enabled; }
    bool ambientEnabled(void) const { return _ambientEnabled; }
    
    void diffuseEnabled(bool enabled = true) { _diffuseEnabled = enabled; }
    bool diffuseEnabled(void) const { return _diffuseEnabled; }
    
    void specularEnabled(bool enabled = true) { _specularEnabled = enabled; }
    bool specularEnabled(void) const { return _specularEnabled; }
    
protected:
    explicit
    MyLightComponent(int compType, const std::string &lightName):
    MyActorComponent(compType, lightName, MyActorComponent::kComponentGroupLight),
    _lightIntensity(100.0f), _lightColor(1.0f),
    _ambientEnabled(true), _diffuseEnabled(true), _specularEnabled(true) {}
    virtual ~MyLightComponent(void) {}
    
private:
    float _lightIntensity;
    glm::vec3 _lightColor;
    
    bool _ambientEnabled;
    bool _diffuseEnabled;
    bool _specularEnabled;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyLightComponent_hpp */
