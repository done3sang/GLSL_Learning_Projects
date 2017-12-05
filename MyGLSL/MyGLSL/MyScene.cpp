//
//  MyScene.cpp
//  MyGLSL
//
//  Created by xy on 05/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyRef.hpp"
#include "MyTemplate.hpp"
#include "MyScene.hpp"

MINE_NAMESPACE_BEGIN

MyScene* MyScene::create(void) {
    return nullptr;
}

MyScene::~MyScene(void) {
    destroy();
}

MINE_NAMESPACE_END
