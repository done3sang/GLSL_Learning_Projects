//
//  MyShader.cpp
//  MyGLSL
//
//  Created by xy on 28/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyShader.hpp"
#include "MyFileUtil.hpp"
#include "MyErrorDesc.hpp"

MINE_NAMESPACE_BEGIN

MyShader::MyShader(int shaderType):
_shaderId(0),
_shaderType(shaderType),
_compiled(false) {}

MyShader::MyShader(int shaderType, const std::string &filepath):
_shaderId(0),
_shaderType(shaderType),
_compiled(false) {
    loadFromFile(filepath);
}

MyShader::~MyShader(void) {
    deleteShader();
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

int MyShader::loadFromFile(const std::string &filepath) {
    std::string source;
    MyFileUtil &sharedFileUtil = MyFileUtil::sharedFileUtil();
    int errCode = sharedFileUtil.readFile(filepath, source);
    
    if(!MyErrorDesc::successed(errCode)) {
        return errCode;
    }
    
    _filepath = filepath;
    return loadFromSource(source);
}

int MyShader::loadFromSource(const std::string &source) {
    GLuint shaderId = glCreateShader(_shaderType);
    
    if(0 == shaderId) {
        return MyErrorDesc::kErrShaderCreatingFailed;
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
        
        return MyErrorDesc::kErrShaderCompilingFailed;
    }
    
    deleteShader();
    _shaderId = shaderId;
    _compiled = true;
    
    return MyErrorDesc::kErrOk;
}

MINE_NAMESPACE_END
