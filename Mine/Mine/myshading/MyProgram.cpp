//
//  MyProgram.cpp
//  MyGLSL
//
//  Created by xy on 28/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <cassert>
#include "MyTemplate.hpp"
#include "MyBufferObject.hpp"
#include "MyProgram.hpp"
#include "MyShader.hpp"
#include "MyErrorDesc.hpp"
#include "MyVector.hpp"
#include "MyMatrix.hpp"

MINE_NAMESPACE_BEGIN

MyProgram* MyProgram::_runningProgram = nullptr;

MyProgram::MyProgram(const std::string &programName):
_programId(0),
_programName(programName),
_linked(false) {}

MyProgram::~MyProgram(void) {
    deleteProgram();
}

MyProgram* MyProgram::create(const std::string &programName) {
    MyProgram *prog = new MyProgram(programName);
    prog->objectName("MyProgram");
    
    return prog;
}

bool MyProgram::shaderAttached(const MyShader *shader) const {
    assert(shader && "MyProgram::shaderAttached = Shader should be non-null");
    
    for(auto iter: _shaderVec) {
        if(shader == iter) {
            return true;
        }
    }
    
    return false;
}

int MyProgram::attachShader(MyShader *shader) {
    assert(shader && "MyProgram::attachShader = Shader should be non-null");
    
    if(linked()) {
        return MyErrorDesc::kErrProgramAlreadyLinked;
    }
    
    if(!valid()) {
        _programId = glCreateProgram();
        if(0 == _programId) {
            return MyErrorDesc::kErrProgramCreatingFailed;
        }
    }
    
    if(!shader->compiled()) {
        return MyErrorDesc::kErrShaderNotCompiled;
    }
    
    if(shaderAttached(shader)) {
        return MyErrorDesc::kErrProgramShaderAlreadyAttached;
    }
    
    glAttachShader(_programId, shader->shaderId());
    shader->addRef();
    _shaderVec.push_back(shader);
    
    return MyErrorDesc::kErrOk;
}

int MyProgram::detachShader(MyShader *shader) {
    assert(shader && "MyProgram::detachShader = Shader should be non-null");
    
    for(auto iter = _shaderVec.begin(); iter != _shaderVec.end(); ++iter) {
        if(shader == *iter) {
            glDetachShader(_programId, shader->shaderId());
            _shaderVec.erase(iter);
            shader->release();
            
            return MyErrorDesc::kErrOk;
        }
    }
    
    return MyErrorDesc::kErrProgramShaderNotAttached;
}

void MyProgram::clearShader(void) {
    for(auto iter: _shaderVec) {
        glDetachShader(_programId, iter->shaderId());
        iter->release();
    }
    
    _shaderVec.clear();
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

void MyProgram::useProgram(void) {
    assert(linked() && "ERROR = MyProgram::useProgram, not linked");
    if(_runningProgram && operator==(*_runningProgram)) {
        return;
    }
    
    glUseProgram(_programId);
    _runningProgram = this;
}

void MyProgram::deleteProgram(void) {
    if(!valid()) {
        return;
    }
    
    if(_runningProgram && operator==(*_runningProgram)) {
        _runningProgram = nullptr;
    }
    
    clearShader();
    clearUniformBlock();
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

int MyProgram::uniformMatrix4(const std::string &name, const MyFMatrix4 &mat) {
    int location(uniformLocation(name));
    
    if(location < 0) {
        return MyErrorDesc::invokeErrorCode(MyErrorDesc::kErrProgramUniformNotExists);
    }
    
    glUniformMatrix4fv(location, 1, GL_FALSE, value_pointer(mat));
    return MyErrorDesc::kErrOk;
}

bool MyProgram::uniformVector3(const std::string &name, const MyFVector3 &vec) {
    int location(uniformLocation(name));
    
    if(location < 0) {
        return MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrProgramUniformNotExists);
    }
    
    glUniform3fv(location, 1, value_pointer(vec));
    return true;
}

bool MyProgram::uniformVector4(const std::string &name, const MyFVector4 &vec) {
    int location(uniformLocation(name));
    
    if(location < 0) {
        return MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrProgramUniformNotExists);
    }
    
    glUniform4fv(location, 1, value_pointer(vec));
    return true;
}

bool MyProgram::uniformBool(const std::string &name, bool value) {
    int location(uniformLocation(name));
    
    if(location < 0) {
        return MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrProgramUniformNotExists);
    }
    
    glUniform1i(location, value);
    return true;
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

int MyProgram::uniformBlockIndex(const std::string &blockName, const std::string &indexName, int valueSize, void *valueptr) {
    auto iter = _uniformLocation.find(blockName);
    int blockIndex(-1);
    
    if(_uniformLocation.end() == iter) {
        if(!linked()) {
            return MyErrorDesc::invokeErrorCode(MyErrorDesc::kErrProgramNotLinked);
        }
        
        blockIndex = glGetUniformBlockIndex(_programId, blockName.c_str());
        
        if(blockIndex < 0) {
            return MyErrorDesc::invokeErrorCode(MyErrorDesc::kErrProgramUniformNotExists);
        }
        
        _uniformLocation[blockName] = blockIndex;
    } else {
        blockIndex = iter->second;
    }
    
    auto bufferIter = _uniformBlock.find(blockIndex);
    MyBufferObject *blockBuffer = nullptr;
    if(_uniformBlock.end() == bufferIter) {
        blockBuffer = MyBufferObject::createWithBufferType(MyBufferObject::kBufferUniform);
        int blockSize(0);
        
        glGetActiveUniformBlockiv(_programId, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
        blockBuffer->bindBuffer();
        blockBuffer->bufferData(blockSize, nullptr, MyBufferObject::kBufferUsageDynamicDraw);
        
        useProgram();
        glBindBufferBase(MyBufferObject::kBufferUniform, blockIndex, blockBuffer->bufferId());
        
        addUniformBlock(blockIndex, blockBuffer);
    } else {
        blockBuffer = bufferIter->second;
    }
    
    GLuint index;
    const GLchar *indexArr[] = {indexName.c_str()};
    glGetUniformIndices(_programId, 1, indexArr, &index);
    if(static_cast<int>(index) < 0 ) {
        return MyErrorDesc::invokeErrorCode(MyErrorDesc::kErrProgramUniformBlockIndexNotExists);
    }
    
    GLint offset;
    glGetActiveUniformsiv(_programId, 1, &index, GL_UNIFORM_OFFSET, &offset);
    blockBuffer->bufferSubData(offset, valueSize, valueptr);
    
    return MyErrorDesc::kErrOk;
}

void MyProgram::addUniformBlock(int blockIndex, MyBufferObject *blockBuffer) {
    assert(blockBuffer && _uniformBlock.end() == _uniformBlock.find(blockIndex));
    _uniformBlock[blockIndex] = blockBuffer;
    blockBuffer->addRef();
}

void MyProgram::clearUniformBlock(void) {
    for(auto &iter: _uniformBlock) {
        iter.second->release();
    }
    _uniformBlock.clear();
}

std::string MyProgram::activeUniform(void) const {
    std::string uniformStr;
    
    if(!linked()) {
        return uniformStr;
    }
    
    GLint numUniform, maxLen;
    
    glGetUniformiv(_programId, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLen);
    glGetUniformiv(_programId, GL_ACTIVE_UNIFORMS, &numUniform);
    
    GLchar *name = new GLchar[maxLen];
    GLint size, location;
    GLsizei written;
    GLenum type;
    for(int i = 0; i < numUniform; ++i) {
        glGetActiveUniform(_programId, i, maxLen, &written, &size, &type, name);
        location = glGetUniformLocation(_programId, name);
        
        uniformStr += name;
        uniformStr += " ";
    }
    
    return uniformStr;
}
MINE_NAMESPACE_END
