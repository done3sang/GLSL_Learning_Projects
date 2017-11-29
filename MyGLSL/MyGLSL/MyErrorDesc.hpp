//
//  MyErrorDesc.hpp
//  MyGLSL
//
//  Created by xy on 27/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyErrorDesc_hpp
#define MyErrorDesc_hpp

#include <map>
#include <string>
#include "Precompiled.h"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyErrorCallback;

class MyErrorDesc {
public:
    static MyErrorDesc* sharedErrorDesc(void);
    static void closeErrorDesc(void);

    static bool successed(int errCode);
    static int invokeErrorCode(int errCode);
    
public:
    static const int kErrOk = 0;
    static const int kErrFileNotExists = 1;
    static const int kErrShaderCreatingFailed = 2;
    static const int kErrShaderNotCompiled = 3;
    static const int kErrShaderCompilingFailed = 4;
    static const int kErrProgramAlreadyLinked = 5;
    static const int kErrProgramCreatingFailed = 6;
    static const int kErrProgramShaderNotAttached = 7;
    static const int kErrProgramNotIntialized = 8;
    static const int kErrProgramLinkingFailed = 9;
    static const int kErrProgramNotLinked = 10;
    static const int kErrProgramShaderAlreadyAttached = 11;
    static const int kErrProgramUniformNotExists = 12;
    
public:
    std::string& errorString(int errCode);
    
    const MyErrorCallback* errorCallback(MyErrorCallback &errCallback) {
        const MyErrorCallback *prev = _errCallback;
        _errCallback = &errCallback;
        
        return prev;
    }
    
    int invokeError(int errCode);
    
private:
    static MyErrorDesc *_sharedErrorDesc;
    
    std::map<int, std::string> _errorDesc;
    MyErrorCallback *_errCallback;
    
    void initialize(void);
    
    MyErrorDesc(void);
    ~MyErrorDesc(void) {}
    MyErrorDesc(const MyErrorDesc&);
    MyErrorDesc& operator=(const MyErrorDesc&);
};

class MyErrorCallback {
public:
    MyErrorCallback(void) {}
    virtual ~MyErrorCallback(void) {}
    
    virtual void disposeError(int errCode, const std::string &errDesc) = 0;
};

MINE_NAMESPACE_END

#endif /* MyErrorDesc_hpp */
