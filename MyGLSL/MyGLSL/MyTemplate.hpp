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
    MySingleton(void) {}
    virtual ~MySingleton(void) {}
    
private:
    MySingleton(const MySingleton&);
    MySingleton& operator=(const MySingleton&);
};

class MyUnique {
protected:
    MyUnique(void) {}
    virtual ~MyUnique(void) {}
    
private:
    MyUnique(const MyUnique&);
    MyUnique& operator=(const MyUnique&);
};

class MyStatic {
private:
    MyStatic(void);
    MyStatic(const MyStatic&);
    ~MyStatic(void);
    
    MyStatic& operator=(const MyStatic);
};

class MySingletonRef: public MyRef {
protected:
    MySingletonRef(void) {}
    virtual ~MySingletonRef(void) {}
    
    void addRef(void) { MyRef::addRef(); }
    void retain(void) { MyRef::retain(); }
    
private:
    MySingletonRef(const MySingleton&);
    MySingletonRef& operator=(const MySingleton&);
};

class MyUniqueRef: public MyRef {
protected:
    MyUniqueRef(void) {}
    virtual ~MyUniqueRef(void) {}
    
private:
    MyUniqueRef(const MyUnique&);
    MyUniqueRef& operator=(const MyUnique&);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MySingleton_hpp */
