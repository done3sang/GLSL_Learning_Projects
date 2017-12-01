//
//  MyAutoreleasePool.hpp
//  MyGLSL
//
//  Created by xy on 01/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyAutoreleasePool_hpp
#define MyAutoreleasePool_hpp

#include <vector>
#include "Precompiled.h"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyRef;
class MySingleton;

class MyAutoreleasePool: public MySingleton {
public:
    static MyAutoreleasePool* sharedAutoreleasePool(void);
    static void deleteAutoreleasePool(void);
    
    void addObject(MyRef *object);
    bool contains(const MyRef *object) const;
    void clear(void);
    
private:
    ~MyAutoreleasePool(void) { clear(); }
    
    std::vector<MyRef*> _objectArray;
    
    static MyAutoreleasePool *_sharedAutorelasePool;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyAutoreleasePool_hpp */
