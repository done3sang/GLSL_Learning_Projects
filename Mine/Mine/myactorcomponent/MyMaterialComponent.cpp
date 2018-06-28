//
//  MyMaterialComponent.cpp
//  MyGLSL
//
//  Created by xy on 11/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyVector.hpp"
#include "MyObject.hpp"
#include "MyActorComponent.hpp"
#include "MyMaterialComponent.hpp"

MINE_NAMESPACE_BEGIN

MyMaterialComponent* MyMaterialComponent::create(void) {
    MyMaterialComponent *mat = new MyMaterialComponent;
    mat->objectName("MyMaterialComponent");
    return mat;
}

MyMaterialComponent* MyMaterialComponent::createWithColor(const MyFVector4 &color) {
    MyMaterialComponent *mat = new MyMaterialComponent(color);
    mat->objectName("MyMaterialComponent");
    return mat;
}

MINE_NAMESPACE_END
