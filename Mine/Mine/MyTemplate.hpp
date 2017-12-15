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
public:
    MySingleton(const MySingleton&) = delete;
    MySingleton(MySingleton&&) = delete;
    MySingleton& operator=(const MySingleton&) = delete;
    MySingleton& operator=(MySingleton&&) = delete;
    
protected:
    MySingleton(void) {}
    virtual ~MySingleton(void) {}
};

class MyUnique {
public:
    MyUnique(const MyUnique&) = delete;
    MyUnique(MyUnique&&) = delete;
    MyUnique& operator=(const MyUnique&) = delete;
    MyUnique& operator=(MyUnique&&) = delete;
    
protected:
    MyUnique(void) {}
    virtual ~MyUnique(void) {}
};

class MyStatic {
public:
    MyStatic(void) = delete;
    MyStatic(const MyStatic&) = delete;
    MyStatic(MyStatic&&) = delete;
    ~MyStatic(void) = delete;
    
    MyStatic& operator=(const MyStatic&) = delete;
    MyStatic& operator=(MyStatic&&) = delete;
};

class MySingletonRef: public MyRef {
public:
    MySingletonRef(const MySingletonRef&) = delete;
    MySingletonRef(const MySingletonRef&&) = delete;
    MySingletonRef& operator=(const MySingletonRef&) = delete;
    MySingletonRef& operator=(MySingletonRef&&) = delete;
    
protected:
    MySingletonRef(void) { MyRef::retain(); }
    virtual ~MySingletonRef(void) {}
    
    void addRef(void) { MyRef::addRef(); }
    void retain(void) { MyRef::retain(); }
};

class MyUniqueRef: public MyRef {
public:
    MyUniqueRef(const MyUniqueRef&) = delete;
    MyUniqueRef(MyUniqueRef&&) = delete;
    MyUniqueRef& operator=(const MyUniqueRef&) = delete;
    
protected:
    MyUniqueRef(void) {}
    virtual ~MyUniqueRef(void) {}
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MySingleton_hpp */
