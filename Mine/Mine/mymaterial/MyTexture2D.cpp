//
//  MyTexture2D.cpp
//  Mine
//
//  Created by xy on 2018/9/26.
//  Copyright © 2018 SangDesu. All rights reserved.
//


#include "MyObject.hpp"
#include "MyVector.hpp"
#include "MyData.hpp"
#include "MyImage.hpp"
#include "MyTexture2D.hpp"

MINE_NAMESPACE_BEGIN

MyTexture2D* MyTexture2D::texture(const MyTextureFilter& filter,
                                  const MyTextureWrap& wrap) {
    MyTexture2D *texture = new MyTexture2D(filter, wrap);
    texture->objectName("MyTexture2D");
    return texture;
}

MyTexture2D* MyTexture2D::textureWithColor(const MyFVector4 &color,
                                           const MyTextureFilter& filter,
                                           const MyTextureWrap& wrap) {
    MyTexture2D *texture = new MyTexture2D(color, filter, wrap);
    texture->objectName("MyTexture2D");
    return texture;
}

MyTexture2D* MyTexture2D::textureWithImage(MyImage* image,
                                           const MyTextureFilter& filter,
                                           const MyTextureWrap& wrap) {
    MyTexture2D *texture = new MyTexture2D(image, filter, wrap);
    texture->objectName("MyTexture2D");
    return texture;
}

MyTexture2D::MyTexture2D(const MyFVector4 &color,
                         const MyTextureFilter& filter,
                         const MyTextureWrap& wrap):
MyTexture(filter, wrap) {
    initWithColor(color);
}

MyTexture2D::MyTexture2D(MyImage* image,
                         const MyTextureFilter& filter,
                         const MyTextureWrap& wrap):
MyTexture(filter, wrap) {
    initWithImage(image);
}

MyTexture2D::~MyTexture2D(void) {
    purge();
}

void MyTexture2D::initWithColor(const MyFVector4 &color) {
    initWithImage(MyImage::imageWithColor(color));
}

void MyTexture2D::initWithImage(MyImage *image) {
    if(image) {
        image->addRef();
    }
    _image = image;
    generateTexture();
}

void MyTexture2D::purge(void) {
    if(_image) {
        _image->release();
        _image = nullptr;
    }
}

void MyTexture2D::image(MyImage *newImage, int nullWidth, int nullHeight) {
    if(_image) {
        _image->release();
    }
    if(newImage) {
        newImage->addRef();
    }
    _image = newImage;
    changeImage(nullWidth, nullHeight);
}

void MyTexture2D::bind(void) const {
    MyTexture::bind();
    glBindTexture(GL_TEXTURE_2D, textureId());
}

void MyTexture2D::generateTexture(void) {
    MINE_ASSERT2(_image, "Error MyTexture2D::generateTexture, image null");
    MyTexture::generateTexture();
    bind();
    
    GLint textureFormat = static_cast<GLint>(_image->format());
    GLint textureFilter = static_cast<GLint>(filter());
    GLint textureWrap = static_cast<GLint>(wrap());
    const unsigned char* data = _image->data()->raw();
    
    glTexImage2D(GL_TEXTURE_2D,
                 0, textureFormat,
                 _image->width(), _image->height(),
                 0, textureFormat,
                 GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrap);
}

void MyTexture2D::changeFilter(void) {
    MyTexture::changeFilter();
    
    GLint textureFilter = static_cast<GLint>(filter());
    
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilter);
}

void MyTexture2D::changeWrap(void) {
    MyTexture::changeWrap();
    
    GLint textureWrap = static_cast<GLint>(wrap());
    
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrap);
}

void MyTexture2D::changeImage(int nullWidth, int nullHeight) {
    if(_image) {
        nullWidth = _image->width();
        nullHeight = _image->height();
    }
    
    bind();
    GLint textureFormat = nullptr != _image ? static_cast<GLint>(_image->format()): GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D,
                 0, textureFormat,
                 nullWidth, nullHeight,
                 0, textureFormat,
                 GL_UNSIGNED_BYTE, nullptr != _image ? _image->data()->raw(): nullptr);
}

MINE_NAMESPACE_END
