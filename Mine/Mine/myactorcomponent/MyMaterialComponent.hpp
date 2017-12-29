//
//  MyMaterialComponent.hpp
//  MyGLSL
//
//  Created by xy on 11/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyMaterialComponent_hpp
#define MyMaterialComponent_hpp

#include <glm/fwd.hpp>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyActorComponent;

class MyMaterialComponent: public MyActorComponent {
public:
    static MyMaterialComponent* create(void);
    static MyMaterialComponent* createWithColor(const glm::vec4 &color);
    
    const glm::vec4& baseColor(void) const { return _baseColor; }
    void baseColor(const glm::vec4 &color) { _baseColor = color; }
    
    float shininess(void) const { return _shininess; }
    void shininess(float shin) { _shininess = shin; }
    
    float ambientFactor(void) const { return _ambientFactor; }
    void ambientFactor(float factor) { _ambientFactor = factor; }
    
    float specularFactor(void) const { return _specularFactor; }
    void specularFactor(float factor) { _specularFactor = factor; }
    
private:
    explicit
    MyMaterialComponent(const glm::vec4 &color = glm::vec4(1.0f)):
    MyActorComponent(MyActorComponent::kComponentTypeMaterial,
                     "Material",
                     MyActorComponent::kComponentGroupMaterial),
    _baseColor(color), _shininess(16.0f), _ambientFactor(0.01f), _specularFactor(16.0f) {}
    ~MyMaterialComponent(void) {}
    
    glm::vec4 _baseColor;
    float _shininess;
    float _ambientFactor;
    float _specularFactor;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyMaterialComponent_hpp */
