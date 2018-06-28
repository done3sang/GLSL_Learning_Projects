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
    FORCEINLINE MySingleton(void) {}
    FORCEINLINE virtual ~MySingleton(void) {}
};

class MyUnique {
public:
    MyUnique(const MyUnique&) = delete;
    MyUnique(MyUnique&&) = delete;
    MyUnique& operator=(const MyUnique&) = delete;
    MyUnique& operator=(MyUnique&&) = delete;
    
protected:
    FORCEINLINE MyUnique(void) {}
    FORCEINLINE virtual ~MyUnique(void) {}
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

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MySingleton_hpp */
