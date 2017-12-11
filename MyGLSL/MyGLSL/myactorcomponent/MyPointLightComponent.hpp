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
    static MyPointLightComponent* createWithPosition(const glm::vec3 &pos);
    
public:
    const glm::vec3& lightPosition(void) const { return _lightPosition; }
    void lightPosition(const glm::vec3 &pos) { _lightPosition = pos; }
    
    int attenuationType(void) const { return _attenuationType; }
    void attenuationType(int type) { _attenuationType = type; }
    
    float attenuationDistance(void) const { return _attenuationDistance; }
    void attenuationDistance(float dist) { _attenuationDistance = dist; }
    
private:
    explicit
    MyPointLightComponent(const glm::vec3 &pos = glm::vec3(0.0f)):
    MyLightComponent(MyActorComponent::kComponentTypePointLight, "Point Light"),
    _attenuationDistance(100.0f), _attenuationType(MyLightComponent::kLightAttenuationQuadratic) {}
    ~MyPointLightComponent(void) {}
    
    glm::vec3 _lightPosition;
    float _attenuationDistance;
    int _attenuationType;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyPointLightComponent_hpp */
