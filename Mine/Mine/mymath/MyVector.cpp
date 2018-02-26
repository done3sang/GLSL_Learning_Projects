//
//  MyVector.cpp
//  Mine
//
//  Created by xy on 26/02/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#include "MyTemplate.hpp"
#include "MyVector.hpp"

MINE_NAMESPACE_BEGIN

const MyFVector2 MyFVector2::kFVector2AxisX(1.0f, 0.0f);
const MyFVector2 MyFVector2::kFVector2AxisY(0.0f, 1.0f);

const MyFVector3 MyFVector3::kFVector3AxisX(1.0f, 0.0f, 0.0f);
const MyFVector3 MyFVector3::kFVector3AxisY(0.0f, 1.0f, 0.0f);
const MyFVector3 MyFVector3::kFVector3AxisZ(0.0f, 0.0f, 1.0f);

const MyFVector4 MyFVector4::kFVector4AxisX(1.0f, 0.0f, 0.0f, 0.0f);
const MyFVector4 MyFVector4::kFVector4AxisY(0.0f, 1.0f, 0.0f, 0.0f);
const MyFVector4 MyFVector4::kFVector4AxisZ(0.0f, 0.0f, 1.0f, 0.0f);
const MyFVector4 MyFVector4::kFVector4AxisW(0.0f, 0.0f, 0.0f, 1.0f);

MINE_NAMESPACE_END
