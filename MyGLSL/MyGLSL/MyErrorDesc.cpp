//
//  MyErrorDesc.cpp
//  MyGLSL
//
//  Created by xy on 27/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyErrorDesc.hpp"

MINE_NAMESPACE_BEGIN

MyErrorDesc* MyErrorDesc::_sharedErrorDesc = nullptr;

MyErrorDesc& MyErrorDesc::sharedErrorDesc(void) {
    if(nullptr == _sharedErrorDesc) {
        _sharedErrorDesc = new MyErrorDesc;
    }
    
    return *_sharedErrorDesc;
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

MyErrorDesc::MyErrorDesc(void) {
    initialize();
}

void MyErrorDesc::initialize(void) {
    _errorDesc[kErrOk] = "Successed";
    _errorDesc[kErrFileNotExists] = "File NOT exists";
    _errorDesc[kErrShaderCreatingFailed] = "Shader creating failed";
}

std::string& MyErrorDesc::errorString(int errCode) {
    return _errorDesc[errCode];
}

int MyErrorDesc::invokeError(int errCode) {
    if(_errCallback) {
        _errCallback->disposeError(errCode, errorString(errCode));
    }
    
    return errCode;
}

MINE_NAMESPACE_END
