//
//  MyTexture.hpp
//  Mine
//
//  Created by xy on 2018/6/22.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MyTexture_hpp
#define MyTexture_hpp

#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyUniqueObject;
class MyFVector3;
class MyFVector4;

class MyTexture: public MyUniqueObject {
public:
    static MyTexture* create(void);
    static MyTexture* createWithColor(const MyFVector3 &color);
    static MyTexture* createWithColor(const MyFVector4 &color);
    
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
    MyFVector4 _baseColor;
    float _shininess;
    float _ambientFactor;
    float _specularFactor;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyTexture_hpp */
