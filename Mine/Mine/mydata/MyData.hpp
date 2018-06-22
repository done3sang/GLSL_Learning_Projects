//
//  MyData.hpp
//  Mine
//
//  Created by xy on 2018/6/19.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MyData_hpp
#define MyData_hpp

#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyUniqueObject;

class MyData: public MyUniqueObject {
public:
    static MyData* create(void);
    static MyData* createFromFile(const char* filepath);
    
    MyData(void);
    MyData(const char* filepath);
    
    
    void loadFromFile(const char* filepath);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyData_hpp */
