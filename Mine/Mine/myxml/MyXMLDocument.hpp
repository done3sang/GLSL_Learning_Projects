//
//  MyXMLDocument.hpp
//  MyGLSL
//
//  Created by xy on 08/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyXMLDocument_hpp
#define MyXMLDocument_hpp

#include <string>
#include <unordered_map>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyUniqueObject;
class MyXMLNode;

class MyXMLDocument final: public MyUniqueObject {
public:
    static MyXMLDocument* create(void);
    static MyXMLDocument* createWithDocument(const std::string &path);
    
    bool loadDocument(const std::string &path);
    
    const auto& attributeMap(void) const { return _attributeMap; }
    bool attributeByName(const std::string &name, std::string &value) const;
    MyXMLNode* rootNode(void) const { return _rootNode; }
    
private:
    MyXMLDocument(void): _rootNode(nullptr) {}
    ~MyXMLDocument(void) { destroy(); }
    
    std::unordered_map<std::string, std::string> _attributeMap;
    MyXMLNode *_rootNode;
    
    void destroy(void);
    void rootNode(MyXMLNode *node);
    bool parseXML(const std::string &xmldata);
    bool parseAttribute(const std::string &xmldata,
                     std::string::size_type &nextpos,
                     const std::string::size_type pos = 0);
    
    std::string::size_type skipwhitespace(const std::string &xmldata,
                                          const std::string::size_type pos = 0);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyXMLDocument_hpp */
