//
//  main.cpp
//  MyGLSLTest
//
//  Created by xy on 01/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
//#include "Mine.hpp"
//#include "TestScenario.hpp"
//#include "BaseScene.hpp"
//#include "UniformScene.hpp"
#include "MyTest/TestMath.hpp"

USING_MINE_NAMESPACE;

class MyErrorDisposer: public MyErrorCallback {
public:
    void disposeError(int errCode, const std::string &errDesc) {
        std::cout << "Error(" << errCode << ") = " << errDesc << "\n";
    }
    
    static MyErrorDisposer* create(void);
};

MyErrorDisposer* MyErrorDisposer::create(void) {
    MyErrorDisposer *disposer = new MyErrorDisposer;
    disposer->refName("MyErrorDisposer");
    return disposer;
}

int main(int argc, const char * argv[]) {
    MathTest test;
    test.run();
    
    /*
    auto sharedDirector = MyDirector::sharedDirector();
    MyErrorDesc::sharedErrorDesc()->errorCallback(MyErrorDisposer::create());
    
    if(!sharedDirector->createWindow(800, 600, "Hello World")) {
        sharedDirector->closeDirector();
        return -1;
    }
    
    MyScenario *myScenerio = TestScenario::create();
    
    if(!myScenerio->initialize()) {
        sharedDirector->closeDirector();
        return -1;
    }
    
    sharedDirector->runScenario(myScenerio);
    sharedDirector->runMainLoop();
    
    sharedDirector->closeDirector();
     */
    
    std::cout << "Hello World\n";
    return 0;
}
