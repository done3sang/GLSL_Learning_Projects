//
//  BaseScene.hpp
//  MyGLSLTest
//
//  Created by xy on 05/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef BaseScene_hpp
#define BaseScene_hpp

#include <glm/glm.hpp>
#include "Mine.hpp"

USING_MINE_NAMESPACE;

class BaseScene: public MyScene  {
public:
    bool initialize(void);
    void update(float deltaTime);
    void render(void);
    void destroy(void) {}
    
    static BaseScene* create(void);
    
private:
    MyRenderer *_myRenderer;
    MyProgram *_myProgram;
    MyVertexArrayObject *_myVertexArray;
    
    glm::mat4 _rotationMatrix;
    float _rotationAngle;
};

#endif /* BaseScene_hpp */
