//
//  MyLinearTransformation.inl
//  Mine
//
//  Created by xy on 24/02/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#include "MyVector.hpp"
#include "MyMatrix.hpp"

MINE_NAMESPACE_BEGIN

namespace {
    // swap matrix row
    template<class M, int D, int I>
    struct MatrixSwapRowImpl {
        enum {
            Continue = I != D - 1,
            NextI = I + 1
        };
        
        static float temp;
        
        static FORCEINLINE void eval(M &mat, int x, int y, int index) {
            MINE_ASSERT2(index <= D, "MatrixSwapRowImpl, index out of range");
            temp = mat.valueAt(x, index);
            mat.valueAt(x, index) = mat.valueAt(y, index);
            mat.valueAt(y, index) = temp;
            ++index;
            if(D != index) {
                MatrixSwapRowImpl<M, D * Continue, NextI * Continue>::eval(M, x, y, index);
            }
        }
    };
    
    template<class M, int D, int I>
    float MatrixSwapRowImpl::temp(0.0f);
    
    template<class M>
    struct MatrixSwapRowImpl<M, 0, 0> {
        static FORCEINLINE void eval(M&, int, int, int) {}
    };
    
    template<class M, int D>
    FORCEINLINE void matrixSwapRow(M &mat, int x, int y, int startIndex) {
        MatrixSwapRowImpl<M, D, 0>::eval(mat, x, y, startIndex);
    }
    
    // multiply matrix row
    template<class M, int D, int I>
    struct MatrixMultiplyRowImpl {
        enum {
            Continue = I != D - 1,
            NextI = I + 1
        };
        
        static FORCEINLINE void eval(M &mat, int x, float multiple, int index) {
            MINE_ASSERT2(index <= D, "MatrixMultiplyRowImpl, index out of range");
            mat.valueAt(x, index) *= multiple;
            ++index;
            if(D != index) {
                MatrixMultiplyRowImpl<M, D * Continue, NextI * Continue>::eval(M, x, multiple, index);
            }
        }
    };
    
    template<class M>
    struct MatrixMutiplyRowImpl<M, 0, 0> {
        static FORCEINLINE void eval(M&, int, float, int) {}
    };
    
    template<class M, int D>
    FORCEINLINE void matrixMultiplyRow(M &mat, int x, float multiple, int startIndex) {
        MatrixMutiplyRowImpl<M, D, 0>::eval(mat, x, multiple, startIndex);
    }
    
    // substract matrix row, x -= y * multiple
    template<class M, int D, int I>
    struct MatrixSubstractRowImpl {
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
                MatrixSubstractRowImpl<M, D * Continue, NextI * Continue>::eval(M, x, y, multiple, index);
            }
        }
    };
    
    template<class M>
    struct MatrixSubstractRowImpl<M, 0, 0> {
        static FORCEINLINE void eval(M&, int, int, float, int) {}
    };
    
    template<class M, int D>
    FORCEINLINE void matrixSubstractRow(M &mat, int x, int y, float multiple, int startIndex) {
        MatrixSubstractRowImpl<M, D, 0>::eval(mat, x, y, multiple, startIndex);
    }
    
    // swap matrix column
    template<class M, int D, int I>
    struct MatrixSwapColumnImpl {
        enum {
            Continue = I != D - 1,
            NextI = I + 1
        };
        
        static float temp;
        
        static FORCEINLINE void eval(M &mat, int x, int y, int index) {
            MINE_ASSERT2(index <= D, "MatrixSwapColumnImpl, index out of range");
            temp = mat.valueAt(index, x);
            mat.valueAt(index, x) = mat.valueAt(index, y);
            mat.valueAt(index, y) = temp;
            ++index;
            if(D != index) {
                MatrixSwapColumnImpl<M, D * Continue, NextI * Continue>::eval(M, x, y, index);
            }
        }
    };
    
    template<class M, int D, int I>
    float MatrixSwapColumnImpl::temp(0.0f);
    
    template<class M>
    struct MatrixSwapColumnImpl<M, 0, 0> {
        static FORCEINLINE void eval(M&, int, int, int) {}
    };
    
    template<class M, int D>
    FORCEINLINE void matrixSwapColumn(M &mat, int x, int y, int startIndex) {
        MatrixSwapColumnImpl<M, D, 0>::eval(mat, x, y, startIndex);
    }
    
    // multiply matrix column
    template<class M, int D, int I>
    struct MatrixMultiplyColumnImpl {
        enum {
            Continue = I != D - 1,
            NextI = I + 1
        };
        
        static FORCEINLINE void eval(M &mat, int x, float multiple, int index) {
            MINE_ASSERT2(index <= D, "MatrixMultiplyColumnImpl, index out of range");
            mat.valueAt(index, x) *= multiple;
            ++index;
            if(D != index) {
                MatrixMultiplyColumnImpl<M, D * Continue, NextI * Continue>::eval(M, x, multiple, index);
            }
        }
    };
    
    template<class M>
    struct MatrixMultiplyColumnImpl<M, 0, 0> {
        static FORCEINLINE void eval(M&, int, float, int) {}
    };
    
    template<class M, int D>
    FORCEINLINE void matrixMultiplyColumn(M &mat, int x, float multiple, int startIndex) {
        MatrixMultiplyColumnImpl<M, D, 0>::eval(mat, x, multiple, startIndex);
    }
    
    // substract matrix column, x -= y * multiple
    template<class M, int D, int C>
    struct MatrixSubstractColumnImpl {
        enum {
            Continue = I != D - 1,
            NextI = I + 1
        };
        
        static FORCEINLINE void eval(M &mat, int x, int y, float multiple, int index) {
            MINE_ASSERT2(index <= D, "MatrixSubstractColumnImpl, index out of range");
            mat.valueAt(x, index) -= mat.valueAt(y, index) * multiple;
            ++index;
            if(D != index) {
                MatrixSubstractColumnImpl<M, D * Continue, NextI * Continue>::eval(M, x, y, multiple, index);
            }
        }
    };
    
    template<class M>
    struct MatrixSubstractColumnImpl<M, 0, 0> {
        static FORCEINLINE void eval(M&, int, int, float, int) {}
    };
    
    template<class M, int D>
    FORCEINLINE void matrixSubstractColumn(M &mat, int x, int y, float multiple, int startIndex) {
        MatrixSubstractColumnImpl<M, D, 0>::eval(mat, x, y, multiple, startIndex);
    }
}

template<class M>
FORCEINLINE void MyLinearTransformation::swapMatrixRow(M &mat,
                                                       int x, int y, int startIndex) {
    matrixSwapRow<M, M::kDimension>(mat, x, y, startIndex);
}

template<class M>
FORCEINLINE void MyLinearTransformation::multiplyMatrixRow(M &mat,
                                                           int x, float multiple, int startIndex) {
    matrixMultiplyRow<M, M::kDimension>(mat, x, multiple, startIndex);
}

template<class M>
FORCEINLINE void MyLinearTransformation::substractMatrixRow(M &mat,
                                                           int x, int, y, float multiple, int startIndex) {
    matrixSubstractRow<M, M::kDimension>(mat, x, y, multiple, startIndex);
}

template<class M>
FORCEINLINE void MyLinearTransformation::swapMatrixColumn(M &mat,
                                                       int x, int y, int startIndex) {
    matrixSwapColumn<M, M::kDimension>(mat, x, y, startIndex);
}

template<class M>
FORCEINLINE void MyLinearTransformation::multiplyMatrixColumn(M &mat,
                                                           int x, float multiple, int startIndex) {
    matrixMultiplyColumn<M, M::kDimension>(mat, x, multiple, startIndex);
}

template<class M>
FORCEINLINE void MyLinearTransformation::substractMatrixColumn(M &mat,
                                                            int x, int, y, float multiple, int startIndex) {
    matrixSubstractColumn<M, M::kDimension>(mat, x, y, multiple, startIndex);
}

MINE_NAMESPACE_END
