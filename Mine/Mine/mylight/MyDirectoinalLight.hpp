//
//  MyDirectoinalLight.hpp
//  MyGLSL
//
//  Created by xy on 11/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyDirectoinalLight_hpp
#define MyDirectoinalLight_hpp

#include <string>
#include <glm/fwd.hpp>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyLight;

class MyDirectionalLight: public MyLight {
public:
    static MyDirectionalLight* createWithName(const std::string &lightName);
    
private:
    explicit
    MyDirectionalLight(const std::string &lightName): MyLight(lightName) {}
    ~MyDirectionalLight(void) {}
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyDirectoinalLight_hpp */
