//
//  MyFileUtility.cpp
//  MyGLSL
//
//  Created by xy on 27/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <fstream>
#include <sstream>
#include "MyRef.hpp"
#include "MyFileUtil.hpp"
#include "MyErrorDesc.hpp"

MINE_NAMESPACE_BEGIN

MyFileUtil* MyFileUtil::_sharedFileUtil = nullptr;

MyFileUtil& MyFileUtil::sharedFileUtil(void) {
    if(nullptr == _sharedFileUtil) {
        _sharedFileUtil = new MyFileUtil;
    }
    
    return *_sharedFileUtil;
}

void MyFileUtil::closeFileUtil(void) {
    if(_sharedFileUtil) {
        delete _sharedFileUtil;
        _sharedFileUtil = nullptr;
    }
}

int MyFileUtil::readFile(const std::string &filepath, std::string &outstr) {
    std::ifstream infile(filepath, std::ifstream::in);
    if(!infile) {
        return MyErrorDesc::kErrFileNotExists;
    }
    
    std::istreambuf_iterator<char> beg(infile), end;
    
    outstr.assign(beg, end);
    infile.close();
    
    return MyErrorDesc::kErrOk;
}

MINE_NAMESPACE_END
