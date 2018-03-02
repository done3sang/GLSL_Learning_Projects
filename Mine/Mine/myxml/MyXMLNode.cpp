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

MyXMLNode* MyXMLNode::createWithType(int nodeType) {
    MyXMLNode *node = new MyXMLNode(nodeType);
    node->objectName("MyXMLNode");
    return node;
}

MyXMLNode* MyXMLNode::createWithNameType(const std::string &name,
                                         int nodeType) {
    MyXMLNode *node = new MyXMLNode(name, nodeType);
    node->objectName(name + "_MyXMLNode");
    return node;
}

void MyXMLNode::destroy(void) {
    if(_childNode) {
        _childNode->release();
        _childNode = nullptr;
    }
    if(_siblingNode) {
        _siblingNode->release();
        _siblingNode = nullptr;
    }
}

void MyXMLNode::siblingNode(MyXMLNode *node) {
    if(_siblingNode) {
        _siblingNode->release();
    }
    if(node) {
        node->addRef();
    }
    _siblingNode = node;
}

void MyXMLNode::childNode(MyXMLNode *node) {
    if(_childNode) {
        _childNode->release();
    }
    if(node) {
        node->addRef();
    }
    _childNode = node;
}

MINE_NAMESPACE_END
