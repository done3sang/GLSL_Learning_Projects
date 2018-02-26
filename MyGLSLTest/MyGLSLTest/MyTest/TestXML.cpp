//
//  TestXML.cpp
//  MyGLSLTest
//
//  Created by xy on 26/02/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#include <iostream>
#include "TestXML.hpp"

USING_MINE_NAMESPACE;

namespace {
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
}

void XMLTest::testXML(void) {
    
}

