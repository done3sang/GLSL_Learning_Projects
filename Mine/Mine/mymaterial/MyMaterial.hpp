//
//  MyMaterial.hpp
//  Mine
//
//  Created by xy on 2018/6/22.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MyMaterial_hpp
#define MyMaterial_hpp

#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyUniqueObject;
class MyTexture;

class MyMaterial: public MyUniqueObject {
public:
    static MyMaterial* create(void);
    static MyMaterial* createWithColor(const MyFVector4 &color);
    
public:
    FORCEINLINE const MyFVector4& baseColor(void) const { return _baseColor; }
    FORCEINLINE void baseColor(const MyFVector4 &color) { _baseColor = color; }
    
    FORCEINLINE float shininess(void) const { return _shininess; }
    FORCEINLINE void shininess(float shin) { _shininess = shin; }
    
    FORCEINLINE float ambientFactor(void) const { return _ambientFactor; }
    FORCEINLINE void ambientFactor(float factor) { _ambientFactor = factor; }
    
    FORCEINLINE float specularFactor(void) const { return _specularFactor; }
    FORCEINLINE void specularFactor(float factor) { _specularFactor = factor; }
    
private:
    explicit
    FORCEINLINE MyMaterialComponent(const MyFVector4 &color = MyFVector4(1.0f)):
    MyActorComponent(MyActorComponent::kComponentTypeMaterial,
                     MyActorComponent::kComponentGroupMaterial),
    _baseColor(color), _shininess(16.0f), _ambientFactor(0.01f), _specularFactor(16.0f) {}
    FORCEINLINE ~MyMaterialComponent(void) {}
    
    MyFVector4 _baseColor;
    float _shininess;
    float _ambientFactor;
    float _specularFactor;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyMaterial_hpp */
