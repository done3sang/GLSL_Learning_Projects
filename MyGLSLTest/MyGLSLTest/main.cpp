//
//  main.cpp
//  MyGLSLTest
//
//  Created by xy on 01/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <iostream>
#include <string>
#include "BaseScene.hpp"

USING_MINE_NAMESPACE;

class MyErrorDisposer: public MyErrorCallback {
public:
    void disposeError(int errCode, const std::string &errDesc) {
        std::cout << "Error(" << errCode << ") = " << errDesc << "\n";
    }
};

int main(int argc, const char * argv[]) {
    MyGLSL *sharedGLSL = MyGLSL::sharedGLSL();
    MyErrorDisposer errDisposer;
    
    sharedGLSL->windowErrorCallback(errDisposer);
    MyErrorDesc::sharedErrorDesc()->errorCallback(errDisposer);
    
    if(!sharedGLSL->createWindow(800, 600, "Hello World")) {
        sharedGLSL->closeGLSL();
        return -1;
    }
    
    BaseScene *myScene = BaseScene::create();
    
    if(!myScene->initialize()) {
        sharedGLSL->closeGLSL();
        return -1;
    }
    
    sharedGLSL->mainFunc(myScene);
    sharedGLSL->runMainLoop();
    
    sharedGLSL->closeGLSL();
    return 0;
}
