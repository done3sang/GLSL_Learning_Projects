//
//  MyTexture2D.hpp
//  Mine
//
//  Created by xy on 2018/9/26.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MyTexture2D_hpp
#define MyTexture2D_hpp

#include "MyPrecompiled.hpp"
#include "MyTexture.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyImage;

class MyTexture2D final: public MyTexture {
public:
    static MyTexture2D* texture(const MyTextureFilter& filter = MyTextureFilter::Linear,
                         const MyTextureWrap& wrap = MyTextureWrap::Clamp);
    
    static MyTexture2D* textureWithColor(const MyFVector4& color,
                                  const MyTextureFilter& filter = MyTextureFilter::Linear,
                                  const MyTextureWrap& wrap = MyTextureWrap::Clamp);
    
    static MyTexture2D* textureWithImage(MyImage* image,
                                  const MyTextureFilter& filter = MyTextureFilter::Linear,
                                  const MyTextureWrap& wrap = MyTextureWrap::Clamp);
    
    void purge(void);
    
public:
    FORCEINLINE int width(void) const {
        MINE_ASSERT(_image);
        return _image->width();
    }
    FORCEINLINE int height(void) const {
        MINE_ASSERT(_image);
        return _image->height();
    }
    FORCEINLINE const MyTextureFormat& format(void) const {
        MINE_ASSERT(_image);
        return _image->format();
    }
    FORCEINLINE const MyImage* image(void) const { return _image; }
    
    void image(MyImage* newImage, int nullWidth = 1, int nullHeight = 1);
    
    virtual void bind(void) const;
    
protected:
    virtual void generateTexture(void);
    virtual void changeFilter(void);
    virtual void changeWrap(void);
    
    void changeImage(int nullWidth, int nullHeight);
    
private:
    FORCEINLINE MyTexture2D(const MyTextureFilter& filter, const MyTextureWrap& wrap):
    MyTexture(filter, wrap),
    _image(nullptr) {}
    MyTexture2D(const MyFVector4& color, const MyTextureFilter& filter, const MyTextureWrap& wrap);
    MyTexture2D(MyImage* image, const MyTextureFilter& filter, const MyTextureWrap& wrap);
    virtual ~MyTexture2D(void);
    
    MyImage* _image;
    
    void initWithColor(const MyFVector4& color);
    void initWithImage(MyImage* image);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyTexture2D_hpp */
