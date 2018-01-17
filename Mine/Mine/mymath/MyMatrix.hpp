//
//  MyMatrix.hpp
//  Mine
//
//  Created by xy on 09/01/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MyMatrix_hpp
#define MyMatrix_hpp

#ifdef DEBUG
#include <cassert>
#endif

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
    int size(void) const { return _row * _column; }
    
    ValueType& valueAt(int r, int c) {
#ifdef DEBUG
        assert(r >= 0 && r < _row && "valueAt error, row overflow");
        assert(c >= 0 && c < _column && "valueAt error, column overflow");
#endif
        return _mat[r][c];
    }
    const ValueType& valueAt(int r, int c) const {
#ifdef DEBUG
        assert(r >= 0 && r < _row && "valueAt error, row overflow");
        assert(c >= 0 && c < _column && "valueAt error, column overflow");
#endif
        return _mat[r][c];
    }
    
private:
    int _row;
    int _column;
    ValueType _mat[numRow][numColumn];
};

template<int numDim, class ValueType>
class MyMatrix<numDim, numDim, ValueType> final {
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
    int size(void) const { return _dimension * _dimension; }
    
    ValueType& valueAt(int r, int c) {
#ifdef DEBUG
        assert(r >= 0 && r < _dimension && "valueAt error, row overflow");
        assert(c >= 0 && c < _dimension && "valueAt error, column overflow");
#endif
        return _mat[r][c];
    }
    const ValueType& valueAt(int r, int c) const {
#ifdef DEBUG
        assert(r >= 0 && r < _dimension && "valueAt error, row overflow");
        assert(c >= 0 && c < _dimension && "valueAt error, column overflow");
#endif
        return _mat[r][c];
    }
    
private:
    int _dimension;
    ValueType _mat[numDim][numDim];
};

// ------------------------------- matrix operation ----------------------------------------- //

template<int numRow, int numColumn, class ValueType>
MyMatrix<numColumn, numRow, ValueType>&
zeroMatrix(MyMatrix<numRow, numColumn, ValueType> &mat,
           const ValueType &zeroValue = ValueType(0));

template<int numDim, class ValueType>
MyMatrix<numDim, numDim, ValueType>&
identityMatrix(MyMatrix<numDim, numDim, ValueType> &mat,
               const ValueType &identityValue = ValueType(1),
               const ValueType &zeroValue = ValueType(0));

template<int numRow, int numColumn, class ValueType>
MyMatrix<numColumn, numRow, ValueType>
transposeMatrix(const MyMatrix<numRow, numColumn, ValueType> &mat);

template<int numDim, class ValueType>
MyMatrix<numDim, numDim, ValueType>&
transposeMatrix(MyMatrix<numDim, numDim, ValueType> &mat);

// ------------------------------- matrix operation ----------------------------------------- //

// ------------------------------- elementary transformation  ----------------------------------------- //

template<int numRow, int numColumn, class ValueType>
MyMatrix<numColumn, numRow, ValueType>&
swapMatrixRow(MyMatrix<numRow, numColumn, ValueType> &mat, int a, int b);

template<int numRow, int numColumn, class ValueType, class OtherValueType>
MyMatrix<numColumn, numRow, ValueType>&
multiplyMatrixRow(MyMatrix<numRow, numColumn, ValueType> &mat, int a, const OtherValueType &multiple);

template<int numRow, int numColumn, class ValueType, class OtherValueType>
MyMatrix<numColumn, numRow, ValueType>&
subtractMatrixRow(MyMatrix<numRow, numColumn, ValueType> &mat,  int a,
                  int b, const OtherValueType &multiple);

template<int numRow, int numColumn, class ValueType>
MyMatrix<numColumn, numRow, ValueType>&
swapMatrixColumn(MyMatrix<numRow, numColumn, ValueType> &mat, int a, int b);

template<int numRow, int numColumn, class ValueType, class OtherValueType>
MyMatrix<numColumn, numRow, ValueType>&
multiplyMatrixColumn(MyMatrix<numRow, numColumn, ValueType> &mat, int a, const OtherValueType &multiple);

template<int numRow, int numColumn, class ValueType, class OtherValueType>
MyMatrix<numColumn, numRow, ValueType>&
subtractMatrixColumn(MyMatrix<numRow, numColumn, ValueType> &mat, int a,
                  int b, const OtherValueType &multiple);

// ------------------------------- elementary transformation  ----------------------------------------- //

MINE_NAMESPACE_END

#pragma GCC visibility pop

#include "MyMatrix.inl"

#endif /* MyMatrix_hpp */
