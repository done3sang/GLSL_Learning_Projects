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
#include "tinyxml/tinyxml.h"

USING_MINE_NAMESPACE;

class MyErrorDisposer: public MyErrorCallback {
public:
    void disposeError(int errCode, const std::string &errDesc) {
        std::cout << "Error(" << errCode << ") = " << errDesc << "\n";
    }
};

bool myReadShader(const std::string &path);

int main(int argc, const char * argv[]) {
    myReadShader("./Shader/shader.xml");
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

bool myReadShader(const std::string &path) {
    TiXmlDocument doc(path.c_str());
    
    if(!doc.LoadFile()) {
        std::cout << "Could not load test file " << path << ". Error = " << doc.ErrorDesc() << ".\n";
        return false;
    }
    
    TiXmlElement *root = doc.RootElement();
    std::cout << "---------------------------------\n\n";
    std::cout << "----------" << root->Value() << "-----\n";
    std::cout << "   contacted person information    \n\n";
    for(TiXmlNode *node = root->FirstChild(); node; node = node->NextSibling()) {
        std::cout << "--------" << node->Value() << "------\n";
    }
    
    return true;
}
