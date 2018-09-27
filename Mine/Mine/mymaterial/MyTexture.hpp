//
//  MyTexture.hpp
//  Mine
//
//  Created by xy on 2018/9/25.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MyTexture_hpp
#define MyTexture_hpp

#include <GLFW/glfw3.h>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyUniqueObject;
class MyImage;

enum class MyTextureType {
    Image,
    Cube
};

enum class MyTextureFilter {
    Linear = GL_LINEAR,
    Nearest = GL_NEAREST
};

enum class MyTextureWrap {
    Clamp = GL_CLAMP_TO_BORDER,
    Repeat = GL_REPEAT
};

class MyTexture: public MyUniqueObject {
public:
    FORCEINLINE const MyTextureFilter& filter(void) const { return _filter; }
    FORCEINLINE const MyTextureWrap& wrap(void) const { return _wrap; }
    FORCEINLINE const bool ready(void) const { return 0 != _Id; }
    FORCEINLINE GLuint textureId(void) const { return _Id; }
    
    void filter(const MyTextureFilter& newFilter);
    void wrap(const MyTextureWrap& newWrap);
    
    void purge(void);
    
    virtual void bind(void) const = 0;
    
protected:
    FORCEINLINE MyTexture(const MyTextureFilter& filter,
                          const MyTextureWrap& wrap):
    _Id(0),
    _filter(filter),
    _wrap(wrap) {}
    virtual ~MyTexture(void);
    
    virtual void generateTexture(void) = 0;
    virtual void changeFilter(void) = 0;
    virtual void changeWrap(void) = 0;
    
private:
    GLuint _Id;
    MyTextureFilter _filter;
    MyTextureWrap _wrap;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyTexture_hpp */
