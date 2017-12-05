//
//  UniformScene.hpp
//  MyGLSLTest
//
//  Created by xy on 05/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef UniformScene_hpp
#define UniformScene_hpp

#include <glm/glm.hpp>
#include "MyGLSLAll.hpp"

USING_MINE_NAMESPACE;

class UniformScene: public MyScene  {
public:
    bool initialize(void);
    void update(float deltaTime);
    void render(void);
    
    static UniformScene* create(void);
    
private:
    MyRenderer *_myRenderer;
    MyProgram *_myProgram;
    MyVertexArrayObject *_myVertexArray;
};

#endif /* UniformScene_hpp */
