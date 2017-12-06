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

class MyRef;
class MyErrorCallback;

class MyErrorDesc: public MyRef {
public:
    static MyErrorDesc* sharedErrorDesc(void);
    static void closeErrorDesc(void);

    static bool successed(int errCode);
    static int invokeErrorCode(int errCode);
    
public:
    static const int kErrOk;
    static const int kErrFileNotExists;
    static const int kErrShaderCreatingFailed;
    static const int kErrShaderNotCompiled;
    static const int kErrShaderCompilingFailed;
    static const int kErrProgramAlreadyLinked;
    static const int kErrProgramCreatingFailed;
    static const int kErrProgramShaderNotAttached;
    static const int kErrProgramNotIntialized;
    static const int kErrProgramLinkingFailed;
    static const int kErrProgramNotLinked;
    static const int kErrProgramShaderAlreadyAttached;
    static const int kErrProgramUniformNotExists;
    static const int kErrProgramUniformBlockIndexNotExists;
    
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

#pragma GCC visibility pop

#endif /* MyErrorDesc_hpp */
