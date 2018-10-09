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

MyMaterial* MyMaterial::material(void) {
    MyMaterial *mat = new MyMaterial;
    mat->objectName("MyMaterial");
    return mat;
}

MyMaterial::~MyMaterial(void) {
    purge();
}

void MyMaterial::shadingProgram(MyProgram *prog) {
    ASSIGN_OBJECT(_shadingProgram, prog);
}

void MyMaterial::baseTexture(MyTexture *baseTex) {
    ASSIGN_OBJECT(_baseTexture, baseTex);
}

void MyMaterial::normalTexture(MyTexture *normalTex) {
    ASSIGN_OBJECT(_normalTexture, normalTex);
}

void MyMaterial::purge(void) {
    RELEASE_OBJECT(_baseTexture);
    RELEASE_OBJECT(_normalTexture);
}

MINE_NAMESPACE_END
