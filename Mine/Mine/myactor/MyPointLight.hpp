//
//  MyPointLight.hpp
//  MyGLSL
//
//  Created by xy on 12/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyPointLight_hpp
#define MyPointLight_hpp

#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyLightActor;
class MyProgram;
class MyPointLightComponent;

class MyPointLight: public MyLightActor {
public:
    static MyPointLight* create(void);
    
    void bindProgram(MyProgram *prog) override;
    
private:
    MyPointLight(void);
    ~MyPointLight(void) {}
    
    MyPointLightComponent *lightComponent;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyPointLight_hpp */
