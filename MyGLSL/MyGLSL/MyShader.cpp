//
//  MyShader.cpp
//  MyGLSL
//
//  Created by xy on 28/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyTemplate.hpp"
#include "MyShader.hpp"
#include "MyFileUtil.hpp"
#include "MyErrorDesc.hpp"

MINE_NAMESPACE_BEGIN

MyShader::MyShader(const std::string &shaderName, int shaderType):
_shaderId(0),
_shaderName(shaderName),
_shaderType(shaderType),
_compiled(false) {}

MyShader::MyShader(const std::string &shaderName, int shaderType, const std::string &filepath):
_shaderId(0),
_shaderName(shaderName),
_shaderType(shaderType),
_compiled(false) {
    loadFromFile(filepath);
}

MyShader::~MyShader(void) {
    deleteShader();
}

MyShader* MyShader::createWithShaderType(const std::string &shaderName, int shaderType) {
    MyShader *shader = new MyShader(shaderName, shaderType);
    shader->refName("MyShader");
    return shader;
}


MyShader* MyShader::createWithShaderTypeAndPath(const std::string &shaderName, int shaderType, const std::string &filepath) {
    MyShader *shader = new MyShader(shaderName, shaderType, filepath);
    shader->refName("MyShader");
    
    return shader;
}

bool MyShader::validate(void) const {
    return glIsShader(_shaderId);
}

void MyShader::deleteShader(void) {
    if(0 != _shaderId) {
        glDeleteShader(_shaderId);
        _shaderId = 0;
        _compiled = false;
    }
    
    _shaderLog.clear();
}

bool MyShader::loadFromFile(const std::string &filepath) {
    std::string source;
    MyFileUtil *sharedFileUtil = MyFileUtil::sharedFileUtil();
    
    if(!sharedFileUtil->readFile(filepath, source)) {
        return false;
    }
    
    _filepath = filepath;
    return loadFromSource(source);
}

bool MyShader::loadFromSource(const std::string &source) {
    GLuint shaderId = glCreateShader(_shaderType);
    
    if(0 == shaderId) {
        return MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrShaderCreatingFailed);
    }
    
    const GLchar *sourceArr[1] = {source.c_str()};
    glShaderSource(shaderId, 1, sourceArr, nullptr);
    glCompileShader(shaderId);
    
    GLint status;
    
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
    if(!status) {
        GLint logLen;
        
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLen);
        if(logLen > 0) {
            char *log = new char[logLen + 1];
            
            GLsizei written(0);
            glGetShaderInfoLog(shaderId, logLen, &written, log);
            log[logLen] = '\0';
            
            _shaderLog = log;
            delete[] log;
        }
        
        return MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrShaderCompilingFailed);
    }
    
    deleteShader();
    _shaderId = shaderId;
    _compiled = true;
    
    return true;
}

MINE_NAMESPACE_END
