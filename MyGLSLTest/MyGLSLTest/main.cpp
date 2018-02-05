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

template<int R, int C, class V>
void printMatrix(const MyMatrix<R, C, V> &mat) {
    for(int r = 0; r != R; ++r) {
        for(int c = 0; c != C; ++c) {
            std::cout << mat.valueAt(r, c) << "\t\t";
        }
        std::cout << '\n';
    }
}

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
    simplifyMatrix(mpp);
    
    MyMatrix<3, 2> im1({1, 2, 3, 4, 5, 6});
    MyMatrix<2, 3> im2({1, 2, 3, 4, 5, 6});
    //MyMatrix<33, 32> im3({1, 2, 3, 4, 5, 6});
    MyMatrix<4, 5> im4({1, 2, 0, 3, 11,
        4, 5, 0, 6, 12,
        7, 8, 0, 10, 13,
        14, 15, 0, 16, 17
    });
    
    simplifyMatrix(im1);
    simplifyMatrix(im2);
    //simplifyMatrix(im3);
    simplifyMatrix(im4);
    
    MyMatrix<1, 1> md1({2});
    MyMatrix<2, 2> md2({2, 1, 1, 0});
    MyMatrix<3, 3> md3({1, 2, 3, 4, 5, 6, 7, 8, 9});
    MyMatrix<3, 3> md4({
        2, 1, 1,
        0, 1, 1,
        0, -1, 3
    });
    MyMatrix<4, 4> md5({
        1, 0, 0, 0,
        0, 2, 0, 0,
        0, 0, 0, 4,
        0, 0, 3, 0
    });
    
    std::cout << std::boolalpha;
    
    MyMatrix<1, 1> mi1;
    MyMatrix<2, 2> mi2;
    MyMatrix<3, 3> mi3;
    MyMatrix<3, 3> mi4;
    MyMatrix<4, 4> mi5;
    bool inversible;
    
    inversible = inverseMatrix(md1, mi1);
    std::cout << "det(md1), inversible = " << md1.determinant() << ", " << inversible << "\n";
    std::cout << "mi1 = \n";
    printMatrix(mi1);
    
    inversible = inverseMatrix(md2, mi2);
    std::cout << "det(md2), inversible = " << md2.determinant() << ", " << inversible << "\n";
    std::cout << "mi2 = \n";
    printMatrix(mi2);
    
    inversible = inverseMatrix(md3, mi3);
    std::cout << "det(md3), inversible = " << md3.determinant() << ", " << inversible << "\n";
    std::cout << "mi3 = \n";
    printMatrix(mi3);
    
    inversible = inverseMatrix(md4, mi4);
    std::cout << "det(md4), inversible = " << md4.determinant() << ", " << inversible << "\n";
    std::cout << "mi4 = \n";
    printMatrix(mi4);
    
    inversible = inverseMatrix(md5, mi5);
    std::cout << "det(md5), inversible = " << md5.determinant() << ", " << inversible << "\n";
    std::cout << "mi5 = \n";
    printMatrix(mi5);
    
    MyMatrix<3, 3> md6({
        0, 2, -1,
        1, 1, 2,
        -1, -1, -1
    });
    MyMatrix<3, 3> mi6;
    
    inversible = inverseMatrix(md6, mi6);
    std::cout << "det(md6), inversible = " << md6.determinant() << ", " << inversible << "\n";
    std::cout << "mi6 = \n";
    printMatrix(mi6);
    
    MyMatrix<3, 3> md7({
        1, -2, 1,
        2, 0, 1,
        0, 4, -1
    });
    MyMatrix<3, 3> mi7;
    
    inversible = inverseMatrix(md7, mi7);
    std::cout << "det(md7), inversible = " << md7.determinant() << ", " << inversible << "\n";
    std::cout << "mi7 = \n";
    printMatrix(mi7);
    
    // evaluation
    MyMatrix<4, 4> mb({
        1, 2, -3, -2,
        0, 1, 2, -3,
        0, 0, 1, 2,
        0, 0, 0, 1
    });
    MyMatrix<4, 4> mc({
        1, 2, 0, 1,
        0, 1, 2, 0,
        0, 0, 1, 2,
        0, 0, 0, 1
    });
    MyMatrix<4, 4> ma(2.0f * mc - mb);
    MyMatrix<4, 4> mai;
    transposeMatrix(ma);
    inversible = inverseMatrix(ma, mai);
    std::cout << "det(ma), inversible = " << ma.determinant() << ", " << inversible << "\n";
    std::cout << "mai = \n";
    printMatrix(mai);
    
    MyMatrix<4, 4> mp1({
        0, 0, 1, 0,
        0, 1, 0, 0,
        1, 0, 0, 0,
        0, 0, 0, 1
    });
    MyMatrix<4, 4> mp2({
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        2, 0, 0, 1
    });
    MyMatrix<4, 4> mp3({
        1, 0, 0, 0,
        0, 3, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    });
    MyMatrix<4, 4> mp4(mp1 * mp2 * mp3);
    MyMatrix<4, 4> mpi;
    inversible = inverseMatrix(mp4, mpi);
    std::cout << "det(mp4), inversible = " << mp4.determinant() << ", " << inversible << "\n";
    std::cout << "mpi = \n";
    printMatrix(mpi);
    
    MyMatrix<3, 3> A({
        4, 2, 5,
        3, 2, 5,
        0, 2, 4
    });
    MyMatrix<3, 1> X, b({550, 475, 222});
    MyMatrix<3, 3> InvA;
    inversible = inverseMatrix(A, InvA);
    if(inversible) {
        X = InvA * b;
    }
    std::cout << "X = \n";
    printMatrix(X);
    
    MyMatrix<2, 2> P({
        -1, -4,
        1, 1
    });
    MyMatrix<2, 2> B({
        -1, 0,
        0, 2
    });
    MyMatrix<2, 2> InvP;
    MyMatrix<2, 2> PA;
    MyMatrix<2, 2> MPA;
    inversible = inverseMatrix(P, InvP);
    if(inversible) {
        PA = P * B * InvP;
        identityMatrix(MPA);
        for(int i = 0; i != 11; ++i) {
            MPA = MPA * PA;
        }
    }
    std::cout << "MPA = \n";
    printMatrix(MPA);
    
    MyMatrix<4, 4> mdd({
        5, 2, -6, -3,
        -4, 7, -2, 4,
        -2, 3, 4, 1,
        7, -8, -10, -5
    });
    std::cout << "det(mdd), inversible = " << mdd.determinant() << ", " << mdd.inversible() << "\n";
    
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
