//
//  MyGLSL.cpp
//  MyGLSL
//
//  Created by xy on 27/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyTemplate.hpp"
#include "MyAutoreleasePool.hpp"
#include "MyGLSL.hpp"

MINE_NAMESPACE_BEGIN

MyGLSL* MyGLSL::_shardeGLSL = nullptr;

MyGLSL* MyGLSL::sharedGLSL(void) {
    if(nullptr == _shardeGLSL) {
        _shardeGLSL = new MyGLSL;
        _shardeGLSL->initialize();
    }
    
    return _shardeGLSL;
}

MyGLSL::~MyGLSL(void) {
    MyAutoreleasePool::deleteAutoreleasePool();
}

void MyGLSL::closeGLSL(void) {
    if(_shardeGLSL) {
        delete _shardeGLSL;
        _shardeGLSL = nullptr;
    }
}

void MyGLSL::initialize(void) {
    MyAutoreleasePool::sharedAutoreleasePool();
}

MINE_NAMESPACE_END
