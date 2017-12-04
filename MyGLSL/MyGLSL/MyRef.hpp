//
//  MyRef.hpp
//  MyGLSL
//
//  Created by xy on 01/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyRef_hpp
#define MyRef_hpp

#include <string>
#include "Precompiled.h"

/* The c/Users/xy/Documents/OpenGLProjects/GLSL_Learning_Projects/MyGLSL/MyGLSLlasses below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyRef {
public:
    MyRef(void);
    MyRef(const MyRef&);
    virtual ~MyRef(void) {}
    
    MyRef& operator=(const MyRef &another) { return *this; }
    
    int refCount(void) const { return _refCount; }
    void retain(void) { ++_refCount; }
    
    const std::string& refName(void) const { return _refName; }
    void refName(const std::string& name) { _refName = name; }
    
    void release(void);
    void autorelase(void);
    
private:
    int _refCount;
    std::string _refName;
    
    friend class MyAutoreleasePool;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyRef_hpp */
