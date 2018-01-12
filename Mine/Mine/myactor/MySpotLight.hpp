//
//  MySpotLight.hpp
//  MyGLSL
//
//  Created by xy on 12/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MySpotLight_hpp
#define MySpotLight_hpp

#include <string>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyLightActor;
class MyProgram;
class MySpotLightComponent;

class MySpotLight: public MyLightActor {
public:
    static MySpotLight* createWithName(const std::string &name);
    
    void bindProgram(MyProgram *prog) override;
    
private:
    MySpotLight(void);
    ~MySpotLight(void) {}
    
    MySpotLightComponent *_lightComponent;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MySpotLight_hpp */
