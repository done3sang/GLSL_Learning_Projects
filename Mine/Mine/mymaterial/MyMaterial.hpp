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
class MyProgram;
class MyFVector3;

class MyMaterial: public MyUniqueObject {
public:
    static constexpr char kBaseTexture[] = "baseTexture";
    static constexpr char kNormalTexture[] = "normalTexture";
    
public:
    static MyMaterial* material(void);
    
public:
    FORCEINLINE float metallic(void) const { return _metallic; }
    FORCEINLINE void metallic(float metallic) { _metallic = metallic; }
    FORCEINLINE float opacity(void) const { return _opacity; }
    FORCEINLINE void opacity(float opacity) { _opacity = opacity; }
    FORCEINLINE MyProgram* shadingProgram(void) const { return _shadingProgram; }
    FORCEINLINE const MyTexture* baseTexture(void) const { return _baseTexture; }
    FORCEINLINE const MyTexture* normalTexture(void) const { return _normalTexture; }
    
    void shadingProgram(MyProgram *prog);
    void baseTexture(MyTexture *baseTex);
    void normalTexture(MyTexture *normalTex);
    
    void purge(void);
    
private:
    explicit
    FORCEINLINE MyMaterial(void):
    _shadingProgram(nullptr),
    _baseTexture(nullptr),
    _normalTexture(nullptr),
    _metallic(16.0f),
    _opacity(1.0f) {}
    virtual ~MyMaterial(void);
    
    MyProgram *_shadingProgram;
    MyTexture *_baseTexture;
    MyTexture *_normalTexture;
    float _metallic;
    float _opacity;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyMaterial_hpp */
