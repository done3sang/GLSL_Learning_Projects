//
//  MySingleton.hpp
//  MyGLSL
//
//  Created by xy on 29/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MySingleton_hpp
#define MySingleton_hpp

#include "MyPrecompiled.hpp"
#include "MyRef.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MySingleton {
protected:
    MySingleton(void) = default;
    virtual ~MySingleton(void) = default;
    
private:
    MySingleton(const MySingleton&) = delete;
    MySingleton& operator=(const MySingleton&) = delete;
};

class MyUnique {
protected:
    MyUnique(void) = default;
    virtual ~MyUnique(void) = default;
    
private:
    MyUnique(const MyUnique&) = delete;
    MyUnique& operator=(const MyUnique&) = delete;
};

class MyStatic {
private:
    MyStatic(void) = delete;
    MyStatic(const MyStatic&) = delete;
    ~MyStatic(void) = delete;
    
    MyStatic& operator=(const MyStatic&) = delete;
};

class MySingletonRef: public MyRef {
protected:
    MySingletonRef(void) { MyRef::retain(); }
    virtual ~MySingletonRef(void) = default;
    
    void addRef(void) { MyRef::addRef(); }
    void retain(void) { MyRef::retain(); }
    
private:
    MySingletonRef(const MySingleton&) = delete;
    MySingletonRef& operator=(const MySingleton&) = delete;
};

class MyUniqueRef: public MyRef {
protected:
    MyUniqueRef(void) = default;
    virtual ~MyUniqueRef(void) = default;
    
private:
    MyUniqueRef(const MyUnique&) = delete;
    MyUniqueRef& operator=(const MyUnique&) = delete;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MySingleton_hpp */
