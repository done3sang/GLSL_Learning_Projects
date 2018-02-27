//
//  MyCoordinate.hpp
//  Mine
//
//  Created by xy on 26/02/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MyCoordinate_hpp
#define MyCoordinate_hpp

#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyFVector3;
class MyFMatrix3;

/* for rotation only, excluding translation
    origin(0, 0, 0) all the same
 */
class MyCoordinate {
public:
    MyCoordinate(void);
    MyCoordinate(const MyFVector3 &inX,
                 const MyFVector3 &inY,
                 const MyFVector3 &inZ);
    MyCoordinate(const MyCoordinate &coord);
    MyCoordinate(const MyCoordinate &&coord);
    ~MyCoordinate(void);
    
    MyCoordinate& operator=(const MyCoordinate &other);
    MyCoordinate& operator=(const MyCoordinate &&other);
    
    bool operator==(const MyCoordinate &other);
    bool operator!=(const MyCoordinate &other);
    
    const MyFVector3& axisX(void) const;
    const MyFVector3& axisY(void) const;
    const MyFVector3& axisZ(void) const;
    const MyFMatrix3& coordinateMatrix(void) const;
    
    void assignCoordinate(const MyFVector3 &inX,
                          const MyFVector3 &inY,
                          const MyFVector3 &inZ);
    
    bool validate(void) const;
    
private:
    MyFVector3 _axisX;
    MyFVector3 _axisY;
    MyFVector3 _axisZ;
    MyFMatrix3 _coordinateMatrix;
};

class MyCoordinateTransition {
public:
    MyCoordinateTransition(void);
    MyCoordinateTransition(const MyCoordinate &coordA, const MyCoordinate &coordB);
    MyCoordinateTransition(const MyCoordinateTransition &other);
    MyCoordinateTransition(const MyCoordinateTransition &&other);
    ~MyCoordinateTransition(void);
    
    MyCoordinateTransition& operator=(const MyCoordinateTransition &other);
    MyCoordinateTransition& operator=(const MyCoordinateTransition &&other);
    
    bool operator==(const MyCoordinateTransition &other) const;
    bool operator!=(const MyCoordinateTransition &other) const;
    
    const MyFMatrix3& forwardMatrix(void) const;
    const MyFMatrix3& backwardMatrix(void) const;
    
    bool validate(void) const;
    
private:
    const MyCoordinate *_coordinateA;
    const MyCoordinate *_coordinateB;
    MyFMatrix3 _forwardMatrix; // B = A * P -> P = A ^ -1 * B
    MyFMatrix3 _backwardMatrix; // Q = transpose(P)
    
    void constructTransition(const MyCoordinate &coordA, const MyCoordinate &coordB);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#include "MyCoordinate.inl"

#endif /* MyCoordinate_hpp */
