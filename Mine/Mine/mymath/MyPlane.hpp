//
//  MyPlane.hpp
//  Mine
//
//  Created by xy on 27/02/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MyPlane_hpp
#define MyPlane_hpp

#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyFVector3;

class MyPlane {
public:
    MyPlane(void);
    MyPlane(const MyFVector3 &norm, float dist);
    MyPlane(const MyPlane &other);
    MyPlane(const MyPlane &&other);
    ~MyPlane(void);
    
    MyPlane& operator=(const MyPlane &other);
    MyPlane& operator=(const MyPlane &&other);
    
    bool operator==(const MyPlane &other) const;
    bool operator!=(const MyPlane &other) const;
    
    const MyFVector3& normal(void) const;
    void normal(const MyFVector3 &norm);
    
    float distance(void) const;
    void distance(float dist);
    
    // 0 on, -1 inside, 1 outside
    int pointOnPlane(const MyFVector3 &vec) const;
    
    void closestPointOnPlane(const MyFVector3 &inVec, MyFVector3 &outVec) const;
    
private:
    MyFVector3 _normal;
    float _distance;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#include "MyPlane.inl"

#endif /* MyPlane_hpp */
