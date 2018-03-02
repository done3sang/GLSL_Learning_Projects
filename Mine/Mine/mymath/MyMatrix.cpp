//
//  MyMatrix.cpp
//  Mine
//
//  Created by xy on 26/02/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#include "MyMatrix.hpp"

MINE_NAMESPACE_BEGIN

const MyFMatrix2 MyFMatrix2::kIdentity(1.0f, 0.0f, 0.0f, 1.0f);
const MyFMatrix2 MyFMatrix2::kZero(0.0f, 0.0f, 0.0f, 0.0f);

const MyFMatrix3 MyFMatrix3::kIdentity(1.0f, 0.0f, 0.0f,
                                       0.0f, 1.0f, 0.0f,
                                       0.0f, 0.0f, 1.0f);
const MyFMatrix3 MyFMatrix3::kZero(0.0f, 0.0f, 0.0f,
                                   0.0f, 0.0f, 0.0f,
                                   0.0f, 0.0f, 0.0f);

const MyFMatrix4 MyFMatrix4::kIdentity(1.0f, 0.0f, 0.0f, 0.0f,
                                       0.0f, 1.0f, 0.0f, 0.0f,
                                       0.0f, 0.0f, 1.0f, 0.0f,
                                       0.0f, 0.0f, 0.0f, 1.0f);
const MyFMatrix4 MyFMatrix4::kZero(0.0f, 0.0f, 0.0f, 0.0f,
                                   0.0f, 0.0f, 0.0f, 0.0f,
                                   0.0f, 0.0f, 0.0f, 0.0f,
                                   0.0f, 0.0f, 0.0f, 0.0f);

MINE_NAMESPACE_END
