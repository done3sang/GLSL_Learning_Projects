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

#include <initializer_list>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

template<int R, int C, class V = float>
class MyMatrix final {
public:
    static_assert(R > 0 && C > 0, "ERROR: MyMatrix, row or column below 0");
    
    typedef int size_type;
    typedef V value_type;
    
    template<class T = value_type>
    MyMatrix(const T &value = T());
    template<class T>
    MyMatrix(const MyMatrix<R, C, T> &other);
    template<class T>
    MyMatrix(const MyMatrix<R, C, T> &&other);
    template<class T>
    MyMatrix(const std::initializer_list<T> &il);
    ~MyMatrix(void) {}
    
    template<class T>
    MyMatrix& operator=(const MyMatrix<R, C, T> &other);
    template<class T>
    MyMatrix& operator=(const MyMatrix<R, C, T> &&other);
    template<class T>
    MyMatrix& operator=(const std::initializer_list<T> &il);
    
    template<class T>
    MyMatrix& operator+=(const MyMatrix<R, C, T> &other);
    template<class T>
    MyMatrix& operator-=(const MyMatrix<R, C, T> &other);
    template<class T>
    MyMatrix& operator*=(const T &value);
    
    bool squared(void) const { return false; }
    int row(void) const { return _row; }
    int column(void) const { return _column; }
    int size(void) const { return _row * _column; }
    
    value_type& valueAt(int r, int c) {
#ifdef DEBUG
        assert(r >= 0 && r < _row && "valueAt error, row overflow");
        assert(c >= 0 && c < _column && "valueAt error, column overflow");
#endif
        return _mat[r][c];
    }
    const value_type& valueAt(int r, int c) const {
#ifdef DEBUG
        assert(r >= 0 && r < _row && "valueAt error, row overflow");
        assert(c >= 0 && c < _column && "valueAt error, column overflow");
#endif
        return _mat[r][c];
    }
    
    bool zeroAt(int r, int c) const {
#ifdef DEBUG
        assert(r >= 0 && r < _row && "valueAt error, row overflow");
        assert(c >= 0 && c < _column && "valueAt error, column overflow");
#endif
        return zeroValue() == _mat[r][c];
    }
    bool identityAt(int r, int c) const {
#ifdef DEBUG
        assert(r >= 0 && r < _row && "valueAt error, row overflow");
        assert(c >= 0 && c < _column && "valueAt error, column overflow");
#endif
        return identityValue() == _mat[r][c];
    }
    
    static const value_type& zeroValue(void) { return _zeroValue; }
    static void zeroValue(const value_type &val) { _zeroValue = val; }
    
    static const value_type& identityValue(void) { return _identityValue; }
    static void identityValue(const value_type &val) { _identityValue = val; }
    
private:
    int _row;
    int _column;
    value_type _mat[R][C];
    
    static value_type _zeroValue;
    static value_type _identityValue;
};

template<int D, class V>
class MyMatrix<D, D, V> final {
public:
    static_assert(D > 0, "ERROR: MyMatrix, row or column below 0");
    
    typedef int size_type;
    typedef V value_type;
    
    template<class T = value_type>
    MyMatrix(const T &value = T());
    template<class T>
    MyMatrix(const MyMatrix<D, D, T> &other);
    template<class T>
    MyMatrix(const MyMatrix<D, D, T> &&other);
    template<class T>
    MyMatrix(const std::initializer_list<T> &il);
    ~MyMatrix(void) {}
    
    template<class T>
    MyMatrix& operator=(const MyMatrix<D, D, T> &other);
    template<class T>
    MyMatrix& operator=(const MyMatrix<D, D, T> &&);
    template<class T>
    MyMatrix& operator=(const std::initializer_list<T> &il);
    
    template<class T>
    MyMatrix& operator+=(const MyMatrix<D, D, T> &other);
    template<class T>
    MyMatrix& operator-=(const MyMatrix<D, D, T> &other);
    template<class T>
    MyMatrix& operator*=(const T &value);
    
    bool squared(void) const { return true; }
    int row(void) const { return _dimension; }
    int column(void) const { return _dimension; }
    int dimension(void) const { return _dimension; }
    int size(void) const { return _dimension * _dimension; }
    
    value_type& valueAt(int r, int c) {
#ifdef DEBUG
        assert(r >= 0 && r < _dimension && "valueAt error, row overflow");
        assert(c >= 0 && c < _dimension && "valueAt error, column overflow");
#endif
        return _mat[r][c];
    }
    const value_type& valueAt(int r, int c) const {
#ifdef DEBUG
        assert(r >= 0 && r < _dimension && "valueAt error, row overflow");
        assert(c >= 0 && c < _dimension && "valueAt error, column overflow");
#endif
        return _mat[r][c];
    }
    
    bool zeroAt(int r, int c) const {
#ifdef DEBUG
        assert(r >= 0 && r < _dimension && "valueAt error, row overflow");
        assert(c >= 0 && c < _dimension && "valueAt error, column overflow");
#endif
        return zeroValue() == _mat[r][c];
    }
    bool identityAt(int r, int c) const {
#ifdef DEBUG
        assert(r >= 0 && r < _dimension && "valueAt error, row overflow");
        assert(c >= 0 && c < _dimension && "valueAt error, column overflow");
#endif
        return identityValue() == _mat[r][c];
    }
    
    static const value_type& zeroValue(void) { return _zeroValue; }
    static void zeroValue(const value_type &val) { _zeroValue = val; }
    
    static const value_type& identityValue(void) { return _identityValue; }
    static void identityValue(const value_type &val) { _identityValue = val; }
    
    // square matrix only
    value_type determinant(void) const;
    bool inversible(void) const { return value_type() != determinant(); }
    
private:
    int _dimension;
    value_type _mat[D][D];
    
    static value_type _zeroValue;
    static value_type _identityValue;
};

// ------------------------------- matrix operation ----------------------------------------- //

template<int R, int C, class V, class T>
MyMatrix<R, C, V> operator+(const MyMatrix<R, C, V> &mat1,
                                   const MyMatrix<R, C, T> &mat2);

template<int R, int C, class V, class T>
MyMatrix<R, C, V> operator-(const MyMatrix<R, C, V> &mat1,
                            const MyMatrix<R, C, T> &mat2);

template<int R, int C, class V, class T>
MyMatrix<R, C, V> operator*(const MyMatrix<R, C, V> &mat, const T &val);

template<int R, int C, class V, class T>
MyMatrix<R, C, V> operator*(const T &val, const MyMatrix<R, C, V> &mat);

template<int R, int C, int N, class V, class T>
MyMatrix<R, C, V> operator*(const MyMatrix<R, N, V> &mat1,
                            const MyMatrix<N, C, T> &mat2);

template<int R, int C, class V>
MyMatrix<R, C, V>&
zeroMatrix(MyMatrix<R, C, V> &mat, const V &zeroValue = V(0));

template<int D, class V>
MyMatrix<D, D, V>&
identityMatrix(MyMatrix<D, D, V> &mat,
               const V &identityValue = V(1),
               const V &zeroValue = V(0));

template<int R, int C, class V>
MyMatrix<R, C, V>
transposeMatrix(const MyMatrix<R, C, V> &mat);

template<int D, class V>
MyMatrix<D, D, V>&
transposeMatrix(MyMatrix<D, D, V> &mat);

// ------------------------------- matrix operation ----------------------------------------- //

// ------------------------------- elementary transformation  ----------------------------------------- //

template<int R, int C, class V>
MyMatrix<R, C, V>&
swapMatrixRow(MyMatrix<R, C, V> &mat, int a, int b);

template<int R, int C, class V, class T>
MyMatrix<R, C, V>&
multiplyMatrixRow(MyMatrix<R, C, V> &mat, int a, const T &multiple);

template<int R, int C, class V, class T>
MyMatrix<R, C, V>&
subtractMatrixRow(MyMatrix<R, C, V> &mat,  int a, int b, const T &multiple);

template<int R, int C, class V>
MyMatrix<R, C, V>&
swapMatrixColumn(MyMatrix<R, C, V> &mat, int a, int b);

template<int R, int C, class V, class T>
MyMatrix<R, C, V>&
multiplyMatrixColumn(MyMatrix<R, C, V> &mat, int a, const T &multiple);

template<int R, int C, class V, class T>
MyMatrix<R, C, V>&
subtractMatrixColumn(MyMatrix<R, C, V> &mat, int a, int b, const T &multiple);

// ------------------------------- elementary transformation  ----------------------------------------- //

// simplified by subtractMatrixRow
template<int R, int C, class V>
MyMatrix<R, C, V>& simplifyMatrix(MyMatrix<R, C, V> &mat);

template<int D, class V>
MyMatrix<D, D, V>& inverseMatrix(MyMatrix<D, D, V> &mat);

MINE_NAMESPACE_END

#pragma GCC visibility pop

#include "MyMatrix.inl"

#endif /* MyMatrix_hpp */
