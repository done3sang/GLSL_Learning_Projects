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
class MyFVector3;

class MyMaterial: public MyUniqueObject {
public:
    static MyMaterial* create(void);
    
public:
    FORCEINLINE const MyFVector3& baseColor(void) const { return _baseColor; }
    FORCEINLINE void baseColor(const MyFVector3 &color) { _baseColor = color; _baseUniform = true; }
    
    FORCEINLINE bool baseUniform(void) const { return _baseUniform; }
    
    FORCEINLINE const MyTexture* baseTexture() const { return _baseTexture; }
    
    FORCEINLINE void baseTexture(MyTexture *baseTex) {
        if(_baseTexture) {
            _baseTexture->release();
            _baseUniform = true;
        }
        _baseTexture = baseTex;
        if(baseTex) {
            baseTex->addRef();
            _baseUniform = false;
        }
    }
    
private:
    explicit
    FORCEINLINE MyMaterial(void): _baseColor(1.0f, 1.0f, 1.0f),
    _baseTexture(nullptr), _normalTexture(nullptr), _metallic(16.0f), _opacity(1.0f), _baseUniform(true) {}
    FORCEINLINE ~MyMaterial(void) {}
    
    MyFVector3 _baseColor;
    MyTexture *_baseTexture;
    MyTexture *_normalTexture;
    float _metallic;
    float _opacity;
    bool _baseUniform;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyMaterial_hpp */
