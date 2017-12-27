//
//  TestScenario.hpp
//  MyGLSLTest
//
//  Created by xy on 27/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef TestScenario_hpp
#define TestScenario_hpp

#include "Mine.hpp"

USING_MINE_NAMESPACE;

class TestScenario: public MyScenario {
public:
    bool initialize(void) override;
    
    static TestScenario* create(void);
    
private:
    
};

#endif /* TestScenario_hpp */
