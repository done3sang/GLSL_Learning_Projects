//
//  MyMaterial.cpp
//  Mine
//
//  Created by xy on 2018/6/22.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#include "MyObject.hpp"
#include "MyVector.hpp"
#include "MyImage.hpp"
#include "MyTexture.hpp"
#include "MyProgram.hpp"
#include "MyMaterial.hpp"

MINE_NAMESPACE_BEGIN

MyMaterial* MyMaterial::materialWithName(const char *name) {
    MyMaterial *mat = new MyMaterial;
    mat->objectName(name);
    return mat;
}

MyMaterial::~MyMaterial(void) {
    purge();
}

void MyMaterial::shadingProgram(MyProgram *prog) {
    MyObject::assign(_shadingProgram, prog);
}

void MyMaterial::baseTexture(MyTexture *baseTex) {
    MyObject::assign(_baseTexture, baseTex);
}

void MyMaterial::normalTexture(MyTexture *normalTex) {
    MyObject::assign(_normalTexture, normalTex);
}

void MyMaterial::purge(void) {
    if(_baseTexture) {
        _baseTexture->release();
        _baseTexture = nullptr;
    }
    if(_normalTexture) {
        _normalTexture->release();
        _normalTexture = nullptr;
    }
}

MINE_NAMESPACE_END
