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
    MyMatrix<2, 2> mm1(1.0f);
    MyMatrix<2, 2, int> mm2(2);
    MyMatrix<2, 2> mm3(mm1);
    MyMatrix<3, 2> mm4(2.5f);
    MyMatrix<2, 3> mm5(1.5f);
    MyMatrix<3, 3> mm6;
    MyMatrix<3, 4> mm7;
    MyMatrix<4, 2> mm8(1.0f);
    MyMatrix<8, 8, std::string> mm9;
    
    for(MyMatrix<3, 4>::size_type i = 0; i != mm7.size(); ++i) {
        mm7.valueAt(i/mm7.column(), i%mm7.column()) = static_cast<MyMatrix<3, 4>::value_type>(i);
    }
    
    mm3 = mm1 + mm2;
    mm3 = mm1 * mm2;
    mm6 = mm4 * mm5;
    mm4 = mm7 * mm8;
    //mm3 = mm1 * mm4;
    mm6 = mm4 * mm5;
    
    swapMatrixRow(mm6, 1, 2);
    multiplyMatrixRow(mm6, 2, 5.0f);
    subtractMatrixRow(mm6, 2, 1, 5.0f);
    
    swapMatrixColumn(mm6, 0, 1);
    multiplyMatrixColumn(mm6, 1, 2);
    subtractMatrixColumn(mm6, 1, 0, 'a');
    
    transposeMatrix(mm6);
    identityMatrix(mm6);
    
    MyMatrix<3, 3> mq({2, 1, 1, 0, 1, 1, 0, -1, 3});
    MyMatrix<3, 3> me({2, 1, 1, 0, 1, 1, 0, -1, 3});
    MyMatrix<3, 1> mp({0, 1, -1});
    
    identityMatrix(me);
    
    auto mpp2 = 2 * me - mq;
    auto mpp = (2 * me - mq) * mp;
    auto mpp1 = 2 * mp - mq * mp;
    
    mpp = {1, 2, 3};
    //simplifyMatrix(mpp);
    
    MyMatrix<3, 2> im1({1, 2, 3, 4, 5, 6});
    MyMatrix<2, 3> im2({1, 2, 3, 4, 5, 6});
    
    //simplifyMatrix(im1);
    simplifyMatrix(im2);
    
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
