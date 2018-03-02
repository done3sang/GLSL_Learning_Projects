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
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyObject;
class MySingleton;

class MyAutoreleasePool final: public MySingleton {
public:
    static MyAutoreleasePool* sharedAutoreleasePool(void);
    static void closeAutoreleasePool(void);
    
    void addObject(MyObject *object);
    bool contains(const MyObject *object) const;
    
    void clearPool(void);
    void purgePool(void);
    
private:
    ~MyAutoreleasePool(void) { purgePool(); }
    
    std::vector<MyObject*> _objectArray;
    
    static MyAutoreleasePool *_sharedAutorelasePool;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyAutoreleasePool_hpp */
