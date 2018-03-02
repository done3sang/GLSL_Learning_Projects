//
//  MyXMLNode.hpp
//  MyGLSL
//
//  Created by xy on 08/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyXMLNode_hpp
#define MyXMLNode_hpp

#include <string>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyUniqueObject;

class MyXMLNode final: public MyUniqueObject {
public:
    static MyXMLNode* createWithType(int nodeType = kXMLNodeTypeElement);
    static MyXMLNode* createWithNameType(const std::string &name,
                                         int nodeType = kXMLNodeTypeElement);
    
    const std::string& nodeName(void) const { return _nodeName; }
    const std::string& nodeValue(void) const { return _nodeValue; }
    MyXMLNode* siblingNode(void) const { return _siblingNode; }
    MyXMLNode* childNode(void) const { return _childNode; }
    int nodeType(void) const { return _nodeType; }
    bool element(void) const { return kXMLNodeTypeElement == _nodeType; }
    bool text(void) const { return kXMLNodeTypeText == _nodeType; }
    bool iteratable(void) const {
        return kXMLNodeTypeElement == _nodeType || kXMLNodeTypeText == _nodeType;
    }
    
public:
    static const int kXMLNodeTypeRoot;
    static const int kXMLNodeTypeDeclaration;
    static const int kXMLNodeTypeElement;
    static const int kXMLNodeTypeComment;
    static const int kXMLNodeTypeText;
    
private:
    explicit
    MyXMLNode(const std::string &name, int nodeType = kXMLNodeTypeElement):
        _nodeName(name), _nodeType(nodeType), _siblingNode(nullptr), _childNode(nullptr) {}
    explicit
    MyXMLNode(int nodeType = kXMLNodeTypeElement): _nodeType(nodeType), _siblingNode(nullptr), _childNode(nullptr) {}
    ~MyXMLNode(void) { destroy(); }
    
    int _nodeType;
    std::string _nodeName;
    std::string _nodeValue;
    MyXMLNode *_siblingNode;
    MyXMLNode *_childNode;
    
    friend class MyXMLDocument;
    
    void siblingNode(MyXMLNode *node);
    void childNode(MyXMLNode *node);
    void nodeType(int nt) { _nodeType = nt; }
    void nodeName(const std::string &name) {
        _nodeName = name;
        objectName(name + "_MyXMLNode");
    }
    void nodeValue(const std::string &value) { _nodeValue = value; }
    
    void destroy(void);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyXMLNode_hpp */
