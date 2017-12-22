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
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MySingletonRef;
class MyUniqueRef;
class MyErrorCallback;

class MyErrorDesc final: public MySingletonRef {
public:
    static MyErrorDesc* sharedErrorDesc(void);
    static void closeErrorDesc(void);
    
    static bool successed(int errCode);
    static int invokeErrorCode(int errCode);
    static bool invokeErrorFailed(int errCode);
    
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
    static const int kErrXMLParseFailed;
    
public:
    std::string& errorString(int errCode);
    
    MyErrorCallback* errorCallback(void) const { return _errCallback; }
    void errorCallback(MyErrorCallback *errCallback);
    
    int invokeError(int errCode);
    
private:
    static MyErrorDesc *_sharedErrorDesc;
    
    std::map<int, std::string> _errorDesc;
    MyErrorCallback *_errCallback;
    
    void initialize(void);
    void destroy(void);
    
    MyErrorDesc(void);
    ~MyErrorDesc(void) { destroy(); }
    
    MyErrorDesc(const MyErrorDesc&);
    MyErrorDesc& operator=(const MyErrorDesc&);
};

class MyErrorCallback: public MyUniqueRef {
public:
    static MyErrorCallback* create(void) { return nullptr;}
    
    virtual void disposeError(int errCode, const std::string &errDesc) = 0;
    
protected:
    MyErrorCallback(void) {}
    virtual ~MyErrorCallback(void) {}
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyErrorDesc_hpp */
