//
//  MyErrorDesc.cpp
//  MyGLSL
//
//  Created by xy on 27/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyRef.hpp"
#include "MyErrorDesc.hpp"

MINE_NAMESPACE_BEGIN

MyErrorDesc* MyErrorDesc::_sharedErrorDesc = nullptr;

const int MyErrorDesc::kErrOk = 0;
const int MyErrorDesc::kErrFileNotExists = 1;
const int MyErrorDesc::kErrShaderCreatingFailed = 2;
const int MyErrorDesc::kErrShaderNotCompiled = 3;
const int MyErrorDesc::kErrShaderCompilingFailed = 4;
const int MyErrorDesc::kErrProgramAlreadyLinked = 5;
const int MyErrorDesc::kErrProgramCreatingFailed = 6;
const int MyErrorDesc::kErrProgramShaderNotAttached = 7;
const int MyErrorDesc::kErrProgramNotIntialized = 8;
const int MyErrorDesc::kErrProgramLinkingFailed = 9;
const int MyErrorDesc::kErrProgramNotLinked = 10;
const int MyErrorDesc::kErrProgramShaderAlreadyAttached = 11;
const int MyErrorDesc::kErrProgramUniformNotExists = 12;

MyErrorDesc* MyErrorDesc::sharedErrorDesc(void) {
    if(nullptr == _sharedErrorDesc) {
        _sharedErrorDesc = new MyErrorDesc;
    }
    
    return _sharedErrorDesc;
}

void MyErrorDesc::closeErrorDesc(void) {
    if(_sharedErrorDesc) {
        delete _sharedErrorDesc;
        _sharedErrorDesc = nullptr;
    }
}

bool MyErrorDesc::successed(int errCode) {
    return kErrOk == errCode;
}

int MyErrorDesc::invokeErrorCode(int errCode) {
    return sharedErrorDesc()->invokeError(errCode);
}

MyErrorDesc::MyErrorDesc(void): _errCallback(nullptr) {
    initialize();
}

void MyErrorDesc::initialize(void) {
    _errorDesc[kErrOk] = "Successed";
    _errorDesc[kErrFileNotExists] = "File NOT exists";
    _errorDesc[kErrShaderCreatingFailed] = "Shader creating failed";
    _errorDesc[kErrShaderNotCompiled] = "Shader NOT compiled";
    _errorDesc[kErrShaderCompilingFailed] = "Shader compling failed";
    _errorDesc[kErrProgramAlreadyLinked] = "Program already linked";
    _errorDesc[kErrProgramCreatingFailed] = "Program NOT created";
    _errorDesc[kErrProgramShaderNotAttached] = "Shader NOT attached to program";
    _errorDesc[kErrProgramNotIntialized] = "Program NOT initialized";
    _errorDesc[kErrProgramLinkingFailed] = "Program linking failed";
    _errorDesc[kErrProgramNotLinked] = "Program NOT linked";
    _errorDesc[kErrProgramShaderAlreadyAttached] = "Shader already attached to program";
}

std::string& MyErrorDesc::errorString(int errCode) {
    return _errorDesc[errCode];
}

int MyErrorDesc::invokeError(int errCode) {
    if(_errCallback && !successed(errCode)) {
        _errCallback->disposeError(errCode, errorString(errCode));
    }
    
    return errCode;
}

MINE_NAMESPACE_END
