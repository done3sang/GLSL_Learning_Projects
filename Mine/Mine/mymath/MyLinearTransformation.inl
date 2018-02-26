//
//  MyLinearTransformation.inl
//  Mine
//
//  Created by xy on 24/02/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#include "MyVector.hpp"
#include "MyMatrix.hpp"
#include "MyCoordinate.hpp"

MINE_NAMESPACE_BEGIN

namespace {
    // swap matrix row
    template<class M, int D, int I>
    struct LinearMatrixSwapRowImpl {
        enum {
            Continue = I != D - 1,
            NextI = I + 1
        };
        
        static FORCEINLINE void eval(M &mat, int x, int y, int index) {
            MINE_ASSERT2(index <= D, "MatrixSwapRowImpl, index out of range");
            float temp = mat.valueAt(x, index);
            mat.valueAt(x, index) = mat.valueAt(y, index);
            mat.valueAt(y, index) = temp;
            ++index;
            if(D != index) {
                LinearMatrixSwapRowImpl<M, D * Continue, NextI * Continue>::eval(mat, x, y, index);
            }
        }
    };
    
    template<class M>
    struct LinearMatrixSwapRowImpl<M, 0, 0> {
        static FORCEINLINE void eval(M&, int, int, int) {}
    };
    
    template<class M, int D>
    FORCEINLINE void linearMatrixSwapRow(M &mat, int x, int y, int startIndex) {
        LinearMatrixSwapRowImpl<M, D, 0>::eval(mat, x, y, startIndex);
    }
    
    // multiply matrix row
    template<class M, int D, int I>
    struct LinearMatrixMultiplyRowImpl {
        enum {
            Continue = I != D - 1,
            NextI = I + 1
        };
        
        static FORCEINLINE void eval(M &mat, int x, float multiple, int index) {
            MINE_ASSERT2(index <= D, "MatrixMultiplyRowImpl, index out of range");
            mat.valueAt(x, index) *= multiple;
            ++index;
            if(D != index) {
                LinearMatrixMultiplyRowImpl<M, D * Continue,
                NextI * Continue>::eval(mat, x, multiple, index);
            }
        }
    };
    
    template<class M>
    struct LinearMatrixMultiplyRowImpl<M, 0, 0> {
        static FORCEINLINE void eval(M&, int, float, int) {}
    };
    
    template<class M, int D>
    FORCEINLINE void linearMatrixMultiplyRow(M &mat, int x, float multiple, int startIndex) {
        LinearMatrixMultiplyRowImpl<M, D, 0>::eval(mat, x, multiple, startIndex);
    }
    
    // substract matrix row, x -= y * multiple
    template<class M, int D, int I>
    struct LinearMatrixSubstractRowImpl {
        enum {
            Continue = I != D - 1,
            NextI = I + 1
        };
        
        static float temp;
        
        static FORCEINLINE void eval(M &mat, int x, int y, float multiple, int index) {
            MINE_ASSERT2(index <= D, "MatrixSubstractRowImpl, index out of range");
            mat.valueAt(x, index) -= mat.valueAt(y, index) * multiple;
            ++index;
            if(D != index) {
                LinearMatrixSubstractRowImpl<M, D * Continue,
                NextI * Continue>::eval(mat, x, y, multiple, index);
            }
        }
    };
    
    template<class M>
    struct LinearMatrixSubstractRowImpl<M, 0, 0> {
        static FORCEINLINE void eval(M&, int, int, float, int) {}
    };
    
    template<class M, int D>
    FORCEINLINE void linearMatrixSubstractRow(M &mat,
                                              int x,
                                              int y,
                                              float multiple,
                                              int startIndex) {
        LinearMatrixSubstractRowImpl<M, D, 0>::eval(mat, x, y, multiple, startIndex);
    }
    
    // swap matrix column
    template<class M, int D, int I>
    struct LinearMatrixSwapColumnImpl {
        enum {
            Continue = I != D - 1,
            NextI = I + 1
        };
        
        static FORCEINLINE void eval(M &mat, int x, int y, int index) {
            MINE_ASSERT2(index <= D, "MatrixSwapColumnImpl, index out of range");
            float temp = mat.valueAt(index, x);
            mat.valueAt(index, x) = mat.valueAt(index, y);
            mat.valueAt(index, y) = temp;
            ++index;
            if(D != index) {
                LinearMatrixSwapColumnImpl<M, D * Continue,
                NextI * Continue>::eval(mat, x, y, index);
            }
        }
    };
    
    template<class M>
    struct LinearMatrixSwapColumnImpl<M, 0, 0> {
        static FORCEINLINE void eval(M&, int, int, int) {}
    };
    
    template<class M, int D>
    FORCEINLINE void linearMatrixSwapColumn(M &mat, int x, int y, int startIndex) {
        LinearMatrixSwapColumnImpl<M, D, 0>::eval(mat, x, y, startIndex);
    }
    
    // multiply matrix column
    template<class M, int D, int I>
    struct LinearMatrixMultiplyColumnImpl {
        enum {
            Continue = I != D - 1,
            NextI = I + 1
        };
        
        static FORCEINLINE void eval(M &mat, int x, float multiple, int index) {
            MINE_ASSERT2(index <= D, "MatrixMultiplyColumnImpl, index out of range");
            mat.valueAt(index, x) *= multiple;
            ++index;
            if(D != index) {
                LinearMatrixMultiplyColumnImpl<M, D * Continue,
                NextI * Continue>::eval(mat, x, multiple, index);
            }
        }
    };
    
    template<class M>
    struct LinearMatrixMultiplyColumnImpl<M, 0, 0> {
        static FORCEINLINE void eval(M&, int, float, int) {}
    };
    
    template<class M, int D>
    FORCEINLINE void linearMatrixMultiplyColumn(M &mat, int x, float multiple, int startIndex) {
        LinearMatrixMultiplyColumnImpl<M, D, 0>::eval(mat, x, multiple, startIndex);
    }
    
    // substract matrix column, x -= y * multiple
    template<class M, int D, int I>
    struct LinearMatrixSubstractColumnImpl {
        enum {
            Continue = I != D - 1,
            NextI = I + 1
        };
        
        static FORCEINLINE void eval(M &mat, int x, int y, float multiple, int index) {
            MINE_ASSERT2(index <= D, "MatrixSubstractColumnImpl, index out of range");
            mat.valueAt(x, index) -= mat.valueAt(y, index) * multiple;
            ++index;
            if(D != index) {
                LinearMatrixSubstractColumnImpl<M, D * Continue,
                NextI * Continue>::eval(mat, x, y, multiple, index);
            }
        }
    };
    
    template<class M>
    struct LinearMatrixSubstractColumnImpl<M, 0, 0> {
        static FORCEINLINE void eval(M&, int, int, float, int) {}
    };
    
    template<class M, int D>
    FORCEINLINE void linearMatrixSubstractColumn(M &mat,
                                                 int x,
                                                 int y,
                                                 float multiple,
                                                 int startIndex) {
        LinearMatrixSubstractColumnImpl<M, D, 0>::eval(mat, x, y, multiple, startIndex);
    }
    
    // inverse matrix by gauss
    template<class M, int D, int C, int I>
    struct LinearMatrixInverseByGaussRowInnerImpl {
        enum {
            Continue = I != D - 1,
            NextI = I + 1
        };
        
        static FORCEINLINE void eval(M &mat, M &invMat) {
            if(I != C && !MyMathUtil::zero(mat.valueAt(I, C))) {
                linearMatrixSubstractRow<M, D>(mat, I, C, mat.valueAt(I, C), C);
                linearMatrixSubstractRow<M, D>(invMat, I, C, mat.valueAt(I, C), 0);
            }
            LinearMatrixInverseByGaussRowInnerImpl<M, Continue * D,
            Continue * C, Continue * NextI>::eval(mat, invMat);
        }
    };
    
    template<class M>
    struct LinearMatrixInverseByGaussRowInnerImpl<M, 0, 0, 0> {
        static FORCEINLINE void eval(M&, M&) {}
    };
    
    template<class M, int D, int C, int I>
    struct LinearMatrixInverseByGaussRowImpl {
        enum {
            Continue = I != D - 1,
            NextI = I + 1
        };
        
        static float dem;
        
        static FORCEINLINE void eval(M &mat, M &invMat, bool &inversible) {
            if(!MyMathUtil::zero(mat.valueAt(I, C))) {
                dem = 1.0f/mat.valueAt(I, C);
                if(!MyMathUtil::equal(dem, 1.0f)) {
                    linearMatrixMultiplyRow<M, D>(mat, I, dem, C);
                    linearMatrixMultiplyRow<M, D>(invMat, I, dem, 0);
                }
                if(I != C) {
                    linearMatrixSwapRow<M, D>(mat, I, C, C);
                    linearMatrixSwapRow<M, D>(invMat, I, C, 0);
                }
                LinearMatrixInverseByGaussRowInnerImpl<M, D, C, 0>::eval(mat, invMat);
                inversible = true;
                return;
            }
            LinearMatrixInverseByGaussRowImpl<M, Continue * D,
            Continue * C, Continue * NextI>::eval(mat, invMat, inversible);
        }
    };
    
    template<class M, int D, int C, int I>
    float LinearMatrixInverseByGaussRowImpl<M, D, C, I>::dem(0.0f);
    
    template<class M>
    struct LinearMatrixInverseByGaussRowImpl<M, 0, 0, 0> {
        static FORCEINLINE void eval(M &mat, M &invMat, bool &inversible) {
            inversible = false;
        }
    };
    
    template<class M, int D, int I>
    struct LinearMatrixInverseByGaussImpl {
        enum {
            Continue = I != D - 1,
            NextI = I + 1
        };
        
        static FORCEINLINE void eval(M &mat, M &invMat, bool &inversible) {
            LinearMatrixInverseByGaussRowImpl<M, D, I, I>::eval(mat, invMat, inversible);
            if(inversible) {
                LinearMatrixInverseByGaussImpl<M, Continue * D,
                Continue * NextI>::eval(mat, invMat, inversible);
            }
        }
    };
    
    template<class M>
    struct LinearMatrixInverseByGaussImpl<M, 0, 0> {
        static FORCEINLINE void eval(M &mat, M &invMat, bool &inversible) {}
    };
    
    template<class M>
    struct LinearMatrixInverseByGaussImpl<M, 1, 0> {
        static FORCEINLINE void eval(M &mat, M &invMat, bool &inversible) {
            if(!MyMathUtil::zero(mat.valueAt(0, 0))) {
                invMat.valueAt(0, 0) = 1.0f/mat.valueAt(0, 0);
                inversible = true;
            } else {
                inversible = false;
            }
        }
    };
    
    template<class M, int D>
    FORCEINLINE void linearMatrixInverseByGauss(M &implMat, M &invMat, bool &inversible) {
        LinearMatrixInverseByGaussImpl<M, D, 0>::eval(implMat, invMat, inversible);
    }
}

// MyLinearTransformation implementation

FORCEINLINE float MyLinearTransformation::magnitudeVector(const MyFVector2 &vec) {
    return MyMathUtil::sqrt(magnitudeSquareVector(vec));
}

FORCEINLINE float MyLinearTransformation::magnitudeSquareVector(const MyFVector2 &vec) {
    return vec.x * vec.x + vec.y * vec.y;
}

FORCEINLINE float MyLinearTransformation::magnitudeVector(const MyFVector3 &vec) {
    return MyMathUtil::sqrt(magnitudeSquareVector(vec));
}

FORCEINLINE float MyLinearTransformation::magnitudeSquareVector(const MyFVector3 &vec) {
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

FORCEINLINE float MyLinearTransformation::magnitudeVector(const MyFVector4 &vec) {
    return MyMathUtil::sqrt(magnitudeSquareVector(vec));
}

FORCEINLINE float MyLinearTransformation::magnitudeSquareVector(const MyFVector4 &vec) {
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w;
}

FORCEINLINE MyFVector2 MyLinearTransformation::normalizeVector(const MyFVector2 &vec) {
    return vec/magnitudeVector(vec);
}

FORCEINLINE MyFVector2& MyLinearTransformation::normalizeVectorSelf(MyFVector2 &vec) {
    vec /= magnitudeVector(vec);
    return vec;
}

FORCEINLINE MyFVector3 MyLinearTransformation::normalizeVector(const MyFVector3 &vec) {
    return vec/magnitudeVector(vec);
}

FORCEINLINE MyFVector3& MyLinearTransformation::normalizeVectorSelf(MyFVector3 &vec) {
    vec /= magnitudeVector(vec);
    return vec;
}

FORCEINLINE MyFVector4 MyLinearTransformation::normalizeVector(const MyFVector4 &vec) {
    return vec/magnitudeVector(vec);
}

FORCEINLINE MyFVector4& MyLinearTransformation::normalizeVectorSelf(MyFVector4 &vec) {
    vec /= magnitudeVector(vec);
    return vec;
}

FORCEINLINE float MyLinearTransformation::dotProduct(const MyFVector2 &a,
                                                     const MyFVector2 &b) {
    return a.x * b.x + a.y * b.y;
}

FORCEINLINE float MyLinearTransformation::dotProduct(const MyFVector3 &a,
                                                     const MyFVector3 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

FORCEINLINE float MyLinearTransformation::dotProduct(const MyFVector4 &a,
                                                     const MyFVector4 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

FORCEINLINE float MyLinearTransformation::radiusVector(const MyFVector2 &a,
                                                       const MyFVector2 &b) {
    float ab = magnitudeVector(a) * magnitudeVector(b);
    return MyMathUtil::zero(ab) ? MyMathUtil::acos(dotProduct(a, b)/ab) : MyMathUtil::kMathPIOver2;
}

FORCEINLINE float MyLinearTransformation::radiusVector(const MyFVector3 &a,
                                                       const MyFVector3 &b) {
    float ab = magnitudeVector(a) * magnitudeVector(b);
    return MyMathUtil::zero(ab) ? MyMathUtil::acos(dotProduct(a, b)/ab) : MyMathUtil::kMathPIOver2;
}

FORCEINLINE float MyLinearTransformation::radiusVector(const MyFVector4 &a,
                                                       const MyFVector4 &b) {
    float ab = magnitudeVector(a) * magnitudeVector(b);
    return MyMathUtil::zero(ab) ? MyMathUtil::acos(dotProduct(a, b)/ab) : MyMathUtil::kMathPIOver2;
}

FORCEINLINE MyFVector3 MyLinearTransformation::projectVector(const MyFVector3 &a,
                                                             const MyFVector3 &b) {
    float k = dotProduct(a, b)/magnitudeSquareVector(b);
    return MyFVector3(b.x * k, b.y * k, b.z * k);
}

FORCEINLINE MyFVector3& MyLinearTransformation::projectVectorSelf(MyFVector3 &a,
                                                                  const MyFVector3 &b) {
    float k = dotProduct(a, b)/magnitudeSquareVector(b);
    a.x = b.x * k;
    a.y = b.y * k;
    a.z = b.z * k;
    return a;
}

FORCEINLINE MyFVector3 MyLinearTransformation::projectNormalizedVector(const MyFVector3 &a,
                                                                       const MyFVector3 &b) {
    float k = dotProduct(a, b);
    return MyFVector3(b.x * k, b.y * k, b.z * k);
}

FORCEINLINE MyFVector3& MyLinearTransformation::projectNormalizedVectorSelf(MyFVector3 &a,
                                                                            const MyFVector3 &b) {
    float k = dotProduct(a, b);
    a.x = b.x * k;
    a.y = b.y * k;
    a.z = b.z * k;
    return a;
}

FORCEINLINE void MyLinearTransformation::zeroMatrix(MyFMatrix2 &mat) {
    mat.valueAt(0, 0) = 0.0f; mat.valueAt(0, 1) = 0.0f;
    mat.valueAt(1, 0) = 0.0f; mat.valueAt(1, 1) = 0.0f;
}

FORCEINLINE void MyLinearTransformation::identityMatrix(MyFMatrix2 &mat) {
    mat.valueAt(0, 0) = 1.0f; mat.valueAt(0, 1) = 0.0f;
    mat.valueAt(1, 0) = 0.0f; mat.valueAt(1, 1) = 1.0f;
}

FORCEINLINE MyFMatrix2 MyLinearTransformation::transposeMatrix(const MyFMatrix2 &mat) {
    return MyFMatrix2(mat.valueAt(0, 0), mat.valueAt(1, 0),
                      mat.valueAt(0, 1), mat.valueAt(1, 1));
}

FORCEINLINE MyFMatrix2& MyLinearTransformation::transposeMatrixSelf(MyFMatrix2 &mat) {
    float tmp = mat.valueAt(0, 1);
    mat.valueAt(0, 1) = mat.valueAt(1, 0);
    mat.valueAt(1, 0) = tmp;
    return mat;
}

FORCEINLINE bool MyLinearTransformation::inverseMatrix(MyFMatrix2 &mat,
                                                       MyFMatrix2 &invMat) {
    return metaInverseMatrix<MyFMatrix2, 2>(mat, invMat);
}

FORCEINLINE bool MyLinearTransformation::inverseMatrixSelf(MyFMatrix2 &mat) {
    return metaInverseMatrixSelf<MyFMatrix2, 2>(mat);
}

FORCEINLINE void MyLinearTransformation::zeroMatrix(MyFMatrix3 &mat) {
    mat.valueAt(0, 0) = 0.0f; mat.valueAt(0, 1) = 0.0f; mat.valueAt(0, 2) = 0.0f;
    mat.valueAt(1, 0) = 0.0f; mat.valueAt(1, 1) = 0.0f; mat.valueAt(1, 1) = 0.0f;
    mat.valueAt(2, 0) = 0.0f; mat.valueAt(2, 1) = 0.0f; mat.valueAt(2, 2) = 0.0f;
}

FORCEINLINE void MyLinearTransformation::identityMatrix(MyFMatrix3 &mat) {
    mat.valueAt(0, 0) = 1.0f; mat.valueAt(0, 1) = 0.0f; mat.valueAt(0, 2) = 0.0f;
    mat.valueAt(1, 0) = 0.0f; mat.valueAt(1, 1) = 1.0f; mat.valueAt(1, 2) = 0.0f;
    mat.valueAt(2, 0) = 0.0f; mat.valueAt(2, 1) = 0.0f; mat.valueAt(2, 2) = 1.0f;
}

FORCEINLINE MyFMatrix3 MyLinearTransformation::transposeMatrix(const MyFMatrix3 &mat) {
    return MyFMatrix3(mat.valueAt(0, 0), mat.valueAt(1, 0), mat.valueAt(2, 0),
                      mat.valueAt(0, 1), mat.valueAt(1, 1), mat.valueAt(2, 1),
                      mat.valueAt(0, 2), mat.valueAt(1, 2), mat.valueAt(2, 2));
}

FORCEINLINE MyFMatrix3& MyLinearTransformation::transposeMatrixSelf(MyFMatrix3 &mat) {
    float tmp = mat.valueAt(0, 1);
    mat.valueAt(0, 1) = mat.valueAt(1, 0);
    mat.valueAt(1, 0) = tmp;
    tmp = mat.valueAt(0, 2);
    mat.valueAt(0, 2) = mat.valueAt(2, 0);
    mat.valueAt(2, 0) = tmp;
    tmp = mat.valueAt(1, 2);
    mat.valueAt(1, 2) = mat.valueAt(2, 1);
    mat.valueAt(2, 1) = tmp;
    return mat;
}

FORCEINLINE bool MyLinearTransformation::inverseMatrix(MyFMatrix3 &mat,
                                                       MyFMatrix3 &invMat) {
    return metaInverseMatrix<MyFMatrix3, 3>(mat, invMat);
}

FORCEINLINE bool MyLinearTransformation::inverseMatrixSelf(MyFMatrix3 &mat) {
    return metaInverseMatrixSelf<MyFMatrix3, 3>(mat);
}

FORCEINLINE void MyLinearTransformation::zeroMatrix(MyFMatrix4 &mat) {
    mat.valueAt(0, 0) = 0.0f; mat.valueAt(0, 1) = 0.0f; mat.valueAt(0, 2) = 0.0f; mat.valueAt(0, 3) = 0.0f;
    mat.valueAt(1, 0) = 0.0f; mat.valueAt(1, 1) = 0.0f; mat.valueAt(1, 2) = 0.0f; mat.valueAt(1, 3) = 0.0f;
    mat.valueAt(2, 0) = 0.0f; mat.valueAt(2, 1) = 0.0f; mat.valueAt(2, 2) = 0.0f; mat.valueAt(2, 3) = 0.0f;
    mat.valueAt(3, 0) = 0.0f; mat.valueAt(3, 1) = 0.0f; mat.valueAt(3, 2) = 0.0f; mat.valueAt(3, 3) = 0.0f;
}

FORCEINLINE void MyLinearTransformation::identityMatrix(MyFMatrix4 &mat) {
    mat.valueAt(0, 0) = 1.0f; mat.valueAt(0, 1) = 0.0f; mat.valueAt(0, 2) = 0.0f; mat.valueAt(0, 3) = 0.0f;
    mat.valueAt(1, 0) = 0.0f; mat.valueAt(1, 1) = 1.0f; mat.valueAt(1, 2) = 0.0f; mat.valueAt(1, 3) = 0.0f;
    mat.valueAt(2, 0) = 0.0f; mat.valueAt(2, 1) = 0.0f; mat.valueAt(2, 2) = 1.0f; mat.valueAt(2, 3) = 0.0f;
    mat.valueAt(3, 0) = 0.0f; mat.valueAt(3, 1) = 0.0f; mat.valueAt(3, 2) = 0.0f; mat.valueAt(3, 3) = 1.0f;
}

FORCEINLINE MyFMatrix4 MyLinearTransformation::transposeMatrix(const MyFMatrix4 &mat) {
    return MyFMatrix4(mat.valueAt(0, 0), mat.valueAt(1, 0), mat.valueAt(2, 0), mat.valueAt(3, 0),
                      mat.valueAt(0, 1), mat.valueAt(1, 1), mat.valueAt(2, 1), mat.valueAt(3, 1),
                      mat.valueAt(0, 2), mat.valueAt(1, 2), mat.valueAt(2, 2), mat.valueAt(3, 2),
                      mat.valueAt(0, 3), mat.valueAt(1, 3), mat.valueAt(2, 3), mat.valueAt(3, 3));
}

FORCEINLINE MyFMatrix4& MyLinearTransformation::transposeMatrixSelf(MyFMatrix4 &mat) {
    float tmp = mat.valueAt(0, 1);
    mat.valueAt(0, 1) = mat.valueAt(1, 0);
    mat.valueAt(1, 0) = tmp;
    tmp = mat.valueAt(0, 2);
    mat.valueAt(0, 2) = mat.valueAt(2, 0);
    mat.valueAt(2, 0) = tmp;
    tmp = mat.valueAt(0, 3);
    mat.valueAt(0, 3) = mat.valueAt(3, 0);
    mat.valueAt(3, 0) = tmp;
    tmp = mat.valueAt(1, 2);
    mat.valueAt(1, 2) = mat.valueAt(2, 1);
    mat.valueAt(2, 1) = tmp;
    tmp = mat.valueAt(1, 3);
    mat.valueAt(1, 3) = mat.valueAt(3, 1);
    mat.valueAt(3, 1) = tmp;
    tmp = mat.valueAt(2, 3);
    mat.valueAt(2, 3) = mat.valueAt(3, 2);
    mat.valueAt(3, 2) = tmp;
    return mat;
}

FORCEINLINE bool MyLinearTransformation::inverseMatrix(MyFMatrix4 &mat,
                                                       MyFMatrix4 &invMat) {
    return metaInverseMatrix<MyFMatrix4, 4>(mat, invMat);
}

FORCEINLINE bool MyLinearTransformation::inverseMatrixSelf(MyFMatrix4 &mat) {
    return metaInverseMatrixSelf<MyFMatrix4, 4>(mat);
}

template<class M, int D>
FORCEINLINE bool MyLinearTransformation::metaInverseMatrix(M &mat, M &invMat) {
    M implMat(mat);
    bool inversible;
    identityMatrix(invMat);
    linearMatrixInverseByGauss<M, D>(implMat, invMat, inversible);
    return inversible;
}

template<class M, int D>
FORCEINLINE bool MyLinearTransformation::metaInverseMatrixSelf(M &mat) {
    M implMat(mat), invMat(1.0f);
    bool inversible;
    linearMatrixInverseByGauss<M, D>(implMat, invMat, inversible);
    if(inversible) {
        mat = invMat;
    }
    return inversible;
}

FORCEINLINE void MyLinearTransformation::swapMatrixRow(MyFMatrix2 &mat,
                                                       int x,
                                                       int y,
                                                       int startIndex) {
    linearMatrixSwapRow<MyFMatrix2, 2>(mat, x, y, startIndex);
}

FORCEINLINE void MyLinearTransformation::multiplyMatrixRow(MyFMatrix2 &mat,
                                                           int x,
                                                           float multiple,
                                                           int startIndex) {
    linearMatrixMultiplyRow<MyFMatrix2, 2>(mat, x, multiple, startIndex);
}

FORCEINLINE void MyLinearTransformation::substractMatrixRow(MyFMatrix2 &mat,
                                                            int x,
                                                            int y,
                                                            float multiple,
                                                            int startIndex) {
    linearMatrixSubstractRow<MyFMatrix2, 2>(mat, x, y, multiple, startIndex);
}

FORCEINLINE void MyLinearTransformation::swapMatrixColumn(MyFMatrix2 &mat,
                                                          int x,
                                                          int y,
                                                          int startIndex) {
    linearMatrixSwapColumn<MyFMatrix2, 2>(mat, x, y, startIndex);
}

FORCEINLINE void MyLinearTransformation::multiplyMatrixColumn(MyFMatrix2 &mat,
                                                              int x,
                                                              float multiple,
                                                              int startIndex) {
    linearMatrixMultiplyColumn<MyFMatrix2, 2>(mat, x, multiple, startIndex);
}

FORCEINLINE void MyLinearTransformation::substractMatrixColumn(MyFMatrix2 &mat,
                                                               int x,
                                                               int y,
                                                               float multiple,
                                                               int startIndex) {
    linearMatrixSubstractColumn<MyFMatrix2, 2>(mat, x, y, multiple, startIndex);
}

FORCEINLINE void MyLinearTransformation::swapMatrixRow(MyFMatrix3 &mat,
                                                       int x,
                                                       int y,
                                                       int startIndex) {
    linearMatrixSwapRow<MyFMatrix3, 3>(mat, x, y, startIndex);
}

FORCEINLINE void MyLinearTransformation::multiplyMatrixRow(MyFMatrix3 &mat,
                                                           int x,
                                                           float multiple,
                                                           int startIndex) {
    linearMatrixMultiplyRow<MyFMatrix3, 3>(mat, x, multiple, startIndex);
}

FORCEINLINE void MyLinearTransformation::substractMatrixRow(MyFMatrix3 &mat,
                                                            int x,
                                                            int y,
                                                            float multiple,
                                                            int startIndex) {
    linearMatrixSubstractRow<MyFMatrix3, 3>(mat, x, y, multiple, startIndex);
}

FORCEINLINE void MyLinearTransformation::swapMatrixColumn(MyFMatrix3 &mat,
                                                          int x,
                                                          int y,
                                                          int startIndex) {
    linearMatrixSwapColumn<MyFMatrix3, 3>(mat, x, y, startIndex);
}

FORCEINLINE void MyLinearTransformation::multiplyMatrixColumn(MyFMatrix3 &mat,
                                                              int x,
                                                              float multiple,
                                                              int startIndex) {
    linearMatrixMultiplyColumn<MyFMatrix3, 3>(mat, x, multiple, startIndex);
}

FORCEINLINE void MyLinearTransformation::substractMatrixColumn(MyFMatrix3 &mat,
                                                               int x,
                                                               int y,
                                                               float multiple,
                                                               int startIndex) {
    linearMatrixSubstractColumn<MyFMatrix3, 3>(mat, x, y, multiple, startIndex);
}

FORCEINLINE void MyLinearTransformation::swapMatrixRow(MyFMatrix4 &mat,
                                                       int x,
                                                       int y,
                                                       int startIndex) {
    linearMatrixSwapRow<MyFMatrix4, 4>(mat, x, y, startIndex);
}

FORCEINLINE void MyLinearTransformation::multiplyMatrixRow(MyFMatrix4 &mat,
                                                           int x,
                                                           float multiple,
                                                           int startIndex) {
    linearMatrixMultiplyRow<MyFMatrix4, 4>(mat, x, multiple, startIndex);
}

FORCEINLINE void MyLinearTransformation::substractMatrixRow(MyFMatrix4 &mat,
                                                            int x,
                                                            int y,
                                                            float multiple,
                                                            int startIndex) {
    linearMatrixSubstractRow<MyFMatrix4, 4>(mat, x, y, multiple, startIndex);
}

FORCEINLINE void MyLinearTransformation::swapMatrixColumn(MyFMatrix4 &mat,
                                                          int x,
                                                          int y,
                                                          int startIndex) {
    linearMatrixSwapColumn<MyFMatrix4, 4>(mat, x, y, startIndex);
}

FORCEINLINE void MyLinearTransformation::multiplyMatrixColumn(MyFMatrix4 &mat,
                                                              int x,
                                                              float multiple,
                                                              int startIndex) {
    linearMatrixMultiplyColumn<MyFMatrix4, 4>(mat, x, multiple, startIndex);
}

FORCEINLINE void MyLinearTransformation::substractMatrixColumn(MyFMatrix4 &mat,
                                                               int x,
                                                               int y,
                                                               float multiple,
                                                               int startIndex) {
    linearMatrixSubstractColumn<MyFMatrix4, 4>(mat, x, y, multiple, startIndex);
}

FORCEINLINE MyFVector2& MyLinearTransformation::transformVector(const MyFMatrix2 &mat,
                                                                MyFVector2 &vec) {
    float y = mat.valueAt(1, 0) * vec.x + mat.valueAt(1, 1) * vec.y;
    vec.x = mat.valueAt(0, 0) * vec.x + mat.valueAt(0, 1) * vec.y;
    vec.y = y;
    return vec;
}

FORCEINLINE MyFVector3& MyLinearTransformation::transformVector(const MyFMatrix3 &mat,
                                                                MyFVector3 &vec) {
    float y = mat.valueAt(1, 0) * vec.x + mat.valueAt(1, 1) * vec.y + mat.valueAt(1, 2) * vec.z;
    float z = mat.valueAt(2, 0) * vec.x + mat.valueAt(2, 1) * vec.y + mat.valueAt(2, 2) * vec.z;
    vec.x = mat.valueAt(0, 0) * vec.x + mat.valueAt(0, 1) * vec.y + mat.valueAt(0, 2) * vec.z;
    vec.y = y;
    vec.z = z;
    return vec;
}

FORCEINLINE MyFVector4& MyLinearTransformation::transformVector(const MyFMatrix4 &mat,
                                                                MyFVector4 &vec) {
    float y = mat.valueAt(1, 0) * vec.x + mat.valueAt(1, 1) * vec.y + mat.valueAt(1, 2) * vec.z + mat.valueAt(1, 3) * vec.w;
    float z = mat.valueAt(2, 0) * vec.x + mat.valueAt(2, 1) * vec.y + mat.valueAt(2, 2) * vec.z + mat.valueAt(2, 3) * vec.w;
    float w = mat.valueAt(3, 0) * vec.x + mat.valueAt(3, 1) * vec.y + mat.valueAt(3, 2) * vec.z + mat.valueAt(3, 3) * vec.w;
    vec.x = mat.valueAt(0, 0) * vec.x + mat.valueAt(0, 1) * vec.y + mat.valueAt(0, 2) * vec.z + mat.valueAt(0, 3) * vec.w;;
    vec.y = y;
    vec.z = z;
    vec.w = w;
    return vec;
}

/*
 cose -sine
 sine cose
 */
FORCEINLINE MyFMatrix2& MyLinearTransformation::rotateMatrix(MyFMatrix2 &mat,
                                                             float radius) {
    float sine = MyMathUtil::sin(radius);
    float cose = MyMathUtil::cos(radius);
    float tmp = -sine * mat.valueAt(0, 0) + cose * mat.valueAt(1, 0);
    mat.valueAt(0, 0) = cose * mat.valueAt(0, 0) - sine * mat.valueAt(1, 0);
    mat.valueAt(1, 0) = tmp;
    tmp = -sine * mat.valueAt(0, 1) + cose * mat.valueAt(1, 1);
    mat.valueAt(0, 1) = cose * mat.valueAt(0, 1) - sine * mat.valueAt(1, 1);
    mat.valueAt(1, 1) = tmp;
    return mat;
}

/*
 1      0       0
 0      cose   -sine
 0      sine    cose
 */
FORCEINLINE MyFMatrix3& MyLinearTransformation::rotateMatrixByAxisX(MyFMatrix3 &mat,
                                                                    float radius) {
    float sine = MyMathUtil::sin(radius);
    float cose = MyMathUtil::cos(radius);
    float tmp1 = cose * mat.valueAt(1, 1) - sine * mat.valueAt(2, 1);
    float tmp2 = cose * mat.valueAt(1, 2) - sine * mat.valueAt(2, 2);
    mat.valueAt(1, 0) = cose * mat.valueAt(1, 0) - sine * mat.valueAt(2, 0);
    mat.valueAt(1, 1) = tmp1;
    mat.valueAt(1, 2) = tmp2;
    tmp1 = sine * mat.valueAt(1, 1) + cose * mat.valueAt(2, 1);
    tmp2 = sine * mat.valueAt(1, 2) + cose * mat.valueAt(2, 2);
    mat.valueAt(2, 0) = sine * mat.valueAt(1, 0) + cose * mat.valueAt(2, 0);
    mat.valueAt(2, 1) = tmp1;
    mat.valueAt(2, 2) = tmp2;
    return mat;
}

/*
 cose      0       sine
 0          1       0
 -sine      0       cose
 */
FORCEINLINE MyFMatrix3& MyLinearTransformation::rotateMatrixByAxisY(MyFMatrix3 &mat,
                                                                    float radius) {
    float sine = MyMathUtil::sin(radius);
    float cose = MyMathUtil::cos(radius);
    float tmp1 = cose * mat.valueAt(0, 1) + sine * mat.valueAt(2, 1);
    float tmp2 = cose * mat.valueAt(0, 2) + sine * mat.valueAt(2, 2);
    mat.valueAt(0, 0) = cose * mat.valueAt(0, 0) + sine * mat.valueAt(2, 0);
    mat.valueAt(0, 1) = tmp1;
    mat.valueAt(0, 2) = tmp2;
    tmp1 = -sine * mat.valueAt(0, 1) + cose * mat.valueAt(2, 1);
    tmp2 = -sine * mat.valueAt(0, 2) + cose * mat.valueAt(2, 2);
    mat.valueAt(2, 0) = -sine * mat.valueAt(0, 0) + cose * mat.valueAt(2, 0);
    mat.valueAt(2, 1) = tmp1;
    mat.valueAt(2, 2) = tmp2;
    return mat;
}

/*
 cose      -sine      0
 0          1           0
 sine       cose       0
 */
FORCEINLINE MyFMatrix3& MyLinearTransformation::rotateMatrixByAxisZ(MyFMatrix3 &mat,
                                                                    float radius) {
    float sine = MyMathUtil::sin(radius);
    float cose = MyMathUtil::cos(radius);
    float tmp1 = cose * mat.valueAt(0, 1) - sine * mat.valueAt(1, 1);
    float tmp2 = cose * mat.valueAt(0, 2) - sine * mat.valueAt(1, 2);
    mat.valueAt(0, 0) = cose * mat.valueAt(0, 0) - sine * mat.valueAt(1, 0);
    mat.valueAt(0, 1) = tmp1;
    mat.valueAt(0, 2) = tmp2;
    tmp1 = sine * mat.valueAt(0, 1) + cose * mat.valueAt(1, 1);
    tmp2 = sine * mat.valueAt(0, 2) + cose * mat.valueAt(1, 2);
    mat.valueAt(2, 0) = sine * mat.valueAt(0, 0) + cose * mat.valueAt(1, 0);
    mat.valueAt(2, 1) = tmp1;
    mat.valueAt(2, 2) = tmp2;
    return mat;
}

FORCEINLINE MyFMatrix3& MyLinearTransformation::rotateMatrixByAxis(MyFMatrix3 &mat,
                                                                   const MyFVector3 &vec,
                                                                   float radius) {
    MyFVector3 normalizedVec(normalizeVector(vec));
    return rotateMatrixByNormalizedAxis(mat, normalizedVec, radius);
}

// v' = (v - dot(v, n)n)cose + cross(v, n) * sine
FORCEINLINE MyFMatrix3& MyLinearTransformation::rotateMatrixByNormalizedAxis(
                                                                             MyFMatrix3 &mat,
                                                                             const MyFVector3 &vec,
                                                                             float radius) {
    float sine = MyMathUtil::sin(radius);
    float cose = MyMathUtil::cos(radius);
    float oneMinusCose = 1.0f - cose;
    float xx = vec.x * vec.x;
    float xy = vec.x * vec.y;
    float yy = vec.y * vec.y;
    float yz = vec.y * vec.z;
    float zz = vec.z * vec.z;
    float zx = vec.z * vec.x;
    float xsine = vec.x * sine;
    float ysine = vec.y * sine;
    float zsine = vec.z * sine;
    float mx = oneMinusCose * xx + cose;
    float my = oneMinusCose * xy + zsine;
    float mz = oneMinusCose * zx - ysine;
    float tmp0 = mx * mat.valueAt(0, 0) + my * mat.valueAt(1, 0) + mz * mat.valueAt(2, 0);
    float tmp1 = mx * mat.valueAt(0, 1) + my * mat.valueAt(1, 1) + mz * mat.valueAt(2, 1);
    float tmp2 = mx * mat.valueAt(0, 2) + my * mat.valueAt(1, 2) + mz * mat.valueAt(2, 2);
    mx = oneMinusCose * xy - zsine;
    my = oneMinusCose * yy + cose;
    mz = oneMinusCose * yz + xsine;
    float tmp3 = mx * mat.valueAt(0, 0) + my * mat.valueAt(1, 0) + mz * mat.valueAt(2, 0);
    float tmp4 = mx * mat.valueAt(0, 1) + my * mat.valueAt(1, 1) + mz * mat.valueAt(2, 1);
    float tmp5 = mx * mat.valueAt(0, 2) + my * mat.valueAt(1, 2) + mz * mat.valueAt(2, 2);
    mx = oneMinusCose * zx + ysine;
    my = oneMinusCose * yz - xsine;
    mz = oneMinusCose * zz + cose;
    float tmp6 = mx * mat.valueAt(0, 0) + my * mat.valueAt(1, 0) + mz * mat.valueAt(2, 0);
    float tmp7 = mx * mat.valueAt(0, 1) + my * mat.valueAt(1, 1) + mz * mat.valueAt(2, 1);
    float tmp8 = mx * mat.valueAt(0, 2) + my * mat.valueAt(1, 2) + mz * mat.valueAt(2, 2);
    mat.valueAt(0, 0) = tmp0; mat.valueAt(0, 1) = tmp1; mat.valueAt(0, 2) = tmp2;
    mat.valueAt(1, 0) = tmp3; mat.valueAt(1, 1) = tmp4; mat.valueAt(1, 2) = tmp5;
    mat.valueAt(2, 0) = tmp6; mat.valueAt(2, 1) = tmp7; mat.valueAt(2, 2) = tmp8;
    return mat;
}

FORCEINLINE bool MyLinearTransformation::validateCoordinate(const Mine::MyCoordinate &coord) {
    return MyMathUtil::zero(dotProduct(coord.axisX(), coord.axisY())) &&
    MyMathUtil::zero(dotProduct(coord.axisY(), coord.axisZ())) &&
    MyMathUtil::zero(dotProduct(coord.axisZ(), coord.axisX())) &&
    MyMathUtil::equal(magnitudeSquareVector(coord.axisX()), 1.0f) &&
    MyMathUtil::equal(magnitudeSquareVector(coord.axisY()), 1.0f) &&
    MyMathUtil::equal(magnitudeSquareVector(coord.axisZ()), 1.0f);
}

FORCEINLINE bool MyLinearTransformation::validateCoordinate(const MyFVector3 &inX,
                                                            const MyFVector3 &inY,
                                                            const MyFVector3 &inZ) {
    return MyMathUtil::zero(dotProduct(inX, inY)) &&
    MyMathUtil::zero(dotProduct(inY, inZ)) &&
    MyMathUtil::zero(dotProduct(inZ, inX)) &&
    MyMathUtil::equal(magnitudeSquareVector(inX), 1.0f) &&
    MyMathUtil::equal(magnitudeSquareVector(inY), 1.0f) &&
    MyMathUtil::equal(magnitudeSquareVector(inZ), 1.0f);
}

FORCEINLINE MyFVector2 operator*(const MyFMatrix2 &mat, const MyFVector2 &vec) {
    return MyFVector2(mat.valueAt(0, 0) * vec.x + mat.valueAt(0, 1) * vec.y,
                      mat.valueAt(1, 0) * vec.x + mat.valueAt(1, 1) * vec.y);
}

FORCEINLINE MyFVector3 operator*(const MyFMatrix3 &mat, const MyFVector3 &vec) {
    return MyFVector3(mat.valueAt(0, 0) * vec.x + mat.valueAt(0, 1) * vec.y + mat.valueAt(0, 2) * vec.z,
                      mat.valueAt(1, 0) * vec.x + mat.valueAt(1, 1) * vec.y + mat.valueAt(1, 2) * vec.z,
                      mat.valueAt(2, 0) * vec.x + mat.valueAt(2, 1) * vec.y + mat.valueAt(2, 2) * vec.z);
}

FORCEINLINE MyFVector4 operator*(const MyFMatrix4 &mat, const MyFVector4 &vec) {
    return MyFVector4(mat.valueAt(0, 0) * vec.x + mat.valueAt(0, 1) * vec.y + mat.valueAt(0, 2) * vec.z + mat.valueAt(0, 3) * vec.w,
                      mat.valueAt(1, 0) * vec.x + mat.valueAt(1, 1) * vec.y + mat.valueAt(1, 2) * vec.z + mat.valueAt(1, 3) * vec.w,
                      mat.valueAt(2, 0) * vec.x + mat.valueAt(2, 1) * vec.y + mat.valueAt(2, 2) * vec.z + mat.valueAt(2, 3) * vec.w,
                      mat.valueAt(3, 0) * vec.x + mat.valueAt(3, 1) * vec.y + mat.valueAt(3, 2) * vec.z + mat.valueAt(3, 3) * vec.w);
}

MINE_NAMESPACE_END
