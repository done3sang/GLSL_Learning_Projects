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
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

template<class T>
class MyArray;
template<class T>
class MyData;
class MyUniqueObject;

class MyShader: public MyUniqueObject {
public:
    static constexpr int kShaderTypeVertex = GL_VERTEX_SHADER;
    static constexpr int kShaderTypeFragment = GL_FRAGMENT_SHADER;
    
    static MyShader* shaderWithType(const std::string &shaderName, int shaderType = kShaderTypeVertex);
    static MyShader* shaderWithContentsOfFile(const std::string &shaderName, int shaderType, const std::string &filepath);
    
    bool operator==(const MyShader &another) const {
        return 0 != _shaderId && _shaderId == another.shaderId();
    }
    
    bool loadFromFile(const std::string &filepath);
    bool loadFromSource(const char *source);
    
    int shaderType(void) const { return _shaderType; }
    GLuint shaderId(void) const { return _shaderId; }
    const std::string& shaderName(void) const { return _shaderName;}
    const std::string& shaderLog(void) const { return _shaderLog; }
    bool valid(void) const { return 0 != _shaderId; }
    bool ready(void) const { return _compiled;  }
    
    bool validate(void) const;
    void deleteShader(void);
    
public:
    static bool shaderType(int st) {
        return st == kShaderTypeVertex || st == kShaderTypeFragment;
    }
    
private:
    explicit
    MyShader(const std::string &shaderName, int shaderType = kShaderTypeVertex);
    MyShader(const std::string &shaderName, int shaderType, const std::string &filepath);
    ~MyShader(void);
    
private:
    GLuint _shaderId;
    int _shaderType;
    std::string _shaderName;
    std::string _filepath;
    std::string _shaderLog;
    bool _compiled;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyShader_hpp */
