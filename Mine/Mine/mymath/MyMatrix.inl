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
    template<class MatrixType, class OtherValueType, int R, int C, int N, int I>
    struct MatrixAssignValueImpl {
        enum {
            Continue = I != 0,
            NextR = I/N,
            NextC = I%N,
            NextI = I - 1
        };
        
        static inline void eval(MatrixType &mat, OtherValueType val) {
            mat.valueAt(R, C) = val;
            MatrixAssignValueImpl<MatrixType, OtherValueType,
            NextR * Continue, NextC * Continue, N * Continue, NextI * Continue>::eval(mat, val);
        }
    };
    
    template<class MatrixType, class OtherValueType>
    struct MatrixAssignValueImpl<MatrixType, OtherValueType, 0, 0, 0, 0> {
        static inline void eval(MatrixType &mat, OtherValueType val) {}
    };
    
    template<int R, int C, class ValueType, class OtherValueType>
    inline void MatrixAssignValue(MyMatrix<R, C, ValueType> &mat, const OtherValueType & val) {
        MatrixAssignValueImpl<MyMatrix<R, C, ValueType>, OtherValueType, 0, 0, C, R * C - 1>::eval(mat, val);
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
        
        static inline void eval(MatrixType1 &mat, const MatrixTyp2 &other) {
            mat.valueAt(R, C) = other.valueAt(R, C);
            MatrixAssignMatrixImpl<MatrixType1, MatrixTyp2,
            NextR * Continue, NextC * Continue, N * Continue, NextI * Continue>::eval(mat, other);
        }
    };
    
    template<class MatrixType1, class MatrixTyp2>
    struct MatrixAssignMatrixImpl<MatrixType1, MatrixTyp2, 0, 0, 0, 0> {
        static inline void eval(MatrixType1 &mat, const MatrixTyp2 &other) {}
    };
    
    template<int R, int C, class ValueType, class OtherValueType>
    inline void MatrixAssignMatrix(MyMatrix<R, C, ValueType> &mat, const MyMatrix<R, C, OtherValueType> &other) {
        MatrixAssignMatrixImpl<MyMatrix<R, C, ValueType>, MyMatrix<R, C, OtherValueType>,
        0, 0, C, R * C - 1>::eval(mat, other);
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
        
        static inline void eval(MatrixType1 &mat, const MatrixTyp2 &other) {
            mat.valueAt(R, C) += other.valueAt(R, C);
            MatrixAddMatrixImpl<MatrixType1, MatrixTyp2,
            NextR * Continue, NextC * Continue, N * Continue, NextI * Continue>::eval(mat, other);
        }
    };
    
    template<class MatrixType1, class MatrixTyp2>
    struct MatrixAddMatrixImpl<MatrixType1, MatrixTyp2, 0, 0, 0, 0> {
        static inline void eval(MatrixType1 &mat, const MatrixTyp2 &other) {}
    };
    
    template<int R, int C, class ValueType, class OtherValueType>
    inline void MatrixAddMatrix(MyMatrix<R, C, ValueType> &mat, const MyMatrix<R, C, OtherValueType> &other) {
        MatrixAddMatrixImpl<MyMatrix<R, C, ValueType>, MyMatrix<R, C, OtherValueType>,
        0, 0, C, R * C - 1>::eval(mat, other);
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
        
        static inline void eval(MatrixType &mat, const ValueType &val) {
            mat.valueAt(R, C) *= val;
            MatrixMultiplyValueImpl<MatrixType, ValueType,
            NextR * Continue, NextC * Continue, N * Continue, NextI * Continue>::eval(mat, val);
        }
    };
    
    template<class MatrixType, class ValueType>
    struct MatrixMultiplyValueImpl<MatrixType, ValueType, 0, 0, 0, 0> {
        static inline void eval(MatrixType&, const ValueType&) {}
    };
    
    template<int R, int C, class ValueType, class OtherValueType>
    inline void MatrixMultiplyValue(MyMatrix<R, C, ValueType> &mat, const OtherValueType &val) {
        MatrixMultiplyValueImpl<MyMatrix<R, C, ValueType>, OtherValueType,
        0, 0, C, R * C - 1>::eval(mat, val);
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
        
        static inline void eval(MatrixType1 &retMat, const MatrixTyp2 &mat) {
            retMat.valueAt(R, C) = mat.valueAt(C, R);
            MatrixTransposeImpl<MatrixType1, MatrixTyp2,
            NextR * Continue, NextC * Continue, N * Continue, NextI * Continue>::eval(mat, mat);
        }
    };
    
    template<class MatrixType1, class MatrixTyp2>
    struct MatrixTransposeImpl<MatrixType1, MatrixTyp2, 0, 0, 0, 0> {
        static inline void eval(MatrixType1 &mat, const MatrixTyp2 &other) {}
    };
    
    template<int R, int C, class ValueType, class OtherValueType>
    inline void MatrixTranspose(MyMatrix<R, C, ValueType> &retMat, const MyMatrix<C, R, OtherValueType> &mat) {
        MatrixAddMatrixImpl<MyMatrix<R, C, ValueType>, MyMatrix<C, R, OtherValueType>,
        0, 0, C, R * C - 1>::eval(mat, mat);
    }
    
    // square matrix transpose
    template<class MatrixType, int R, int C, int N, int I>
    struct SquareMatrixTransposeImpl {
        enum {
            Continue = I != 1,
            Newline = C == N - 1,
            NextR = Newline ? R + 1 : R,
            NextC = Newline ? NextR + 1 : C + 1,
            NextI = I - 1
        };
        
        static typename MatrixType::value_type temp;
        
        static inline void eval(MatrixType &mat) {
            temp = mat.valueAt(R, C);
            mat.valueAt(R, C) = mat.valueAt(C, R);
            mat.valueAt(C, R) = temp;
            SquareMatrixTransposeImpl<MatrixType,
            NextR * Continue, NextC * Continue, N * Continue, NextI * Continue>::eval(mat);
        }
    };
    
    template<class MatrixType, int R, int C, int N, int I>
    typename MatrixType::value_type SquareMatrixTransposeImpl<MatrixType, R, C, N, I>::temp;
    
    // avoid to deduce 1x1 square matrix
    template<class MatrixType>
    struct SquareMatrixTransposeImpl<MatrixType, 0, 1, 1, 0> {
        static inline void eval(MatrixType&) {}
    };
    
    template<class MatrixType>
    struct SquareMatrixTransposeImpl<MatrixType, 0, 0, 0, 0> {
        static inline void eval(MatrixType&) {}
    };
    
    template<int R, class ValueType>
    inline void SquareMatrixTranspose(MyMatrix<R, R, ValueType> &mat) {
        SquareMatrixTransposeImpl<MyMatrix<R, R, ValueType>,0, 1, R, ((R * (R - 1)) >> 1)>::eval(mat);
    }
    
    // square matrix identity
    template<class MatrixType, int R, int C, int N, int I>
    struct SquareMatrixIdentityImpl {
        enum {
            Continue = I != 0,
            NextR = I/N,
            NextC = I%N,
            NextI = I - 1
        };
        
        static inline void eval(MatrixType &mat,
                                const typename MatrixType::value_type &identityValue,
                                const typename MatrixType::value_type &zeroValue) {
            mat.valueAt(R, C) = (R == C) ? identityValue : zeroValue;
            SquareMatrixIdentityImpl<MatrixType,
            NextR * Continue, NextC * Continue, N * Continue, NextI * Continue>::eval(mat, identityValue, zeroValue);
        }
    };
    
    template<class MatrixType>
    struct SquareMatrixIdentityImpl<MatrixType, 0, 0, 0, 0> {
        static inline void eval(MatrixType&,
                                const typename MatrixType::value_type&,
                                const typename MatrixType::value_type&) {}
    };
    
    template<int R, class ValueType>
    inline void SquareMatrixIdentity(MyMatrix<R, R, ValueType> &mat,
                                     const ValueType &identityValue,
                                     const ValueType &zeroValue) {
        SquareMatrixIdentityImpl<MyMatrix<R, R, ValueType>, 0, 0, R, R * R - 1>::eval(mat, identityValue, zeroValue);
    }
    
    // matrix multiply matrix
    template<class MatrixType1, class MatrixType2, class MatrixType3, int R, int C, int M, int K>
    struct MatrixInnerMultiplyMatrixImpl {
        enum {
            Continue = M != K - 1,
            NextM = M + 1
        };
        
        static inline void eval(MatrixType1 &retMat, const MatrixType2 &mat1, const MatrixType3 &mat2) {
            retMat.valueAt(R, C) += mat1.valueAt(R, M) * mat2.valueAt(M, C);
            MatrixInnerMultiplyMatrixImpl<MatrixType1, MatrixType2, MatrixType3,
            R * Continue, C * Continue, NextM * Continue,
            K * Continue>::eval(retMat, mat1, mat2);
        }
    };
    
    template<class MatrixType1, class MatrixType2, class MatrixType3>
    struct MatrixInnerMultiplyMatrixImpl<MatrixType1, MatrixType2, MatrixType3, 0, 0, 0, 0> {
        static inline void eval(MatrixType1 &retMat, const MatrixType2 &mat1, const MatrixType3 &mat2) {}
    };
    
    template<class MatrixType1, class MatrixType2, class MatrixType3, int R, int C, int N, int K, int I>
    struct MatrixMultiplyMatrixImpl {
        enum {
            Continue = I != 0,
            NextR = I/N,
            NextC = I%N,
            NextI = I - 1
        };
        
        static inline void eval(MatrixType1 &retMat, const MatrixType2 &mat1, const MatrixType3 &mat2) {
            MatrixInnerMultiplyMatrixImpl<MatrixType1, MatrixType2, MatrixType3, R, C, 0, K>::eval(retMat, mat1, mat2);
            
            MatrixMultiplyMatrixImpl<MatrixType1, MatrixType2, MatrixType3,
            NextR * Continue, NextC * Continue,
            N * Continue, K * Continue, NextI * Continue>::eval(retMat, mat1, mat2);
        }
    };
    
    template<class MatrixType1, class MatrixTyp2, class MatrixTyp3>
    struct MatrixMultiplyMatrixImpl<MatrixType1, MatrixTyp2, MatrixTyp3, 0, 0, 0, 0, 0> {
        static inline void eval(MatrixType1&, const MatrixTyp2&, const MatrixTyp3&) {}
    };
    
    template<int R, int K, int C, class RetValueType, class ValueType1, class ValueType2>
    inline void MatrixMultiplyMatrix(MyMatrix<R, C, RetValueType> &retMat,
                              const MyMatrix<R, K, ValueType1> &mat1,
                              const MyMatrix<K, C, ValueType2> &mat2) {
        MatrixAssignValue(retMat, RetValueType());
        MatrixMultiplyMatrixImpl<MyMatrix<R, C, RetValueType>, MyMatrix<R, K, ValueType1>, MyMatrix<K, C, ValueType2>,
        0, 0, C, K, R * C - 1>::eval(retMat, mat1, mat2);
    }
    
    /* -------------- elementary transformation ----------- */
    template<class MatrixType, int C, int N>
    struct MatrixSwapRowImpl {
        enum {
            Continue = C != N - 1,
            NextC = C + 1
        };
        
        static typename MatrixType::value_type temp;
        
        static inline void eval(MatrixType &mat, int a, int b) {
            temp = mat.valueAt(a, C);
            mat.valueAt(a, C) = mat.valueAt(b, C);
            mat.valueAt(b, C) = temp;
            
            MatrixSwapRowImpl<MatrixType,
            NextC * Continue, N * Continue>::eval(mat, a, b);
        }
    };
    
    template<class MatrixType, int C, int N>
    typename MatrixType::value_type MatrixSwapRowImpl<MatrixType, C, N>::temp;
    
    template<class MatrixType>
    struct MatrixSwapRowImpl<MatrixType, 0, 0> {
        static inline void eval(MatrixType&, int, int) {}
    };
    
    template<int R, int C, class ValueType>
    inline void MatrixSwapRow(MyMatrix<R, C, ValueType> &mat, int a, int b) {
        MatrixSwapRowImpl<MyMatrix<R, C, ValueType>, 0, C>::eval(mat, a, b);
    }
    
    /* -------------------------------------- */
    template<class MatrixType, class OtherValueType, int C, int N>
    struct MatrixMultiplyRowImpl {
        enum {
            Continue = C != N - 1,
            NextC = C + 1
        };
        
        static inline void eval(MatrixType &mat, int a,
                                const OtherValueType &multiple) {
            mat.valueAt(a, C) *= multiple;
            
            MatrixMultiplyRowImpl<MatrixType, OtherValueType,
            NextC * Continue, N * Continue>::eval(mat, a, multiple);
        }
    };
    
    template<class MatrixType, class OtherValueType>
    struct MatrixMultiplyRowImpl<MatrixType, OtherValueType, 0, 0> {
        static inline void eval(MatrixType&, int, const OtherValueType &multiple) {}
    };
    
    template<int R, int C, class ValueType, class OtherValueType>
    inline void MatrixMultiplyRow(MyMatrix<R, C, ValueType> &mat, int a, const OtherValueType &multiple) {
        MatrixMultiplyRowImpl<MyMatrix<R, C, ValueType>, OtherValueType, 0, C>::eval(mat, a, multiple);
    }
    
    /* -------------------------------------- */
    template<class MatrixType, class OtherValueType, int C, int N>
    struct MatrixSubtractRowImpl {
        enum {
            Continue = C != N - 1,
            NextC = C + 1
        };
        
        static inline void eval(MatrixType &mat, int a,
                                int b, const OtherValueType &multiple) {
            mat.valueAt(a, C) -= mat.valueAt(b, C) * multiple;
            
            MatrixSubtractRowImpl<MatrixType, OtherValueType,
            NextC * Continue, N * Continue>::eval(mat, a, b, multiple);
        }
    };
    
    template<class MatrixType, class OtherValueType>
    struct MatrixSubtractRowImpl<MatrixType, OtherValueType, 0, 0> {
        static inline void eval(MatrixType&, int, int, const OtherValueType&) {}
    };
    
    template<int R, int C, class ValueType, class OtherValueType>
    inline void MatrixSubtractRow(MyMatrix<R, C, ValueType> &mat, int a, int b, const OtherValueType &multiple) {
        MatrixSubtractRowImpl<MyMatrix<R, C, ValueType>, OtherValueType, 0, C>::eval(mat, a, b, multiple);
    }
    
    /* -------------------------------------- */
    template<class MatrixType, int R, int N>
    struct MatrixSwapColumnImpl {
        enum {
            Continue = R != N - 1,
            NextR = R + 1
        };
        
        static typename MatrixType::value_type temp;
        
        static inline void eval(MatrixType &mat, int a, int b) {
            temp = mat.valueAt(R, a);
            mat.valueAt(R, a) = mat.valueAt(R, b);
            mat.valueAt(R, b) = temp;
            
            MatrixSwapColumnImpl<MatrixType,
            NextR * Continue, N * Continue>::eval(mat, a, b);
        }
    };
    
    template<class MatrixType, int R, int N>
    typename MatrixType::value_type MatrixSwapColumnImpl<MatrixType, R, N>::temp;
    
    template<class MatrixType>
    struct MatrixSwapColumnImpl<MatrixType, 0, 0> {
        static inline void eval(MatrixType&, int, int) {}
    };
    
    template<int R, int C, class ValueType>
    inline void MatrixSwapColumn(MyMatrix<R, C, ValueType> &mat, int a, int b) {
        MatrixSwapColumnImpl<MyMatrix<R, C, ValueType>, 0, R>::eval(mat, a, b);
    }
    
    /* -------------------------------------- */
    template<class MatrixType, class OtherValueType, int R, int N>
    struct MatrixMultiplyColumnImpl {
        enum {
            Continue = R != N - 1,
            NextR = R + 1
        };
        
        static inline void eval(MatrixType &mat, int a,
                                const OtherValueType &multiple) {
            mat.valueAt(R, a) *= multiple;
            
            MatrixMultiplyColumnImpl<MatrixType, OtherValueType,
            NextR * Continue, N * Continue>::eval(mat, a, multiple);
        }
    };
    
    template<class MatrixType, class OtherValueType>
    struct MatrixMultiplyColumnImpl<MatrixType, OtherValueType, 0, 0> {
        static inline void eval(MatrixType&, int, const OtherValueType&) {}
    };
    
    template<int R, int C, class ValueType, class OtherValueType>
    inline void MatrixMultiplyColumn(MyMatrix<R, C, ValueType> &mat, int a, const OtherValueType &multiple) {
        MatrixMultiplyColumnImpl<MyMatrix<R, C, ValueType>, OtherValueType, 0, R>::eval(mat, a, multiple);
    }
    
    /* -------------------------------------- */
    template<class MatrixType, class OtherValueType, int R, int N>
    struct MatrixSubtractColumnImpl {
        enum {
            Continue = R != N - 1,
            NextR = R + 1
        };
        
        static inline void eval(MatrixType &mat, int a,
                                int b, const OtherValueType &multiple) {
            mat.valueAt(R, a) -= mat.valueAt(R, b) * multiple;
            
            MatrixSubtractColumnImpl<MatrixType, OtherValueType,
            NextR * Continue, N * Continue>::eval(mat, a, b, multiple);
        }
    };
    
    template<class MatrixType, class OtherValueType>
    struct MatrixSubtractColumnImpl<MatrixType, OtherValueType, 0, 0> {
        static inline void eval(MatrixType&, int, int, const OtherValueType&) {}
    };
    
    template<int R, int C, class ValueType, class OtherValueType>
    inline void MatrixSubtractColumn(MyMatrix<R, C, ValueType> &mat, int a, int b, const OtherValueType &multiple) {
        MatrixSubtractColumnImpl<MyMatrix<R, C, ValueType>, OtherValueType, 0, C>::eval(mat, a, b, multiple);
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

// ------------------------------- matrix operation ----------------------------------------- //

template<int numRow, int numColumn, class ValueType>
inline MyMatrix<numColumn, numRow, ValueType>&
zeroMatrix(MyMatrix<numRow, numColumn, ValueType> &mat,
           const ValueType &zeroValue) {
#ifdef ENABLE_TEMPLATE_META
    MatrixAssignValue(mat, zeroValue);
#else
    for(int i = 0; i != numRow; ++i) {
        for(int j = 0; j != numColumn; ++j) {
            retMat.valueAt(i, j) = zeroValue;
        }
    }
#endif
    return mat;
}

template<int numDim, class ValueType>
inline MyMatrix<numDim, numDim, ValueType>&
identityMatrix(MyMatrix<numDim, numDim, ValueType> &mat,
               const ValueType &identityValue,
               const ValueType &zeroValue) {
#ifdef ENABLE_TEMPLATE_META
    SquareMatrixIdentity(mat, identityValue, zeroValue);
#else
    for(int i = 0; i != numDim; ++i) {
        for(int j = 0; j != numDim; ++j) {
            retMat.valueAt(i, j) = (i == j) ? identityValue : zeroValue;
        }
    }
#endif
    return mat;
}

template<int numRow, int numColumn, class ValueType>
inline MyMatrix<numColumn, numRow, ValueType>
transposeMatrix(const MyMatrix<numRow, numColumn, ValueType> &mat) {
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
inline MyMatrix<numDim, numDim, ValueType>&
transposeMatrix(MyMatrix<numDim, numDim, ValueType> &mat) {
#ifdef ENABLE_TEMPLATE_META
    SquareMatrixTranspose(mat);
#else
    ValueType tmp;
    for(int i = 0; i != numDim; ++i) {
        for(int j = i + 1; j != numDim; ++j) {
            tmp = retMat.valueAt(i, j);
            retMat.valueAt(i, j) = mat.valueAt(j, i);
            mat.valueAt(j, i) = tmp;
        }
    }
#endif
    return mat;
}

// ------------------------------- matrix operation ----------------------------------------- //

// ------------------------------- elementary transformation  ----------------------------------------- //

template<int numRow, int numColumn, class ValueType>
MyMatrix<numColumn, numRow, ValueType>&
swapMatrixRow(MyMatrix<numRow, numColumn, ValueType> &mat, int a, int b) {
#ifdef ENABLE_TEMPLATE_META
    MatrixSwapRow(mat, a, b);
#else
    ValueType tmp;
    for(int i = 0; i != numColumn; ++i) {
            tmp = mat.valueAt(a, i);
            mat.valueAt(a, i) = mat.valueAt(b, i);
            mat.valueAt(b, i) = tmp;
    }
#endif
    return mat;
}

template<int numRow, int numColumn, class ValueType, class OtherValueType>
MyMatrix<numColumn, numRow, ValueType>&
multiplyMatrixRow(MyMatrix<numRow, numColumn, ValueType> &mat, int a, const OtherValueType &multiple) {
#ifdef ENABLE_TEMPLATE_META
    MatrixMultiplyRow(mat, a, multiple);
#else
    for(int i = 0; i != numColumn; ++i) {
        mat.valueAt(a, i) *= multiple;
    }
#endif
    return mat;
}

template<int numRow, int numColumn, class ValueType, class OtherValueType>
MyMatrix<numColumn, numRow, ValueType>&
subtractMatrixRow(MyMatrix<numRow, numColumn, ValueType> &mat,  int a,
                  int b, const OtherValueType &multiple) {
#ifdef ENABLE_TEMPLATE_META
    MatrixSubtractRow(mat, a, b, multiple);
#else
    for(int i = 0; i != numColumn; ++i) {
        mat.valueAt(a, i) -= mat.valueAt(b, i) * multiple;
    }
#endif
    return mat;
}

template<int numRow, int numColumn, class ValueType>
MyMatrix<numColumn, numRow, ValueType>&
swapMatrixColumn(MyMatrix<numRow, numColumn, ValueType> &mat, int a, int b) {
#ifdef ENABLE_TEMPLATE_META
    MatrixSwapColumn(mat, a, b);
#else
    ValueType tmp;
    for(int i = 0; i != numRow; ++i) {
        tmp = mat.valueAt(i, a);
        mat.valueAt(i, a) = mat.valueAt(i, b);
        mat.valueAt(i, b) = tmp;
    }
#endif
    return mat;
}

template<int numRow, int numColumn, class ValueType, class OtherValueType>
MyMatrix<numColumn, numRow, ValueType>&
multiplyMatrixColumn(MyMatrix<numRow, numColumn, ValueType> &mat, int a, const OtherValueType &multiple) {
#ifdef ENABLE_TEMPLATE_META
    MatrixMultiplyColumn(mat, a, multiple);
#else
    for(int i = 0; i != numRow; ++i) {
        mat.valueAt(i, a) *= multiple;
    }
#endif
    return mat;
}

template<int numRow, int numColumn, class ValueType, class OtherValueType>
MyMatrix<numColumn, numRow, ValueType>&
subtractMatrixColumn(MyMatrix<numRow, numColumn, ValueType> &mat, int a,
                     int b, const OtherValueType &multiple) {
#ifdef ENABLE_TEMPLATE_META
    MatrixSubtractColumn(mat, a, b, multiple);
#else
    for(int i = 0; i != numRow; ++i) {
        mat.valueAt(i, a) -= mat.valueAt(i, b) * multiple;
    }
#endif
    return mat;
}

// ------------------------------- elementary transformation  ----------------------------------------- //

MINE_NAMESPACE_END
