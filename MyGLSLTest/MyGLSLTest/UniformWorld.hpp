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
#include "Mine.hpp"

USING_MINE_NAMESPACE;

class UniformScene: public MyWorld  {
public:
    bool initialize(void) override;
    void update(float deltaTime) override;
    void render(void) override;
    void destroy(void);
    
    static UniformScene* create(void);
    
private:
    UniformScene(void) {}
    ~UniformScene(void) { destroy(); }
    
    MyRenderer *_myRenderer;
    MyProgram *_myProgram;
    MyBufferObject *_myVertexBuffer;
    MyVertexArrayObject *_myVertexArray;
};

#endif /* UniformScene_hpp */
