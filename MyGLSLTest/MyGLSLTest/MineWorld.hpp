//
//  MineWorld.hpp
//  MyGLSLTest
//
//  Created by xy on 2018/10/10.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MineWorld_hpp
#define MineWorld_hpp

#include "Mine.hpp"

USING_MINE_NAMESPACE;

class MineWorld: public MyWorld {
public:
    bool initialize(void) override;
    void update(float deltaTime) override;
    
    static MineWorld* world(void);
    
private:
    MyActor *_triangleActor;
};

#endif /* MineWorld_hpp */
