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
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MySingletonObject;

class MyFileUtil final: public MySingletonObject {
public:
    static MyFileUtil* sharedFileUtil(void);
    static void closeFileUtil(void);
    
public:
    bool readFile(const std::string &filepath, std::string &outstr);
    
private:
    MyFileUtil(void) {}
    ~MyFileUtil(void) {}
    
    static MyFileUtil *_sharedFileUtil;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyFileUtility_hpp */
