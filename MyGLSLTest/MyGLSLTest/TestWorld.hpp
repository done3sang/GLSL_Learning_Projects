//
//  TestWorld.hpp
//  MyGLSLTest
//
//  Created by xy on 27/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef TestWorld_hpp
#define TestWorld_hpp

#include "Mine.hpp"

USING_MINE_NAMESPACE;

class TestWorld: public MyWorld {
public:
    bool initialize(void) override;
    
    static TestWorld* create(void);
    
private:
    
};

#endif /* TestWorld_hpp */
