//
//  MyProgram.cpp
//  MyGLSL
//
//  Created by xy on 28/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyProgram.hpp"
#include "MyShader.hpp"
#include "MyErrorDesc.hpp"

MINE_NAMESPACE_BEGIN

MyProgram* MyProgram::_runningProgram = nullptr;

MyProgram::MyProgram(void):
_programId(0),
_linked(false) {}

MyProgram::~MyProgram(void) {
    deleteProgram();
}

bool MyProgram::shaderAttached(const Mine::MyShader &shader) const {
    for(auto iter: _shaderVec) {
        if(shader == *iter) {
            return true;
        }
    }
    
    return false;
}

int MyProgram::attachShader(const Mine::MyShader &shader) {
    if(linked()) {
        return MyErrorDesc::kErrProgramLinked;
    }
    
    if(!valid()) {
        _programId = glCreateProgram();
        if(0 == _programId) {
            return MyErrorDesc::kErrProgramNotCreated;
        }
    }
    
    if(!shader.compiled()) {
        return MyErrorDesc::kErrShaderNotCompiled;
    }
    
    if(shaderAttached(shader)) {
        return MyErrorDesc::kErrProgramShaderAlreadyAttached;
    }
    
    glAttachShader(_programId, shader.shaderId());
    _shaderVec.push_back(&shader);
    
    return MyErrorDesc::kErrOk;
}

int MyProgram::detachShader(const Mine::MyShader &shader) {
    for(auto iter = _shaderVec.begin(); iter != _shaderVec.end(); ++iter) {
        if(shader == **iter) {
            glDetachShader(_programId, shader.shaderId());
            _shaderVec.erase(iter);
            
            return MyErrorDesc::kErrOk;
        }
    }
    
    return MyErrorDesc::kErrProgramShaderNotAttached;
}

int MyProgram::linkPorgram(void) {
    if(!valid()) {
        return MyErrorDesc::kErrProgramNotIntialized;
    }
    
    glLinkProgram(_programId);
    
    GLint status;
    glGetProgramiv(_programId, GL_LINK_STATUS, &status);
    if(!status) {
        GLint loglen(0);
        glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &loglen);
        
        if (loglen > 0) {
            char *log = new char[loglen + 1];
            
            GLsizei written(0);
            glGetProgramInfoLog(_programId, loglen, &written, log);
            log[loglen] = '\0';
            
            _programLog = log;
            delete[] log;
        }
        
        return MyErrorDesc::kErrProgramLinkingFailed;
    }
    
    _programLog.clear();
    return MyErrorDesc::kErrOk;
}

MyProgram* MyProgram::runningProgram(void) {
    return _runningProgram;
}

int MyProgram::useProgram(void) {
    if(!linked()) {
        return MyErrorDesc::kErrProgramNotLinked;
    }
    if(_runningProgram && operator==(*_runningProgram)) {
        return MyErrorDesc::kErrOk;
    }
    
    glUseProgram(_programId);
    _runningProgram = this;
    return MyErrorDesc::kErrOk;
}

void MyProgram::deleteProgram(void) {
    if(!valid()) {
        return;
    }
    
    if(_runningProgram && operator==(*_runningProgram)) {
        _runningProgram = nullptr;
    }
    
    glDeleteProgram(_programId);
    _programId = 0;
}

bool MyProgram::validate(void) const {
    return glIsProgram(_programId);
}

MINE_NAMESPACE_END
