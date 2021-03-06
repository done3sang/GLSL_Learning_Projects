//
//  MyShader.cpp
//  MyGLSL
//
//  Created by xy on 28/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifdef DEBUG
#include <iostream>
#endif

#include "MyObject.hpp"
#include "MyShader.hpp"
#include "MyArray.hpp"
#include "MyData.hpp"
#include "MyFileManager.hpp"
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

MyShader* MyShader::shaderWithType(const std::string &shaderName,
                                         int shaderType) {
    MyShader *shader = new MyShader(shaderName, shaderType);
    shader->objectName(shaderName);
    return shader;
}

MyShader* MyShader::shaderWithContentsOfFile(const std::string &shaderName,
                                             int shaderType,
                                             const std::string &filepath) {
    MyShader *shader = new MyShader(shaderName, shaderType);
    shader->objectName(shaderName);
    
    return shader->loadFromFile(filepath) ? shader : nullptr;
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
    MyData<char>* filedata = MyFileManager::sharedFileManager()->loadFile(filepath.c_str());
    
    if(nullptr == filedata) {
        return false;
    }
    
    _filepath = filepath;
    return loadFromSource(filedata->raw());
}

bool MyShader::loadFromSource(const char *source) {
    GLuint shaderId = glCreateShader(_shaderType);
    
    if(0 == shaderId) {
        return MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrShaderCreatingFailed);
    }
    
    const GLchar *sourceArr[] = {source};
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
            
#ifdef DEBUG
            std::cout << "ERROR: Shader compilation failed = " << _shaderLog << "\n";
#endif
        }
        
        return MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrShaderCompilingFailed);
    }
    
    deleteShader();
    _shaderId = shaderId;
    _compiled = true;
    
    return true;
}

MINE_NAMESPACE_END
