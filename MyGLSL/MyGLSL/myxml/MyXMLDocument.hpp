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
#include <map>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyUniqueRef;
class MyXMLNode;

class MyXMLDocument: public MyUniqueRef {
public:
    static MyXMLDocument* create(void);
    
    bool loadFromFile(const std::string &path);
    
    const std::string& attributeByName(const std::string &name);
    MyXMLNode* rootNode(void) const { return _rootNode; }
    
private:
    MyXMLDocument(void): _rootNode(nullptr) {}
    ~MyXMLDocument(void) {}
    
    std::map<std::string, std::string> _attributeMap;
    MyXMLNode *_rootNode;
    
    void rootNode(MyXMLNode *node);
    bool parseXML(const std::string &xmldata);
    
    bool parseAttribute(const std::string &xmldata,
                        std::string::size_type &nextpos,
                        const std::string::size_type pos = 0);
    bool parseComment(const std::string &xmldata,
                      std::string::size_type &nextpos,
                      const std::string::size_type pos = 0);
    MyXMLNode* parseElement(const std::string &xmldata,
                            std::string::size_type &nextpos,
                            const std::string::size_type pos = 0,
                            std::string::size_type endpos = std::string::npos);
    MyXMLNode* parseText(const std::string &xmldata,
                         std::string::size_type &nextpos,
                         const std::string::size_type pos = 0);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyXMLDocument_hpp */
