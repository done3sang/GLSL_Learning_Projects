//
//  MyLinearTransformation.hpp
//  Mine
//
//  Created by xy on 24/02/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MyLinearTransformation_hpp
#define MyLinearTransformation_hpp

#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyStatic;
class MyFMatrix2;
class MyFMatrix3;
class MyFMatrix4;

class MyLinearTransformation: private MyStatic {
public:
    template<class M>
    void swapMatrixRow(M &mat, int x, int y, int startIndex = 0);
    template<class M>
    void multiplyMatrixRow(M &mat, int x, float multiple, int startIndex = 0);
    template<class M>
    void substractMatrixRow(M &mat, int x, int y, float multiple, int startIndex = 0);
    
    template<class M>
    void swapMatrixColumn(M &mat, int x, int y, int startIndex = 0);
    template<class M>
    void multiplyMatrixColumn(M &mat, int x, float multiple, int startIndex = 0);
    template<class M>
    void substractMatrixColumn(M &mat, int x, int y, float multiple, int startIndex = 0);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#include "MyLinearTransformation.inl"

#endif /* MyLinearTransformation_hpp */
