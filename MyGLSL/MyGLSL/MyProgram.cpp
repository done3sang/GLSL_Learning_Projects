//
//  MyProgram.cpp
//  MyGLSL
//
//  Created by xy on 28/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "MyRef.hpp"
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

MyProgram* MyProgram::create(void) {
    return new MyProgram;
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
        return MyErrorDesc::kErrProgramAlreadyLinked;
    }
    
    if(!valid()) {
        _programId = glCreateProgram();
        if(0 == _programId) {
            return MyErrorDesc::kErrProgramCreatingFailed;
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
    
    glBindAttribLocation(_programId, kAttribPosition, "vertexPosition");
    glBindAttribLocation(_programId, kAttribColor, "vertexColor");
    glBindAttribLocation(_programId, kAttribTexCoord0, "vertexTexCoord0");
    glBindAttribLocation(_programId, kAttribNormal, "vertexNormal");
    glBindAttribLocation(_programId, kAttribTangent, "vertexTangent");
    
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
    
    _linked = true;
    _programLog.clear();
    return MyErrorDesc::kErrOk;
}

MyProgram* MyProgram::runningProgram(void) {
    return _runningProgram;
}

int MyProgram::useProgram(void) {
    if(!linked()) {
        return MyErrorDesc::invokeErrorCode(MyErrorDesc::kErrProgramNotLinked);
    }
    if(_runningProgram && operator==(*_runningProgram)) {
        return MyErrorDesc::invokeErrorCode(MyErrorDesc::kErrOk);
    }
    
    glUseProgram(_programId);
    _runningProgram = this;
    return MyErrorDesc::invokeErrorCode(MyErrorDesc::kErrOk);
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

int MyProgram::bindAttribLocation(GLuint location, const std::string &name) const {
    if(!valid()) {
        return MyErrorDesc::invokeErrorCode(MyErrorDesc::kErrProgramNotIntialized);
    }
    
    glBindAttribLocation(_programId, location, name.c_str());
    
    return MyErrorDesc::kErrOk;
}

int MyProgram::uniformLocation(const std::string &name) {
    auto iter = _uniformLocation.find(name);
    int location(-1);
    
    if(_uniformLocation.end() == iter) {
        if(!linked()) {
            MyErrorDesc::invokeErrorCode(MyErrorDesc::kErrProgramNotLinked);
            return location;
        }
        
        location = glGetUniformLocation(_programId, name.c_str());
        
        if(location < 0) {
            MyErrorDesc::invokeErrorCode(MyErrorDesc::kErrProgramUniformNotExists);
            return location;
        }
        
        _uniformLocation[name] = location;
    } else {
        location = iter->second;
    }
    
    return location;
}

int MyProgram::uniformMatrix4(const std::string &name, const glm::mat4 &mat) {
    int location(uniformLocation(name));
    
    if(location < 0) {
        return MyErrorDesc::invokeErrorCode(MyErrorDesc::kErrProgramUniformNotExists);
    }
    
    glUniformMatrix4fv(_uniformLocation[name], 1, GL_FALSE, glm::value_ptr(mat));
    return MyErrorDesc::kErrOk;
}

int MyProgram::uniformFloat(const std::string &name, float value) {
    int location(uniformLocation(name));
    
    if(location < 0) {
        return MyErrorDesc::invokeErrorCode(MyErrorDesc::kErrProgramUniformNotExists);
    }
    
    glUniform1f(location, value);
    return MyErrorDesc::kErrOk;
}

int MyProgram::uniformInteger(const std::string &name, int value) {
    int location(uniformLocation(name));
    
    if(location < 0) {
        return MyErrorDesc::invokeErrorCode(MyErrorDesc::kErrProgramUniformNotExists);
    }
    
    glUniform1i(location, value);
    return MyErrorDesc::kErrOk;
}

MINE_NAMESPACE_END
