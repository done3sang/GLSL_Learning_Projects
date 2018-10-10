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
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

#define ASSIGN_OBJECT(dest, src) {\
if(dest) {\
    (dest)->release();\
}\
if(src) {\
    (src)->addRef();\
}\
dest = src;\
}

#define RETAIN_OBJECT(obj) {\
if(obj) {\
(obj)->addRef();\
}\
}

#define RELEASE_OBJECT(obj) {\
if(obj) {\
(obj)->release();\
obj = nullptr;\
}\
}

class MyObject {
public:
    MyObject(void);
    MyObject(const MyObject&);
    MyObject(const MyObject&&) = delete;
    FORCEINLINE virtual ~MyObject(void) {}
    
    MyObject& operator=(const MyObject&&) = delete;
    FORCEINLINE MyObject& operator=(const MyObject&) { return *this; }
    
    FORCEINLINE int refCount(void) const { return _refCount; }
    FORCEINLINE void addRef(void) { ++_refCount; }
    FORCEINLINE void retain(void) { ++_refCount; }
    
    FORCEINLINE const std::string& objectName(void) const { return _objectName; }
    FORCEINLINE void objectName(const std::string& name) { _objectName = name; }
    
    void release(void);
    void autorelease(void);
    
    // memory allocation
    void* operator new(size_t sz);
    void operator delete(void*);
    
private:
    int _refCount;
    std::string _objectName;
    
    friend class MyAutoreleasePool;
    friend class MyMemoryBlock;
    friend class MyMemoryManager;
};

class MySingletonObject: public MyObject {
public:
    MySingletonObject(const MySingletonObject&) = delete;
    MySingletonObject(const MySingletonObject&&) = delete;
    MySingletonObject& operator=(const MySingletonObject&) = delete;
    MySingletonObject& operator=(MySingletonObject&&) = delete;
    
    void* operator new(size_t sz);
    
protected:
    FORCEINLINE MySingletonObject(void) { retain(); }
    FORCEINLINE virtual ~MySingletonObject(void) {}
};

class MyUniqueObject: public MyObject {
public:
    MyUniqueObject(const MyUniqueObject&) = delete;
    MyUniqueObject(MyUniqueObject&&) = delete;
    MyUniqueObject& operator=(const MyUniqueObject&) = delete;
    
protected:
    FORCEINLINE MyUniqueObject(void) {}
    FORCEINLINE virtual ~MyUniqueObject(void) {}
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyRef_hpp */
