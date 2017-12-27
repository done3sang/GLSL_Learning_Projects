//
//  main.cpp
//  MyGLSLTest
//
//  Created by xy on 01/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <iostream>
#include <string>
#include "TestScenario.hpp"
#include "BaseScene.hpp"
#include "UniformScene.hpp"
#include "myxml/MyXMLDocument.hpp"
#include "myxml/MyXMLNode.hpp"

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

void printXMLNode(const MyXMLNode *xmlnode, std::string &desc);
std::string printXMLDoc(const MyXMLDocument *doc);

int main(int argc, const char * argv[]) {
    auto sharedDirector = MyDirector::sharedDirector();
    MyErrorDesc::sharedErrorDesc()->errorCallback(MyErrorDisposer::create());
    
    /*
    MyXMLDocument *doc = MyXMLDocument::create();
    if(!doc->loadDocument("./Shader/shader.xml")) {
        std::cout << "Failed to load xml\n";
    }
    
    std::cout << "hello world\n" << printXMLDoc(doc);
     */
    
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
    return 0;
}

void printXMLNode(const MyXMLNode *xmlnode, std::string &desc) {
    if(!xmlnode) {
        return;
    }
    
    desc += xmlnode->nodeName() + " = ";
    if(xmlnode->text()) {
        desc += xmlnode->nodeValue();
    } else {
        desc += "element";
    }
    desc += "(";
    if(xmlnode->childNode()) {
        desc += xmlnode->childNode()->nodeName() + ", ";
    } else {
        desc += "nullptr, ";
    }
    if(xmlnode->siblingNode()) {
        desc += xmlnode->siblingNode()->nodeName();
    } else {
        desc += "nullptr";
    }
    desc += ")\n";
    
    printXMLNode(xmlnode->childNode(), desc);
    printXMLNode(xmlnode->siblingNode(), desc);
}

std::string printXMLDoc(const MyXMLDocument *doc) {
    std::string desc;
    
    if(!doc) {
        return desc;
    }
    
    desc += "-----------xml attribute-----------\n";
    for(auto iter: doc->attributeMap()) {
        desc += iter.first + " = ";
        desc += iter.second + "\n";
    }
    
    desc += "\n----------xml root--------------\n";
    printXMLNode(doc->rootNode(), desc);
    
    return desc;
}
