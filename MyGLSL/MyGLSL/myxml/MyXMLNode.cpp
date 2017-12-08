//
//  MyXMLNode.cpp
//  MyGLSL
//
//  Created by xy on 08/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyTemplate.hpp"
#include "MyXMLNode.hpp"

MINE_NAMESPACE_BEGIN

const int MyXMLNode::kXMLNodeTypeRoot = 0;
const int MyXMLNode::kXMLNodeTypeDeclaration = 1;
const int MyXMLNode::kXMLNodeTypeElement = 2;
const int MyXMLNode::kXMLNodeTypeComment = 3;
const int MyXMLNode::kXMLNodeTypeText = 4;

MyXMLNode* MyXMLNode::create(int nodeType) {
    MyXMLNode *node = new MyXMLNode(nodeType);
    node->refName("MyXMLNode");
    node->autorelase();
    return node;
}

void MyXMLNode::destroy(void) {
    if(_siblingNode) {
        _siblingNode->release();
    }
}

void MyXMLNode::siblingNode(Mine::MyXMLNode *node) {
    if(_siblingNode) {
        _siblingNode->release();
    }
    if(node) {
        node->addRef();
    }
    _siblingNode = node;
}

void MyXMLNode::childNode(Mine::MyXMLNode *node) {
    if(_childNode) {
        _childNode->release();
    }
    if(node) {
        node->addRef();
    }
    _childNode = node;
}

MINE_NAMESPACE_END
