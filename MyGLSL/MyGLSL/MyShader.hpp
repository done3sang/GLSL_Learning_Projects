//
//  MyShader.hpp
//  MyGLSL
//
//  Created by xy on 28/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyShader_hpp
#define MyShader_hpp

#include <GLFW/glfw3.h>
#include <string>
#include "Precompiled.h"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyShader {
public:
    MyShader(int shaderType = kShaderTypeVertex);
    MyShader(int shaderType, const std::string &filepath);
    ~MyShader(void);
    
    bool operator==(const MyShader &another) const {
        return 0 != _shaderId && _shaderId == another.shaderId();
    }
    
    int loadFromFile(const std::string &filepath);
    int loadFromSource(const std::string &source);
    
    int shaderType(void) const { return _shaderType; }
    GLuint shaderId(void) const { return _shaderId; }
    const std::string& shaderLog(void) const { return _shaderLog; }
    bool valid(void) const { return 0 != _shaderId; }
    bool compiled(void) const { return _compiled;  }
    
    bool validate(void) const;
    void deleteShader(void);
    
public:
    static const int kShaderTypeVertex = GL_VERTEX_SHADER;
    static const int kShaderTypeFragment = GL_FRAGMENT_SHADER;
    
private:
    GLuint _shaderId;
    int _shaderType;
    std::string _filepath;
    std::string _shaderLog;
    bool _compiled;
    
    MyShader(const MyShader&);
    MyShader& operator=(const MyShader&);
};

MINE_NAMESPACE_END

#endif /* MyShader_hpp */
