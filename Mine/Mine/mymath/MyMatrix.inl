//
//  MyMatrix.inl
//  Mine
//
//  Created by xy on 10/01/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

MINE_NAMESPACE_BEGIN

// matrix template meta
namespace {
    // matrix assign value
    template<class MatrixType, int R, int C, int N, int I, class ValueType>
    struct MatrixAssignValueImpl {
        enum {
            Continue = I != 0,
            NextR = I/N,
            NextC = I%N,
            NextI = I - 1
        };
        
        static inline void value(MatrixType &mat, ValueType val) {
            mat.valueAt(R, C) = val;
            MatrixAssignValueImpl<MatrixType, NextR * Continue, NextC * Continue, N * Continue, NextI * Continue, ValueType>::value(mat, val);
        }
    };
    
    template<class MatrixType, class ValueType>
    struct MatrixAssignValueImpl<MatrixType, 0, 0, 0, 0, ValueType> {
        static inline void value(MatrixType &mat, ValueType val) {
            
        }
    };
    
    template<int R, int C, class ValueType, class OtherValueType>
    inline void MatrixAssignValue(MyMatrix<R, C, ValueType> &mat, const OtherValueType & val) {
        MatrixAssignValueImpl<MyMatrix<R, C, ValueType>, 0, 0, C, R * C + 1, OtherValueType>::value(mat, val);
    }
    
    // matrix assign matrix
    template<class MatrixType1, class MatrixTyp2, int R, int C, int N, int I>
    struct MatrixAssignMatrixImpl {
        enum {
            Continue = I != 0,
            NextR = I/N,
            NextC = I%N,
            NextI = I - 1
        };
        
        static inline void value(MatrixType1 &mat, const MatrixTyp2 &other) {
            mat.valueAt(R, C) = other.valueAt(R, C);
            MatrixAssignMatrixImpl<MatrixType1, MatrixTyp2,
            NextR * Continue, NextC * Continue, N * Continue, NextI * Continue>::value(mat, other);
        }
    };
    
    template<class MatrixType1, class MatrixTyp2>
    struct MatrixAssignMatrixImpl<MatrixType1, MatrixTyp2, 0, 0, 0, 0> {
        static inline void value(MatrixType1 &mat, const MatrixTyp2 &other) {
            
        }
    };
    
    template<int R, int C, class ValueType, class OtherValueType>
    inline void MatrixAssignMatrix(MyMatrix<R, C, ValueType> &mat, const MyMatrix<R, C, OtherValueType> &other) {
        MatrixAssignMatrixImpl<MyMatrix<R, C, ValueType>, MyMatrix<R, C, OtherValueType>, 0, 0, C, R * C - 1>::value(mat, other);
    }
    
    // matrix add matrix
    template<class MatrixType1, class MatrixTyp2, int R, int C, int N, int I>
    struct MatrixAddMatrixImpl {
        enum {
            Continue = I != 0,
            NextR = I/N,
            NextC = I%N,
            NextI = I - 1
        };
        
        static inline void value(MatrixType1 &mat, const MatrixTyp2 &other) {
            mat.valueAt(R, C) += other.valueAt(R, C);
            MatrixAddMatrixImpl<MatrixType1, MatrixTyp2,
            NextR * Continue, NextC * Continue, N * Continue, NextI * Continue>::value(mat, other);
        }
    };
    
    template<class MatrixType1, class MatrixTyp2>
    struct MatrixAddMatrixImpl<MatrixType1, MatrixTyp2, 0, 0, 0, 0> {
        static inline void value(MatrixType1 &mat, const MatrixTyp2 &other) {
            
        }
    };
    
    template<int R, int C, class ValueType, class OtherValueType>
    inline void MatrixAddMatrix(MyMatrix<R, C, ValueType> &mat, const MyMatrix<R, C, OtherValueType> &other) {
        MatrixAddMatrixImpl<MyMatrix<R, C, ValueType>, MyMatrix<R, C, OtherValueType>, 0, 0, C, R * C - 1>::value(mat, other);
    }
    
    // matrix mutliple by value
    template<class MatrixType, class ValueType, int R, int C, int N, int I>
    struct MatrixMultiplyValueImpl {
        enum {
            Continue = I != 0,
            NextR = I/N,
            NextC = I%N,
            NextI = I - 1
        };
        
        static inline void value(MatrixType &mat, const ValueType &val) {
            mat.valueAt(R, C) *= val;
            MatrixMultiplyValueImpl<MatrixType, ValueType,
            NextR * Continue, NextC * Continue, N * Continue, NextI * Continue>::value(mat, val);
        }
    };
    
    template<class MatrixType, class ValueType>
    struct MatrixMultiplyValueImpl<MatrixType, ValueType, 0, 0, 0, 0> {
        static inline void value(MatrixType&, const ValueType&) {
            
        }
    };
    
    template<int R, int C, class ValueType, class OtherValueType>
    inline void MatrixMultiplyValue(MyMatrix<R, C, ValueType> &mat, const OtherValueType &val) {
        MatrixMultiplyValueImpl<MyMatrix<R, C, ValueType>, OtherValueType, 0, 0, C, R * C - 1>::value(mat, val);
    }
    
    // matrix transpose
    template<class MatrixType1, class MatrixTyp2, int R, int C, int N, int I>
    struct MatrixTransposeImpl {
        enum {
            Continue = I != 0,
            NextR = I/N,
            NextC = I%N,
            NextI = I - 1
        };
        
        static inline void value(MatrixType1 &retMat, const MatrixTyp2 &mat) {
            retMat.valueAt(R, C) = mat.valueAt(C, R);
            MatrixTransposeImpl<MatrixType1, MatrixTyp2,
            NextR * Continue, NextC * Continue, N * Continue, NextI * Continue>::value(mat, mat);
        }
    };
    
    template<class MatrixType1, class MatrixTyp2>
    struct MatrixTransposeImpl<MatrixType1, MatrixTyp2, 0, 0, 0, 0> {
        static inline void value(MatrixType1 &mat, const MatrixTyp2 &other) {
            
        }
    };
    
    template<int R, int C, class ValueType, class OtherValueType>
    inline void MatrixTranspose(MyMatrix<R, C, ValueType> &retMat, const MyMatrix<C, R, OtherValueType> &mat) {
        MatrixAddMatrixImpl<MyMatrix<R, C, ValueType>, MyMatrix<C, R, OtherValueType>, 0, 0, C, R * C - 1>::value(mat, mat);
    }
    
    // square matrix transpose
    template<class MatrixType, int R, int C, int N, int I>
    struct SquareMatrixTransposeImpl {
        enum {
            Continue = I != 0,
            NextR = I/N,
            NextC = I%N,
            NextI = I - 1
        };
        
        static inline void value(MatrixType &mat) {
            typename MatrixType::value_type tmp(mat.valueAt(R, C));
            mat.valueAt(R, C) = mat.valueAt(C, R);
            mat.valueAt(C, R) = tmp;
            SquareMatrixTransposeImpl<MatrixType,
            NextR * Continue, NextC * Continue, N * Continue, NextI * Continue>::value(mat);
        }
    };
    
    template<class MatrixType>
    struct SquareMatrixTransposeImpl<MatrixType, 0, 0, 0, 0> {
        static inline void value(MatrixType&) {
            
        }
    };
    
    template<int R, class ValueType>
    inline void SquareMatrixTranspose(MyMatrix<R, R, ValueType> &mat) {
        SquareMatrixTransposeImpl<MyMatrix<R, R, ValueType>, 0, 0, R, R * R - 1>::value(mat);
    }
    
    // matrix multiply matrix
    template<class MatrixType1, class MatrixType2, class MatrixType3, int R, int C, int M, int K>
    struct MatrixInnerMultiplyMatrixImpl {
        enum {
            Continue = M != K - 1,
            NextM = M + 1
        };
        
        static inline void value(MatrixType1 &retMat, const MatrixType2 &mat1, const MatrixType3 &mat2) {
            retMat.valueAt(R, C) += mat1.valueAt(R, M) * mat2.valueAt(M, C);
            MatrixInnerMultiplyMatrixImpl<MatrixType1, MatrixType2, MatrixType3,
            R * Continue, C * Continue, NextM * Continue,
            K * Continue>::value(retMat, mat1, mat2);
        }
    };
    
    template<class MatrixType1, class MatrixType2, class MatrixType3>
    struct MatrixInnerMultiplyMatrixImpl<MatrixType1, MatrixType2, MatrixType3, 0, 0, 0, 0> {
        static inline void value(MatrixType1 &retMat, const MatrixType2 &mat1, const MatrixType3 &mat2) {
            
        }
    };
    
    template<class MatrixType1, class MatrixType2, class MatrixType3, int R, int C, int N, int K, int I>
    struct MatrixMultiplyMatrixImpl {
        enum {
            Continue = I != 0,
            NextR = I/N,
            NextC = I%N,
            NextI = I - 1
        };
        
        static inline void value(MatrixType1 &retMat, const MatrixType2 &mat1, const MatrixType3 &mat2) {
            MatrixInnerMultiplyMatrixImpl<MatrixType1, MatrixType2, MatrixType3, R, C, 0, K>::value(retMat, mat1, mat2);
            
            MatrixMultiplyMatrixImpl<MatrixType1, MatrixType2, MatrixType3,
            NextR * Continue, NextC * Continue,
            N * Continue, K * Continue, NextI * Continue>::value(retMat, mat1, mat2);
        }
    };
    
    template<class MatrixType1, class MatrixTyp2, class MatrixTyp3>
    struct MatrixMultiplyMatrixImpl<MatrixType1, MatrixTyp2, MatrixTyp3, 0, 0, 0, 0, 0> {
        static inline void value(MatrixType1&, const MatrixTyp2&, const MatrixTyp3&) {
            
        }
    };
    
    template<int R, int K, int C, class RetValueType, class ValueType1, class ValueType2>
    inline void MatrixMultiplyMatrix(MyMatrix<R, C, RetValueType> &retMat,
                              const MyMatrix<R, K, ValueType1> &mat1,
                              const MyMatrix<K, C, ValueType2> &mat2) {
        MatrixAssignValue(retMat, RetValueType());
        MatrixMultiplyMatrixImpl<MyMatrix<R, C, RetValueType>, MyMatrix<R, K, ValueType1>, MyMatrix<K, C, ValueType2>,
        0, 0, C, K, R * C - 1>::value(retMat, mat1, mat2);
    }
}

template<int numRow, int numColumn, class ValueType>
template<class OtherValueType>
inline MyMatrix<numRow, numColumn, ValueType>::MyMatrix(const OtherValueType &value):
_row(numRow), _column(numColumn) {
#ifdef ENABLE_TEMPLATE_META
    MatrixAssignValue(*this, value);
#else
    for(int i = 0; i != _row; ++i) {
        for(int j = 0; j != _column; ++j) {
            _mat[i][j] = value;
        }
    }
#endif
}

template<int numRow, int numColumn, class ValueType>
template<class OtherValueType>
inline MyMatrix<numRow, numColumn, ValueType>::MyMatrix(const MyMatrix<numRow, numColumn, OtherValueType> &other):
_row(numRow), _column(numColumn) {
#ifdef ENABLE_TEMPLATE_META
    MatrixAssignMatrix(*this, other);
#else
    for(int i = 0; i != _row; ++i) {
        for(int j = 0; j != _column; ++j) {
            _mat[i][j] = other.valueAt(i, j);
        }
    }
#endif
}

template<int numRow, int numColumn, class ValueType>
template<class OtherValueType>
inline MyMatrix<numRow, numColumn, ValueType>::MyMatrix(const MyMatrix<numRow, numColumn, OtherValueType> &&other):
MyMatrix(other) {
}

template<int numRow, int numColumn, class ValueType>
template<class OtherValueType>
inline MyMatrix<numRow, numColumn, ValueType>&
MyMatrix<numRow, numColumn, ValueType>::operator=(const MyMatrix<numRow, numColumn, OtherValueType> &other) {
#ifdef ENABLE_TEMPLATE_META
    MatrixAssignMatrix(*this, other);
#else
    for(int i = 0; i != row(); ++i) {
        for(int j = 0; j != column(); ++j) {
            _mat[i][j] = other.valueAt(i, j);
        }
    }
#endif
    return *this;
}

template<int numRow, int numColumn, class ValueType>
template<class OtherValueType>
inline MyMatrix<numRow, numColumn, ValueType>&
MyMatrix<numRow, numColumn, ValueType>::operator=(const MyMatrix<numRow, numColumn, OtherValueType> &&other) {
#ifdef ENABLE_TEMPLATE_META
    MatrixAssignMatrix(*this, other);
#else
    for(int i = 0; i != row(); ++i) {
        for(int j = 0; j != column(); ++j) {
            _mat[i][j] = other.valueAt(i, j);
        }
    }
#endif
    return *this;
}

template<int numRow, int numColumn, class ValueType>
template<class OtherValueType>
inline MyMatrix<numRow, numColumn, ValueType>&
MyMatrix<numRow, numColumn, ValueType>::operator+=(const MyMatrix<numRow, numColumn, OtherValueType> &other) {
#ifdef ENABLE_TEMPLATE_META
    MatrixAddMatrix(*this, other);
#else
    for(int i = 0; i != row(); ++i) {
        for(int j = 0; j != column(); ++j) {
            _mat[i][j] += other.valueAt(i, j);
        }
    }
#endif
    return *this;
}

template<int numRow, int numColumn, class ValueType>
template<class OtherValueType>
inline MyMatrix<numRow, numColumn, ValueType>&
MyMatrix<numRow, numColumn, ValueType>::operator*=(const OtherValueType &value) {
#ifdef ENABLE_TEMPLATE_META
    MatrixMultiplyValue(*this, value);
#else
    for(int i = 0; i != row(); ++i) {
        for(int j = 0; j != column(); ++j) {
            _mat[i][j] *= value;
        }
    }
#endif
    return *this;
}

template<int numRow, int numColumn, class ValueType, class ValueType1>
inline MyMatrix<numRow, numColumn, ValueType> operator+(
                                                        const MyMatrix<numRow, numColumn, ValueType> &mat1,
                                                        const MyMatrix<numRow, numColumn, ValueType1> &mat2) {
    MyMatrix<numRow, numColumn, ValueType> retMat(mat1);
    retMat += mat2;
    return retMat;
}

template<int numRow, int numColumn, class ValueType>
inline MyMatrix<numRow, numColumn, ValueType> operator*(
                                                        const MyMatrix<numRow, numColumn, ValueType> &mat,
                                                        const ValueType &val) {
    MyMatrix<numRow, numColumn, ValueType> retMat(mat);
    retMat *= val;
    return retMat;
}

template<int numRow, int numColumn, class ValueType>
inline MyMatrix<numRow, numColumn, ValueType> operator*(const ValueType &val,
                                                        const MyMatrix<numRow, numColumn, ValueType> &mat) {
    MyMatrix<numRow, numColumn, ValueType> retMat(mat);
    retMat *= val;
    return retMat;
}

template<int retRow, int retColumn, int multiNum, class RetValueType, class SecondValueType>
inline MyMatrix<retRow, retColumn, RetValueType> operator*(
                                                           const MyMatrix<retRow, multiNum, RetValueType> &mat1,
                                                           const MyMatrix<multiNum, retColumn, SecondValueType> &mat2) {
    MyMatrix<retRow, retColumn, RetValueType> retMat;
#ifdef ENABLE_TEMPLATE_META
    MatrixMultiplyMatrix(retMat, mat1, mat2);
#else
    for(int i = 0; i != retRow; ++i) {
        for(int j = 0; j != retColumn; ++j) {
            for(int k = 0; k != multiNum; ++k) {
                retMat.valueAt(i, j) += mat1.valueAt(i, k) * mat2.valueAt(k, j);
            }
        }
    }
#endif
    return retMat;
}

template<int numRow, int numColumn, class ValueType>
inline MyMatrix<numColumn, numRow, ValueType> transposeMatrix(
                                                              const MyMatrix<numRow, numColumn, ValueType> &mat) {
    MyMatrix<numColumn, numRow, ValueType> retMat;
#ifdef ENABLE_TEMPLATE_META
    MatrixTranspose(retMat, mat);
#else
    for(int i = 0; i != numColumn; ++i) {
        for(int j = 0; j != numRow; ++j) {
            retMat.valueAt(i, j) = mat.valueAt(j, i);
        }
    }
#endif
    return retMat;
}

template<int numDim, class ValueType>
inline MyMatrix<numDim, numDim, ValueType> transposeMatrix(
                                                              const MyMatrix<numDim, numDim, ValueType> &mat) {
    MyMatrix<numDim, numDim, ValueType> retMat(mat);
    retMat.transpose();
    return retMat;
}

template<int numDim, class ValueType>
template<class OtherValueType>
inline MyMatrix<numDim, numDim, ValueType>::MyMatrix(const OtherValueType &value):
_dimension(numDim) {
#ifdef ENABLE_TEMPLATE_META
    MatrixAssignValue(*this, value);
#else
    for(int i = 0; i != _dimension; ++i) {
        for(int j = 0; j != _dimension; ++j) {
            _mat[i][j] = value;
        }
    }
#endif
}

template<int numDim, class ValueType>
template<class OtherValueType>
inline MyMatrix<numDim, numDim, ValueType>::MyMatrix(const MyMatrix<numDim, numDim, OtherValueType> &other):
_dimension(numDim) {
#ifdef ENABLE_TEMPLATE_META
    MatrixAssignMatrix(*this, other);
#else
    for(int i = 0; i != _dimension; ++i) {
        for(int j = 0; j != _dimension; ++j) {
            _mat[i][j] = other.valueAt(i, j);
        }
    }
#endif
}

template<int numDim, class ValueType>
template<class OtherValueType>
inline MyMatrix<numDim, numDim, ValueType>::MyMatrix(const MyMatrix<numDim, numDim, OtherValueType> &&other):
MyMatrix(other) {
}

template<int numDim, class ValueType>
template<class OtherValueType>
inline MyMatrix<numDim, numDim, ValueType>&
MyMatrix<numDim, numDim, ValueType>::operator=(const MyMatrix<numDim, numDim, OtherValueType> &other) {
#ifdef ENABLE_TEMPLATE_META
    MatrixAssignMatrix(*this, other);
#else
    for(int i = 0; i != dimension(); ++i) {
        for(int j = 0; j != dimension(); ++j) {
            _mat[i][j] = other.valueAt(i, j);
        }
    }
#endif
    return *this;
}

template<int numDim, class ValueType>
template<class OtherValueType>
inline MyMatrix<numDim, numDim, ValueType>&
MyMatrix<numDim, numDim, ValueType>::operator=(const MyMatrix<numDim, numDim, OtherValueType> &&other) {
#ifdef ENABLE_TEMPLATE_META
    MatrixAssignMatrix(*this, other);
#else
    for(int i = 0; i != dimension(); ++i) {
        for(int j = 0; j != dimension(); ++j) {
            _mat[i][j] = other.valueAt(i, j);
        }
    }
#endif
    return *this;
}

template<int numDim, class ValueType>
template<class OtherValueType>
inline MyMatrix<numDim, numDim, ValueType>&
MyMatrix<numDim, numDim, ValueType>::operator+=(const MyMatrix<numDim, numDim, OtherValueType> &other) {
#ifdef ENABLE_TEMPLATE_META
    MatrixAddMatrix(*this, other);
#else
    for(int i = 0; i != dimension(); ++i) {
        for(int j = 0; j != dimension(); ++j) {
            _mat[i][j] += other.valueAt(i, j);
        }
    }
#endif
    return *this;
}

template<int numDim, class ValueType>
template<class OtherValueType>
inline MyMatrix<numDim, numDim, ValueType>&
MyMatrix<numDim, numDim, ValueType>::operator*=(const OtherValueType &value) {
#ifdef ENABLE_TEMPLATE_META
    MatrixMultiplyValue(*this, value);
#else
    for(int i = 0; i != dimension(); ++i) {
        for(int j = 0; j != dimension(); ++j) {
            _mat[i][j] *= value;
        }
    }
#endif
    return *this;
}

template<int numDim, class ValueType>
inline MyMatrix<numDim, numDim, ValueType>& MyMatrix<numDim, numDim, ValueType>::transpose(void) {
#ifdef ENABLE_TEMPLATE_META
    SquareMatrixTranspose(*this);
#else
    ValueType tmp;
    for(int i = 0; i != dimension(); ++i) {
        for(int j = 0; j != dimension(); ++j) {
            if(i != j) {
                tmp = valueAt(i, j);
                valueAt(i, j) = valueAt(j, i);
                valueAt(j, i) = tmp;
            }
        }
    }
#endif
    return *this;
}

/*
template<int numDim, class ValueType>
template<class OtherValueType>
inline MyMatrix<numDim, numDim, ValueType>& MyMatrix<numDim, numDim, ValueType>::
operator*=( const MyMatrix<numDim, numDim, OtherValueType> &other) {
    
}
*/

MINE_NAMESPACE_END
