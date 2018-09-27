//
//  BaseScene.hpp
//  MyGLSLTest
//
//  Created by xy on 05/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef BaseScene_hpp
#define BaseScene_hpp

#include "Mine.hpp"

USING_MINE_NAMESPACE;

class BaseScene: public MyWorld  {
public:
    bool initialize(void) override;
    void update(float deltaTime) override;
    void render(void) override;
    
    static BaseScene* create(void);
    
private:
    virtual ~BaseScene(void);
    
    MyRenderer *_myRenderer;
    MyProgram *_myProgram;
    MyBufferObject *_positionBuffer;
    MyBufferObject *_colorBuffer;
    MyBufferObject* _texCoordBuffer;
    MyVertexArrayObject *_myVertexArray;
    MyTexture2D* _myTexture;
    
    MyFMatrix4 _rotationMatrix;
    float _rotationAngle;
};

#endif /* BaseScene_hpp */
