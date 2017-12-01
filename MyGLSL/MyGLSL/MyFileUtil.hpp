//
//  MyFileUtility.hpp
//  MyGLSL
//
//  Created by xy on 27/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyFileUtility_hpp
#define MyFileUtility_hpp

#include <string>
#include "Precompiled.h"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyRef;

class MyFileUtil: public MyRef {
public:
    ~MyFileUtil(void) {}
    
    static MyFileUtil& sharedFileUtil(void);
    static void closeFileUtil(void);
    
public:
    int readFile(const std::string &filepath, std::string &outstr);
    
private:
    static MyFileUtil *_sharedFileUtil;
    
    MyFileUtil(void) {}
    
    MyFileUtil(const MyFileUtil&);
    MyFileUtil& operator=(const MyFileUtil&);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyFileUtility_hpp */
