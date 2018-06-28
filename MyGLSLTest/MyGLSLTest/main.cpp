//
//  main.cpp
//  MyGLSLTest
//
//  Created by xy on 01/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <iostream>
#include <memory>
#include <string>
#include <sstream>
//#include "TestScenario.hpp"
#include "BaseScene.hpp"
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
    disposer->objectName("MyErrorDisposer");
    return disposer;
}

void* operator new(size_t sz) {
    std::cout << "come up with global new\n";
    return malloc(sz);
}

void operator delete(void* p) {
    std::cout << "come up with global delete\n";
    MyObject *obj = (MyObject*)p;
    if(obj) {
        std::cout << "delete object = " << obj->objectName() << "\n";
    }
    free(p);
}

int main(int argc, const char * argv[]) {
    //MathTest test;
    //test.run();
    
    auto sharedDirector = MyDirector::sharedDirector();
    MyErrorDesc::sharedErrorDesc()->errorCallback(MyErrorDisposer::create());
    
    if(!sharedDirector->createWindow(800, 600, "Hello World")) {
        sharedDirector->closeDirector();
        return -1;
    }
    
    MyScenario *myScenerio = BaseScene::create();
    
    if(!myScenerio->initialize()) {
        sharedDirector->closeDirector();
        return -1;
    }
    
    sharedDirector->runScenario(myScenerio);
    sharedDirector->runMainLoop();
    
    sharedDirector->closeDirector();
    
    std::cout << "Hello World\n";
    return 0;
}
