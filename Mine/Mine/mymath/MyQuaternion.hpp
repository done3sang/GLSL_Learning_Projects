//
//  MyQuaternion.hpp
//  Mine
//
//  Created by xy on 01/03/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MyQuaternion_hpp
#define MyQuaternion_hpp

#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyQuaternion final {
public:
    MyQuaternion(void);
    MyQuaternion(float inW, float inX, float inY, float inZ);
    MyQuaternion(const MyFVector4 &other);
    MyQuaternion(const MyFVector4 &&other);
    ~MyQuaternion(void);
    
    MyQuaternion& operator=(const MyQuaternion &other);
    MyQuaternion& operator=(const MyQuaternion &&other);
    
    bool operator==(const MyQuaternion &other) const;
    bool operator!=(const MyQuaternion &other) const;
    
public:
    float w;
    float x;
    float y;
    float z;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#include "MyQuaternion.inl"

#endif /* Quaternion_hpp */
