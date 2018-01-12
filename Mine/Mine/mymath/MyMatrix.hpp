//
//  MyMatrix.hpp
//  Mine
//
//  Created by xy on 09/01/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MyMatrix_hpp
#define MyMatrix_hpp

#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

template<int numRow, int numColumn, class ValueType = float>
class MyMatrix final {
public:
    static_assert(numRow > 0 && numColumn > 0, "ERROR: MyMatrix, row or column below 0");
    
    typedef int size_type;
    typedef ValueType value_type;
    
    template<class OtherValueType = ValueType>
    MyMatrix(const OtherValueType &value = OtherValueType());
    template<class OtherValueType>
    MyMatrix(const MyMatrix<numRow, numColumn, OtherValueType> &other);
    template<class OtherValueType>
    MyMatrix(const MyMatrix<numRow, numColumn, OtherValueType> &&other);
    ~MyMatrix(void) {}
    
    template<class OtherValueType>
    MyMatrix& operator=(
                        const MyMatrix<numRow, numColumn, OtherValueType> &other);
    template<class OtherValueType>
    MyMatrix& operator=(
                        const MyMatrix<numRow, numColumn, OtherValueType> &&other);
    
    template<class OtherValueType>
    MyMatrix& operator+= (const MyMatrix<numRow, numColumn, OtherValueType> &other);
    template<class OtherValueType>
    MyMatrix& operator*=(const OtherValueType &value);
    
    bool squared(void) const { return false; }
    int row(void) const { return _row; }
    int column(void) const { return _column; }
    
    ValueType& valueAt(int r, int c) { return _mat[r][c]; }
    const ValueType& valueAt(int r, int c) const { return _mat[r][c]; }

private:
    int _row;
    int _column;
    ValueType _mat[numRow][numColumn];
};

template<int numDim, class ValueType>
class MyMatrix<numDim, numDim, ValueType> {
public:
    static_assert(numDim > 0, "ERROR: MyMatrix, row or column below 0");
    
    typedef int size_type;
    typedef ValueType value_type;
    
    template<class OtherValueType = ValueType>
    MyMatrix(const OtherValueType &value = OtherValueType());
    template<class OtherValueType>
    MyMatrix(const MyMatrix<numDim, numDim, OtherValueType> &other);
    template<class OtherValueType>
    MyMatrix(const MyMatrix<numDim, numDim, OtherValueType> &&other);
    ~MyMatrix(void) {}
    
    template<class OtherValueType>
    MyMatrix& operator=(const MyMatrix<numDim, numDim, OtherValueType> &other);
    template<class OtherValueType>
    MyMatrix& operator=(const MyMatrix<numDim, numDim, OtherValueType> &&);
    
    template<class OtherValueType>
    MyMatrix& operator+= (const MyMatrix<numDim, numDim, OtherValueType> &other);
    template<class OtherValueType>
    MyMatrix& operator*=(const OtherValueType &value);
    
    bool squared(void) const { return true; }
    int row(void) const { return _dimension; }
    int column(void) const { return _dimension; }
    int dimension(void) const { return _dimension; }
    
    ValueType& valueAt(int r, int c) { return _mat[r][c]; }
    const ValueType& valueAt(int r, int c) const { return _mat[r][c]; }
    
    // square matrix only
    MyMatrix& transpose(void);
    //template<class OtherValueType>
    //MyMatrix& operator*=(const MyMatrix<numDim, numDim, OtherValueType> &other);
    
private:
    int _dimension;
    ValueType _mat[numDim][numDim];
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#include "MyMatrix.inl"

#endif /* MyMatrix_hpp */
