//
//  MySingleton.hpp
//  MyGLSL
//
//  Created by xy on 29/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MySingleton_hpp
#define MySingleton_hpp

#include "Precompiled.h"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MySingleton {
protected:
    MySingleton(void) {}
    ~MySingleton(void) {}
    
private:
    MySingleton(const MySingleton&);
    MySingleton& operator=(const MySingleton&);
};

class MyUnique {
protected:
    MyUnique(void) {}
    ~MyUnique(void) {}
    
private:
    MyUnique(const MyUnique&);
    MyUnique& operator=(const MyUnique&);
};

MINE_NAMESPACE_END

#endif /* MySingleton_hpp */
