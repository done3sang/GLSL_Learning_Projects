//
//  MyTexture.hpp
//  Mine
//
//  Created by xy on 2018/6/22.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MyImage_hpp
#define MyImage_hpp

#include <GLFW/glfw3.h>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyUniqueObject;
class MyFVector3;
class MyFVector4;
template<typename T>
class MyData;

enum class MyTextureFormat {
    RGB = GL_RGB,
    RGBA = GL_RGBA
};

class MyImage: public MyUniqueObject {
public:
    static MyImage* image(void);
    static MyImage* imageWithColor(const MyFVector3& color);
    static MyImage* imageWithColor(const MyFVector4& color);
    static MyImage* imageWithContentsOfFile(const char* path);
    
public:
    int width(void) const { return _width; }
    int height(void) const { return _height; }
    const MyTextureFormat& format(void) { return _format; }
    const MyData<unsigned char>* data(void) { return _data; }
    
    void purge(void);
    
private:
    FORCEINLINE MyImage(void):
    _width(0),
    _height(0),
    _data(nullptr),
    _format(MyTextureFormat::RGBA) {}
    MyImage(const MyFVector3& color);
    MyImage(const MyFVector4& color);
    MyImage(const char* path);
    virtual ~MyImage(void);
    
    int _width;
    int _height;
    MyTextureFormat _format;
    MyData<unsigned char>* _data;
    
    void initWithColor(const MyFVector4& color);
    void initWithContentsOfFile(const char* path);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyTexture_hpp */
