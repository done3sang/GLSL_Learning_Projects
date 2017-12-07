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
#include "UniformScene.hpp"

USING_MINE_NAMESPACE;

class MyErrorDisposer: public MyErrorCallback {
public:
    void disposeError(int errCode, const std::string &errDesc) {
        std::cout << "Error(" << errCode << ") = " << errDesc << "\n";
    }
};

int main(int argc, const char * argv[]) {
    
    /*
    MyDirector *sharedDirector = MyDirector::sharedDirector();
    MyErrorDisposer *errDisposer = new MyErrorDisposer;
    
    sharedDirector->errorCallback(errDisposer);
    
    if(!sharedDirector->createWindow(800, 600, "Hello World")) {
        sharedDirector->closeDirector();
        return -1;
    }
    
    MyScene *myScene = UniformScene::create();
    
    if(!myScene->initialize()) {
        sharedDirector->closeDirector();
        return -1;
    }
    
    sharedDirector->runningScene(myScene);
    sharedDirector->runMainLoop();
    
    sharedDirector->closeDirector();
    */
    return 0;
}
