//
//  MyTexture.cpp
//  Mine
//
//  Created by xy on 2018/9/25.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#include "MyObject.hpp"
#include "MyVector.hpp"
#include "MyImage.hpp"
#include "MyTexture.hpp"

MINE_NAMESPACE_BEGIN

MyTexture::~MyTexture(void) {
    purge();
}

void MyTexture::generateTexture(void) {
    if(0 == _Id) {
        glGenTextures(1, &_Id);
    }
}

void MyTexture::changeFilter(void) {
    if(!ready()) {
        return;
    }
}

void MyTexture::changeWrap(void) {
    if(!ready()) {
        return;
    }
}

void MyTexture::bind(void) const {
    MINE_ASSERT2(ready(), "Error MyTexture::bind, texture has NOT generated.");
}

void MyTexture::filter(const MyTextureFilter &newFilter) {
    _filter = newFilter;
    changeFilter();
}

void MyTexture::wrap(const MyTextureWrap &newWrap) {
    _wrap = newWrap;
    changeWrap();
}

void MyTexture::purge(void) {
    if(ready()) {
        glDeleteTextures(1, &_Id);
        _Id = 0;
    }
}

MINE_NAMESPACE_END
