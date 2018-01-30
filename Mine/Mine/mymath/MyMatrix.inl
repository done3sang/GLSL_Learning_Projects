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
    template<class M, class T, int R, int C, int N, int I>
    struct MatrixAssignValueImpl {
        enum {
            Continue = I != 0,
            NextR = I/N,
            NextC = I%N,
            NextI = I - 1
        };
        
        static inline void eval(M &mat, T val) {
            mat.valueAt(R, C) = val;
            MatrixAssignValueImpl<M, T,
            NextR * Continue, NextC * Continue, N * Continue, NextI * Continue>::eval(mat, val);
        }
    };
    
    template<class M, class T>
    struct MatrixAssignValueImpl<M, T, 0, 0, 0, 0> {
        static inline void eval(M &mat, T val) {}
    };
    
    template<int R, int C, class V, class T>
    inline void MatrixAssignValue(MyMatrix<R, C, V> &mat, const T & val) {
        MatrixAssignValueImpl<MyMatrix<R, C, V>, T, 0, 0, C, R * C - 1>::eval(mat, val);
    }
    
    // matrix assign initializer_list
    template<class M, class Iterator, int R, int C, int N, int I>
    struct MatrixAssignInitializerImpl {
        enum {
            Continue = I != 0,
            Newline = C == N - 1,
            NextR = Newline ? R + 1 : R,
            NextC = Newline ? 0 : C + 1,
            NextI = I - 1
        };
        
        static inline void eval(M &mat, Iterator curr, Iterator last) {
            if(last != curr) {
                mat.valueAt(R, C) = *curr;
                ++curr;
            } else {
                mat.valueAt(R, C) = typename M::value_type();
            }
            MatrixAssignInitializerImpl<M, Iterator,
            NextR * Continue, NextC * Continue, N * Continue, NextI * Continue>::eval(mat, curr, last);
        }
    };
    
    template<class M, class Iterator>
    struct MatrixAssignInitializerImpl<M, Iterator, 0, 0, 0, 0> {
        static inline void eval(M &mat, Iterator curr, Iterator last) {}
    };
    
    template<int R, int C, class V, class Iterator>
    inline void MatrixAssignInitializer(MyMatrix<R, C, V> &mat, Iterator first, Iterator last) {
        MatrixAssignInitializerImpl<MyMatrix<R, C, V>, Iterator, 0, 0, C, R * C - 1>::eval(mat, first, last);
    }
    
    // matrix assign matrix
    template<class M1, class M2, int R, int C, int N, int I>
    struct MatrixAssignMatrixImpl {
        enum {
            Continue = I != 0,
            NextR = I/N,
            NextC = I%N,
            NextI = I - 1
        };
        
        static inline void eval(M1 &mat, const M2 &other) {
            mat.valueAt(R, C) = other.valueAt(R, C);
            MatrixAssignMatrixImpl<M1, M2,
            NextR * Continue, NextC * Continue, N * Continue, NextI * Continue>::eval(mat, other);
        }
    };
    
    template<class M1, class M2>
    struct MatrixAssignMatrixImpl<M1, M2, 0, 0, 0, 0> {
        static inline void eval(M1 &mat, const M2 &other) {}
    };
    
    template<int R, int C, class V, class T>
    inline void MatrixAssignMatrix(MyMatrix<R, C, V> &mat, const MyMatrix<R, C, T> &other) {
        MatrixAssignMatrixImpl<MyMatrix<R, C, V>, MyMatrix<R, C, T>,
        0, 0, C, R * C - 1>::eval(mat, other);
    }
    
    // matrix add matrix
    template<class M1, class M2, int R, int C, int N, int I>
    struct MatrixAddMatrixImpl {
        enum {
            Continue = I != 0,
            NextR = I/N,
            NextC = I%N,
            NextI = I - 1
        };
        
        static inline void eval(M1 &mat, const M2 &other) {
            mat.valueAt(R, C) += other.valueAt(R, C);
            MatrixAddMatrixImpl<M1, M2,
            NextR * Continue, NextC * Continue, N * Continue, NextI * Continue>::eval(mat, other);
        }
    };
    
    template<class M1, class M2>
    struct MatrixAddMatrixImpl<M1, M2, 0, 0, 0, 0> {
        static inline void eval(M1 &mat, const M2 &other) {}
    };
    
    template<int R, int C, class V, class T>
    inline void MatrixAddMatrix(MyMatrix<R, C, V> &mat, const MyMatrix<R, C, T> &other) {
        MatrixAddMatrixImpl<MyMatrix<R, C, V>, MyMatrix<R, C, T>,
        0, 0, C, R * C - 1>::eval(mat, other);
    }
    
    // matrix add matrix
    template<class M1, class M2, int R, int C, int N, int I>
    struct MatrixMinusMatrixImpl {
        enum {
            Continue = I != 0,
            NextR = I/N,
            NextC = I%N,
            NextI = I - 1
        };
        
        static inline void eval(M1 &mat, const M2 &other) {
            mat.valueAt(R, C) -= other.valueAt(R, C);
            MatrixMinusMatrixImpl<M1, M2,
            NextR * Continue, NextC * Continue, N * Continue, NextI * Continue>::eval(mat, other);
        }
    };
    
    template<class M1, class M2>
    struct MatrixMinusMatrixImpl<M1, M2, 0, 0, 0, 0> {
        static inline void eval(M1 &mat, const M2 &other) {}
    };
    
    template<int R, int C, class V, class T>
    inline void MatrixMinusMatrix(MyMatrix<R, C, V> &mat, const MyMatrix<R, C, T> &other) {
        MatrixMinusMatrixImpl<MyMatrix<R, C, V>, MyMatrix<R, C, T>,
        0, 0, C, R * C - 1>::eval(mat, other);
    }
    
    // matrix mutliple by value
    template<class M, class V, int R, int C, int N, int I>
    struct MatrixMultiplyValueImpl {
        enum {
            Continue = I != 0,
            NextR = I/N,
            NextC = I%N,
            NextI = I - 1
        };
        
        static inline void eval(M &mat, const V &val) {
            mat.valueAt(R, C) *= val;
            MatrixMultiplyValueImpl<M, V,
            NextR * Continue, NextC * Continue, N * Continue, NextI * Continue>::eval(mat, val);
        }
    };
    
    template<class M, class V>
    struct MatrixMultiplyValueImpl<M, V, 0, 0, 0, 0> {
        static inline void eval(M&, const V&) {}
    };
    
    template<int R, int C, class V, class T>
    inline void MatrixMultiplyValue(MyMatrix<R, C, V> &mat, const T &val) {
        MatrixMultiplyValueImpl<MyMatrix<R, C, V>, T,
        0, 0, C, R * C - 1>::eval(mat, val);
    }
    
    // matrix transpose
    template<class M1, class M2, int R, int C, int N, int I>
    struct MatrixTransposeImpl {
        enum {
            Continue = I != 0,
            NextR = I/N,
            NextC = I%N,
            NextI = I - 1
        };
        
        static inline void eval(M1 &retMat, const M2 &mat) {
            retMat.valueAt(R, C) = mat.valueAt(C, R);
            MatrixTransposeImpl<M1, M2,
            NextR * Continue, NextC * Continue, N * Continue, NextI * Continue>::eval(mat, mat);
        }
    };
    
    template<class M1, class M2>
    struct MatrixTransposeImpl<M1, M2, 0, 0, 0, 0> {
        static inline void eval(M1 &mat, const M2 &other) {}
    };
    
    template<int R, int C, class V, class T>
    inline void MatrixTranspose(MyMatrix<R, C, V> &retMat, const MyMatrix<C, R, T> &mat) {
        MatrixAddMatrixImpl<MyMatrix<R, C, V>, MyMatrix<C, R, T>,
        0, 0, C, R * C - 1>::eval(mat, mat);
    }
    
    // square matrix transpose
    template<class M, int R, int C, int N, int I>
    struct SquareMatrixTransposeImpl {
        enum {
            Continue = I != 1,
            Newline = C == N - 1,
            NextR = Newline ? R + 1 : R,
            NextC = Newline ? NextR + 1 : C + 1,
            NextI = I - 1
        };
        
        static typename M::value_type temp;
        
        static inline void eval(M &mat) {
            temp = mat.valueAt(R, C);
            mat.valueAt(R, C) = mat.valueAt(C, R);
            mat.valueAt(C, R) = temp;
            SquareMatrixTransposeImpl<M,
            NextR * Continue, NextC * Continue, N * Continue, NextI * Continue>::eval(mat);
        }
    };
    
    template<class M, int R, int C, int N, int I>
    typename M::value_type SquareMatrixTransposeImpl<M, R, C, N, I>::temp;
    
    // avoid to deduce 1x1 square matrix
    template<class M>
    struct SquareMatrixTransposeImpl<M, 0, 1, 1, 0> {
        static inline void eval(M&) {}
    };
    
    template<class M>
    struct SquareMatrixTransposeImpl<M, 0, 0, 0, 0> {
        static inline void eval(M&) {}
    };
    
    template<int R, class V>
    inline void SquareMatrixTranspose(MyMatrix<R, R, V> &mat) {
        SquareMatrixTransposeImpl<MyMatrix<R, R, V>,0, 1, R, ((R * (R - 1)) >> 1)>::eval(mat);
    }
    
    // square matrix identity
    template<class M, int R, int C, int N, int I>
    struct SquareMatrixIdentityImpl {
        enum {
            Continue = I != 0,
            NextR = I/N,
            NextC = I%N,
            NextI = I - 1
        };
        
        static inline void eval(M &mat,
                                const typename M::value_type &identityValue,
                                const typename M::value_type &zeroValue) {
            mat.valueAt(R, C) = (R == C) ? identityValue : zeroValue;
            SquareMatrixIdentityImpl<M,
            NextR * Continue, NextC * Continue, N * Continue, NextI * Continue>::eval(mat, identityValue, zeroValue);
        }
    };
    
    template<class M>
    struct SquareMatrixIdentityImpl<M, 0, 0, 0, 0> {
        static inline void eval(M&,
                                const typename M::value_type&,
                                const typename M::value_type&) {}
    };
    
    template<int R, class V>
    inline void SquareMatrixIdentity(MyMatrix<R, R, V> &mat,
                                     const V &identityValue,
                                     const V &zeroValue) {
        SquareMatrixIdentityImpl<MyMatrix<R, R, V>, 0, 0, R, R * R - 1>::eval(mat, identityValue, zeroValue);
    }
    
    // matrix multiply matrix
    template<class M1, class M2, class M3, int R, int C, int M, int K>
    struct MatrixInnerMultiplyMatrixImpl {
        enum {
            Continue = M != K - 1,
            NextM = M + 1
        };
        
        static inline void eval(M1 &retMat, const M2 &mat1, const M3 &mat2) {
            retMat.valueAt(R, C) += mat1.valueAt(R, M) * mat2.valueAt(M, C);
            MatrixInnerMultiplyMatrixImpl<M1, M2, M3,
            R * Continue, C * Continue, NextM * Continue,
            K * Continue>::eval(retMat, mat1, mat2);
        }
    };
    
    template<class M1, class M2, class M3>
    struct MatrixInnerMultiplyMatrixImpl<M1, M2, M3, 0, 0, 0, 0> {
        static inline void eval(M1 &retMat, const M2 &mat1, const M3 &mat2) {}
    };
    
    template<class M1, class M2, class M3, int R, int C, int N, int K, int I>
    struct MatrixMultiplyMatrixImpl {
        enum {
            Continue = I != 0,
            NextR = I/N,
            NextC = I%N,
            NextI = I - 1
        };
        
        static inline void eval(M1 &retMat, const M2 &mat1, const M3 &mat2) {
            MatrixInnerMultiplyMatrixImpl<M1, M2, M3, R, C, 0, K>::eval(retMat, mat1, mat2);
            
            MatrixMultiplyMatrixImpl<M1, M2, M3,
            NextR * Continue, NextC * Continue,
            N * Continue, K * Continue, NextI * Continue>::eval(retMat, mat1, mat2);
        }
    };
    
    template<class M1, class M2, class M3>
    struct MatrixMultiplyMatrixImpl<M1, M2, M3, 0, 0, 0, 0, 0> {
        static inline void eval(M1&, const M2&, const M3&) {}
    };
    
    template<int R, int K, int C, class RetV, class V, class T>
    inline void MatrixMultiplyMatrix(MyMatrix<R, C, RetV> &retMat,
                              const MyMatrix<R, K, V> &mat1,
                              const MyMatrix<K, C, T> &mat2) {
        MatrixAssignValue(retMat, RetV());
        MatrixMultiplyMatrixImpl<MyMatrix<R, C, RetV>, MyMatrix<R, K, V>, MyMatrix<K, C, T>,
        0, 0, C, K, R * C - 1>::eval(retMat, mat1, mat2);
    }
    
    /* -------------- elementary transformation ----------- */
    template<class M, int C, int N>
    struct MatrixSwapRowImpl {
        enum {
            Continue = C != N - 1,
            NextC = C + 1
        };
        
        static typename M::value_type temp;
        
        static inline void eval(M &mat, int a, int b) {
            temp = mat.valueAt(a, C);
            mat.valueAt(a, C) = mat.valueAt(b, C);
            mat.valueAt(b, C) = temp;
            
            MatrixSwapRowImpl<M,
            NextC * Continue, N * Continue>::eval(mat, a, b);
        }
    };
    
    template<class M, int C, int N>
    typename M::value_type MatrixSwapRowImpl<M, C, N>::temp;
    
    template<class M>
    struct MatrixSwapRowImpl<M, 0, 0> {
        static inline void eval(M&, int, int) {}
    };
    
    template<int R, int C, class V>
    inline void MatrixSwapRow(MyMatrix<R, C, V> &mat, int a, int b) {
        MatrixSwapRowImpl<MyMatrix<R, C, V>, 0, C>::eval(mat, a, b);
    }
    
    /* -------------------------------------- */
    template<class M, class T, int C, int N>
    struct MatrixMultiplyRowImpl {
        enum {
            Continue = C != N - 1,
            NextC = C + 1
        };
        
        static inline void eval(M &mat, int a, const T &multiple) {
            mat.valueAt(a, C) *= multiple;
            
            MatrixMultiplyRowImpl<M, T,
            NextC * Continue, N * Continue>::eval(mat, a, multiple);
        }
    };
    
    template<class M, class T>
    struct MatrixMultiplyRowImpl<M, T, 0, 0> {
        static inline void eval(M&, int, const T &multiple) {}
    };
    
    template<int R, int C, class V, class T>
    inline void MatrixMultiplyRow(MyMatrix<R, C, V> &mat, int a, const T &multiple) {
        MatrixMultiplyRowImpl<MyMatrix<R, C, V>, T, 0, C>::eval(mat, a, multiple);
    }
    
    /* -------------------------------------- */
    template<class M, class T, int C, int N>
    struct MatrixSubtractRowImpl {
        enum {
            Continue = C != N - 1,
            NextC = C + 1
        };
        
        static inline void eval(M &mat, int a, int b, const T &multiple) {
            mat.valueAt(a, C) -= mat.valueAt(b, C) * multiple;
            
            MatrixSubtractRowImpl<M, T,
            NextC * Continue, N * Continue>::eval(mat, a, b, multiple);
        }
    };
    
    template<class M, class T>
    struct MatrixSubtractRowImpl<M, T, 0, 0> {
        static inline void eval(M&, int, int, const T&) {}
    };
    
    template<int R, int C, class V, class T>
    inline void MatrixSubtractRow(MyMatrix<R, C, V> &mat, int a, int b, const T &multiple) {
        MatrixSubtractRowImpl<MyMatrix<R, C, V>, T, 0, C>::eval(mat, a, b, multiple);
    }
    
    /* -------------------------------------- */
    template<class M, int R, int N>
    struct MatrixSwapColumnImpl {
        enum {
            Continue = R != N - 1,
            NextR = R + 1
        };
        
        static typename M::value_type temp;
        
        static inline void eval(M &mat, int a, int b) {
            temp = mat.valueAt(R, a);
            mat.valueAt(R, a) = mat.valueAt(R, b);
            mat.valueAt(R, b) = temp;
            
            MatrixSwapColumnImpl<M,
            NextR * Continue, N * Continue>::eval(mat, a, b);
        }
    };
    
    template<class M, int R, int N>
    typename M::value_type MatrixSwapColumnImpl<M, R, N>::temp;
    
    template<class M>
    struct MatrixSwapColumnImpl<M, 0, 0> {
        static inline void eval(M&, int, int) {}
    };
    
    template<int R, int C, class V>
    inline void MatrixSwapColumn(MyMatrix<R, C, V> &mat, int a, int b) {
        MatrixSwapColumnImpl<MyMatrix<R, C, V>, 0, R>::eval(mat, a, b);
    }
    
    /* -------------------------------------- */
    template<class M, class T, int R, int N>
    struct MatrixMultiplyColumnImpl {
        enum {
            Continue = R != N - 1,
            NextR = R + 1
        };
        
        static inline void eval(M &mat, int a,
                                const T &multiple) {
            mat.valueAt(R, a) *= multiple;
            
            MatrixMultiplyColumnImpl<M, T,
            NextR * Continue, N * Continue>::eval(mat, a, multiple);
        }
    };
    
    template<class M, class T>
    struct MatrixMultiplyColumnImpl<M, T, 0, 0> {
        static inline void eval(M&, int, const T&) {}
    };
    
    template<int R, int C, class V, class T>
    inline void MatrixMultiplyColumn(MyMatrix<R, C, V> &mat, int a, const T &multiple) {
        MatrixMultiplyColumnImpl<MyMatrix<R, C, V>, T, 0, R>::eval(mat, a, multiple);
    }
    
    /* -------------------------------------- */
    template<class M, class T, int R, int N>
    struct MatrixSubtractColumnImpl {
        enum {
            Continue = R != N - 1,
            NextR = R + 1
        };
        
        static inline void eval(M &mat, int a,
                                int b, const T &multiple) {
            mat.valueAt(R, a) -= mat.valueAt(R, b) * multiple;
            
            MatrixSubtractColumnImpl<M, T,
            NextR * Continue, N * Continue>::eval(mat, a, b, multiple);
        }
    };
    
    template<class M, class T>
    struct MatrixSubtractColumnImpl<M, T, 0, 0> {
        static inline void eval(M&, int, int, const T&) {}
    };
    
    template<int R, int C, class V, class T>
    inline void MatrixSubtractColumn(MyMatrix<R, C, V> &mat, int a, int b, const T &multiple) {
        MatrixSubtractColumnImpl<MyMatrix<R, C, V>, T, 0, C>::eval(mat, a, b, multiple);
    }
    
    /* ------------------- square matrix determinant ------------------- */
    
    /* ------------------- simply matrix by subtract  ------------------- */
    template<class M, int I, int R, int C>
    struct SimplifyMatrixBySubtractRowInnerImpl {
        enum {
            Continue = I != R - 1,
            NextI = I + 1
        };
        
        static inline void eval(M &mat,
                                int t,
                                const typename M::value_type &dem,
                                bool *gauss) {
            if(((I < t && gauss[I]) || I > t) && !mat.zeroAt(I, C)) {
                MatrixSubtractRow(mat, I, t, mat.valueAt(I, C) * dem);
            }
            SimplifyMatrixBySubtractRowInnerImpl<M, Continue * NextI,
            Continue * R, Continue * C>::eval(mat, t, dem, gauss);
        }
    };
    
    template<class M>
    struct SimplifyMatrixBySubtractRowInnerImpl<M, 0, 0, 0> {
        static inline void eval(M&,
                                int,
                                const typename M::value_type&,
                                bool*) {}
    };
    
    template<class M, int I, int R, int C>
    struct SimplifyMatrixBySubtractRowImpl {
        enum {
            Continue = I != R - 1,
            NextI = I + 1
        };
        
        static typename M::value_type dem;
        
        static inline void eval(M &mat, bool *gauss) {
            if(!gauss[I] && !mat.zeroAt(I, C)) {
                dem = M::identityValue()/mat.valueAt(I, C);
                SimplifyMatrixBySubtractRowInnerImpl<M, 0, R, C>::eval(mat, I, dem, gauss);
                gauss[I] = true;
                return;
            }
            SimplifyMatrixBySubtractRowImpl<M, Continue * NextI,
            Continue * R, Continue * C>::eval(mat, gauss);
        }
    };
    
    template<class M, int I, int R, int C>
    typename M::value_type SimplifyMatrixBySubtractRowImpl<M, I, R, C>::dem;
    
    template<class M>
    struct SimplifyMatrixBySubtractRowImpl<M, 0, 0, 0> {
        static inline void eval(M &mat, bool *gauss) {}
    };
    
    template<class M, int R, int I, int N>
    struct SimplifyMatrixBySubtractImpl {
        enum {
            Continue = I != N - 1,
            NextI = I + 1
        };
        
        static inline void eval(M &mat, bool *gauss) {
            SimplifyMatrixBySubtractRowImpl<M, 0, R, I>::eval(mat, gauss);
            SimplifyMatrixBySubtractImpl<M, Continue * R,
            Continue * NextI, Continue * N>::eval(mat, gauss);
        }
    };
    
    template<class M>
    struct SimplifyMatrixBySubtractImpl<M, 0, 0, 0> {
        static inline void eval(M &mat, bool *gauss) {}
    };
    
    // avoid to deduce vector, wonderful for partial template specialization
    // thanks to clang&gcc powerful compiler
    template<class M, int R>
    struct SimplifyMatrixBySubtractImpl<M, R, 0, 1> {
        static inline void eval(M &mat, bool *gauss) {}
    };
    
    // depth = R * C
    template<int R, int C, class V>
    inline void SimplifyMatrixBySubtract(MyMatrix<R, C, V> &mat) {
        constexpr int N = R < C ? R : C;
        bool gauss[N] = {false};
        SimplifyMatrixBySubtractImpl<MyMatrix<R, C, V>, R, 0, N>::eval(mat, gauss);
    }
}

template<int R, int C, class V> typename MyMatrix<R, C, V>::value_type MyMatrix<R, C, V>::_zeroValue = V(0);
template<int R, int C, class V> typename MyMatrix<R, C, V>::value_type MyMatrix<R, C, V>::_identityValue = V(1);

template<int R, int C, class V>
template<class T>
inline MyMatrix<R, C, V>::MyMatrix(const T &value):
_row(R), _column(C) {
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

template<int R, int C, class V>
template<class T>
inline MyMatrix<R, C, V>::MyMatrix(const MyMatrix<R, C, T> &other):
_row(R), _column(C) {
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

template<int R, int C, class V>
template<class T>
inline MyMatrix<R, C, V>::MyMatrix(const MyMatrix<R, C, T> &&other):
MyMatrix(other) {
}

template<int R, int C, class V>
template<class T>
inline MyMatrix<R, C, V>::MyMatrix(const std::initializer_list<T> &il):
_row(R), _column(C) {
#ifdef ENABLE_TEMPLATE_META
//#if R * C < 1024
    MatrixAssignInitializer(*this, il.begin(), il.end());
#else
    auto initIter(il.begin());
    auto initEnd(il.end());
    for(int i = 0; i != _row; ++i) {
        for(int j = 0; j != _column; ++j) {
            if(initEnd != initIter) {
                _mat[i][j] = *initIter;
                ++initIter;
            } else {
                _mat[i][j] = value_type();
            }
        }
    }
#endif
}

template<int R, int C, class V>
template<class T>
inline MyMatrix<R, C, V>&
MyMatrix<R, C, V>::operator=(const MyMatrix<R, C, T> &other) {
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

template<int R, int C, class V>
template<class T>
inline MyMatrix<R, C, V>&
MyMatrix<R, C, V>::operator=(const MyMatrix<R, C, T> &&other) {
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

template<int R, int C, class V>
template<class T>
inline MyMatrix<R, C, V>&
MyMatrix<R, C, V>::operator=(const std::initializer_list<T> &il) {
#ifdef ENABLE_TEMPLATE_META
    MatrixAssignInitializer(*this, il.begin(), il.end());
#else
    auto initIter(il.begin());
    auto initEnd(il.end());
    for(int i = 0; i != _row; ++i) {
        for(int j = 0; j != _column; ++j) {
            if(initEnd == initIter) {
                break;
            }
            _mat[i][j] = value;
            ++initIter;
        }
    }
#endif
    return *this;
}

template<int R, int C, class V>
template<class T>
inline MyMatrix<R, C, V>&
MyMatrix<R, C, V>::operator+=(const MyMatrix<R, C, T> &other) {
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

template<int R, int C, class V>
template<class T>
inline MyMatrix<R, C, V>&
MyMatrix<R, C, V>::operator-=(const MyMatrix<R, C, T> &other) {
#ifdef ENABLE_TEMPLATE_META
    MatrixMinusMatrix(*this, other);
#else
    for(int i = 0; i != row(); ++i) {
        for(int j = 0; j != column(); ++j) {
            _mat[i][j] -= other.valueAt(i, j);
        }
    }
#endif
    return *this;
}

template<int R, int C, class V>
template<class T>
inline MyMatrix<R, C, V>&
MyMatrix<R, C, V>::operator*=(const T &value) {
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

template<int D, class V> typename MyMatrix<D, D, V>::value_type MyMatrix<D, D, V>::_zeroValue = V(0);
template<int D, class V> typename MyMatrix<D, D, V>::value_type MyMatrix<D, D, V>::_identityValue = V(1);

template<int D, class V>
template<class T>
inline MyMatrix<D, D, V>::MyMatrix(const T &value):
_dimension(D) {
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

template<int D, class V>
template<class T>
inline MyMatrix<D, D, V>::MyMatrix(const MyMatrix<D, D, T> &other):
_dimension(D) {
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

template<int D, class V>
template<class T>
inline MyMatrix<D, D, V>::MyMatrix(const MyMatrix<D, D, T> &&other):
MyMatrix(other) {
}

template<int D, class V>
template<class T>
inline MyMatrix<D, D, V>::MyMatrix(const std::initializer_list<T> &il):
_dimension(D) {
#ifdef ENABLE_TEMPLATE_META
    MatrixAssignInitializer(*this, il.begin(), il.end());
#else
    auto initIter(il.begin());
    auto initEnd(il.end());
    for(int i = 0; i != _row; ++i) {
        for(int j = 0; j != _column; ++j) {
            if(initEnd != initIter) {
                _mat[i][j] = *initIter;
                ++initIter;
            } else {
                _mat[i][j] = value_type();
            }
        }
    }
#endif
}

template<int D, class V>
template<class T>
inline MyMatrix<D, D, V>&
MyMatrix<D, D, V>::operator=(const MyMatrix<D, D, T> &other) {
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

template<int D, class V>
template<class T>
inline MyMatrix<D, D, V>&
MyMatrix<D, D, V>::operator=(const MyMatrix<D, D, T> &&other) {
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

template<int D, class V>
template<class T>
inline MyMatrix<D, D, V>&
MyMatrix<D, D, V>::operator=(const std::initializer_list<T> &il) {
#ifdef ENABLE_TEMPLATE_META
        MatrixAssignInitializer(*this, il.begin(), il.end());
#else
        auto initIter(il.begin());
        auto initEnd(il.end());
        for(int i = 0; i != _row; ++i) {
            for(int j = 0; j != _column; ++j) {
                if(initEnd == initIter) {
                    break;
                }
                _mat[i][j] = *initIter;
                ++initIter;
            }
        }
#endif
        return *this;
}

template<int D, class V>
template<class T>
inline MyMatrix<D, D, V>&
MyMatrix<D, D, V>::operator+=(const MyMatrix<D, D, T> &other) {
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

template<int D, class V>
template<class T>
inline MyMatrix<D, D, V>&
MyMatrix<D, D, V>::operator-=(const MyMatrix<D, D, T> &other) {
#ifdef ENABLE_TEMPLATE_META
    MatrixMinusMatrix(*this, other);
#else
    for(int i = 0; i != dimension(); ++i) {
        for(int j = 0; j != dimension(); ++j) {
            _mat[i][j] -= other.valueAt(i, j);
        }
    }
#endif
    return *this;
}

template<int D, class V>
template<class T>
inline MyMatrix<D, D, V>&
MyMatrix<D, D, V>::operator*=(const T &value) {
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

// ------------------------------ matrix operator ------------------------------- //

template<int R, int C, class V, class T>
inline MyMatrix<R, C, V> operator+(const MyMatrix<R, C, V> &mat1,
                                   const MyMatrix<R, C, T> &mat2) {
    MyMatrix<R, C, V> retMat(mat1);
    retMat += mat2;
    return retMat;
}

template<int R, int C, class V, class T>
inline MyMatrix<R, C, V> operator-(const MyMatrix<R, C, V> &mat1,
                                   const MyMatrix<R, C, T> &mat2) {
    MyMatrix<R, C, V> retMat(mat1);
    retMat -= mat2;
    return retMat;
}

template<int R, int C, class V, class T>
inline MyMatrix<R, C, V> operator*(const MyMatrix<R, C, V> &mat, const T &val) {
    MyMatrix<R, C, V> retMat(mat);
    retMat *= val;
    return retMat;
}

template<int R, int C, class V, class T>
inline MyMatrix<R, C, V> operator*(const T &val, const MyMatrix<R, C, V> &mat) {
    MyMatrix<R, C, V> retMat(mat);
    retMat *= val;
    return retMat;
}

template<int R, int C, int N, class V, class T>
inline MyMatrix<R, C, V> operator*(const MyMatrix<R, N, V> &mat1,
                                   const MyMatrix<N, C, T> &mat2) {
    MyMatrix<R, C, V> retMat;
#ifdef ENABLE_TEMPLATE_META
    MatrixMultiplyMatrix(retMat, mat1, mat2);
#else
    for(int i = 0; i != R; ++i) {
        for(int j = 0; j != C; ++j) {
            for(int k = 0; k != N; ++k) {
                retMat.valueAt(i, j) += mat1.valueAt(i, k) * mat2.valueAt(k, j);
            }
        }
    }
#endif
    return retMat;
}

// ------------------------------- matrix operation ----------------------------------------- //

template<int R, int C, class V>
inline MyMatrix<R, C, V>&
zeroMatrix(MyMatrix<R, C, V> &mat, const V &zeroValue) {
#ifdef ENABLE_TEMPLATE_META
    MatrixAssignValue(mat, zeroValue);
#else
    for(int i = 0; i != R; ++i) {
        for(int j = 0; j != C; ++j) {
            retMat.valueAt(i, j) = zeroValue;
        }
    }
#endif
    return mat;
}

template<int D, class V>
inline MyMatrix<D, D, V>&
identityMatrix(MyMatrix<D, D, V> &mat,
               const V &identityValue,
               const V &zeroValue) {
#ifdef ENABLE_TEMPLATE_META
    SquareMatrixIdentity(mat, identityValue, zeroValue);
#else
    for(int i = 0; i != D; ++i) {
        for(int j = 0; j != D; ++j) {
            retMat.valueAt(i, j) = (i == j) ? identityValue : zeroValue;
        }
    }
#endif
    return mat;
}

template<int R, int C, class V>
inline MyMatrix<R, C, V>
transposeMatrix(const MyMatrix<R, C, V> &mat) {
    MyMatrix<C, R, V> retMat;
#ifdef ENABLE_TEMPLATE_META
    MatrixTranspose(retMat, mat);
#else
    for(int i = 0; i != C; ++i) {
        for(int j = 0; j != R; ++j) {
            retMat.valueAt(i, j) = mat.valueAt(j, i);
        }
    }
#endif
    return retMat;
}

template<int D, class V>
inline MyMatrix<D, D, V>&
transposeMatrix(MyMatrix<D, D, V> &mat) {
#ifdef ENABLE_TEMPLATE_META
    SquareMatrixTranspose(mat);
#else
    V tmp;
    for(int i = 0; i != D; ++i) {
        for(int j = i + 1; j != D; ++j) {
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

template<int R, int C, class V>
inline MyMatrix<R, C, V>&
swapMatrixRow(MyMatrix<R, C, V> &mat, int a, int b) {
#ifdef ENABLE_TEMPLATE_META
    MatrixSwapRow(mat, a, b);
#else
    V tmp;
    for(int i = 0; i != C; ++i) {
            tmp = mat.valueAt(a, i);
            mat.valueAt(a, i) = mat.valueAt(b, i);
            mat.valueAt(b, i) = tmp;
    }
#endif
    return mat;
}

template<int R, int C, class V, class T>
inline MyMatrix<R, C, V>&
multiplyMatrixRow(MyMatrix<R, C, V> &mat, int a, const T &multiple) {
#ifdef ENABLE_TEMPLATE_META
    MatrixMultiplyRow(mat, a, multiple);
#else
    for(int i = 0; i != C; ++i) {
        mat.valueAt(a, i) *= multiple;
    }
#endif
    return mat;
}

template<int R, int C, class V, class T>
inline MyMatrix<R, C, V>&
subtractMatrixRow(MyMatrix<R, C, V> &mat,  int a,
                  int b, const T &multiple) {
#ifdef ENABLE_TEMPLATE_META
    MatrixSubtractRow(mat, a, b, multiple);
#else
    for(int i = 0; i != C; ++i) {
        mat.valueAt(a, i) -= mat.valueAt(b, i) * multiple;
    }
#endif
    return mat;
}

template<int R, int C, class V>
inline MyMatrix<R, C, V>&
swapMatrixColumn(MyMatrix<R, C, V> &mat, int a, int b) {
#ifdef ENABLE_TEMPLATE_META
    MatrixSwapColumn(mat, a, b);
#else
    V tmp;
    for(int i = 0; i != R; ++i) {
        tmp = mat.valueAt(i, a);
        mat.valueAt(i, a) = mat.valueAt(i, b);
        mat.valueAt(i, b) = tmp;
    }
#endif
    return mat;
}

template<int R, int C, class V, class T>
inline MyMatrix<R, C, V>&
multiplyMatrixColumn(MyMatrix<R, C, V> &mat, int a, const T &multiple) {
#ifdef ENABLE_TEMPLATE_META
    MatrixMultiplyColumn(mat, a, multiple);
#else
    for(int i = 0; i != R; ++i) {
        mat.valueAt(i, a) *= multiple;
    }
#endif
    return mat;
}

template<int R, int C, class V, class T>
inline MyMatrix<R, C, V>&
subtractMatrixColumn(MyMatrix<R, C, V> &mat, int a,
                     int b, const T &multiple) {
#ifdef ENABLE_TEMPLATE_META
    MatrixSubtractColumn(mat, a, b, multiple);
#else
    for(int i = 0; i != R; ++i) {
        mat.valueAt(i, a) -= mat.valueAt(i, b) * multiple;
    }
#endif
    return mat;
}

// ------------------------------- elementary transformation  ----------------------------------------- //

template<int R, int C, class V>
inline MyMatrix<R, C, V>&
simplifyMatrix(MyMatrix<R, C, V> &mat) {
#ifdef ENABLE_TEMPLATE_META
//#if R * C < 1024
    SimplifyMatrixBySubtract(mat);
//#endif
#else
    constexpr int order = R < C ? R : C;
    
    if(1 == order) {
        return mat;
    }
    
    bool gua[order] = {false};
    typename MyMatrix<R, C, V>::value_type det;
    
    for(int r = 0; r != order; ++r) {
        for(int t = 0; t != R; ++t) {
            if(gua[t]) {
                continue;
            }
            if(!mat.zeroAt(t, r)) {
                det = MyMatrix<R, C, V>::identityValue()/mat.valueAt(t, r);
                for(int p = 0; p != R; ++p) {
                    if(p == t) {
                        continue;
                    }
                    MatrixSubtractRow(mat, p, t, mat.valueAt(p, r) * det);
                }
                gua[t] = true;
            }
        }
    }
#endif
    return mat;
}

MINE_NAMESPACE_END
