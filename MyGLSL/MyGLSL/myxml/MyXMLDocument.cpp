//
//  MyXMLDocument.cpp
//  MyGLSL
//
//  Created by xy on 08/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <cassert>
#include <stack>
#include "MyTemplate.hpp"
#include "MyFileUtil.hpp"
#include "MyErrorDesc.hpp"
#include "MyXMLNode.hpp"
#include "MyStringUtil.hpp"
#include "MyXMLDocument.hpp"

MINE_NAMESPACE_BEGIN

MyXMLDocument* MyXMLDocument::create(void) {
    MyXMLDocument *doc = new MyXMLDocument;
    doc->refName("MyXMLDocument");
    return doc;
}

bool MyXMLDocument::attributeByName(const std::string &name,
                                    std::string &value) const {
    auto iter = _attributeMap.find(name);
    if(_attributeMap.end() != iter) {
        value = iter->second;
        return true;
    }
    return false;
}

void MyXMLDocument::rootNode(MyXMLNode *node) {
    if(_rootNode) {
        _rootNode->release();
    }
    if(node) {
        node->addRef();
    }
    _rootNode = node;
}

bool MyXMLDocument::loadDocument(const std::string &path) {
    std::string filedata;
    if(!MyFileUtil::sharedFileUtil()->readFile(path, filedata)) {
        return false;
    }
    
    return parseXML(filedata);
}

bool MyXMLDocument::parseXML(const std::string &xmldata) {
    assert(!xmldata.empty() && "MyXMLDocument::parseXML = xml data cannot be empty");
    
    std::stack<std::string> docstack;
    std::stack<MyXMLNode*> nodestack, firststack;
    MyXMLNode *firstnode = nullptr, *currnode, *prevnode, *childnode, *siblingnode;
    MyXMLNode *rootnode = nullptr;
    std::string::size_type currpos(0), nextpos, keypos, keyendpos, valpos(0), valendpos(0);
    std::string key, value;
    const std::string::size_type xmllen(xmldata.length());
    char curr;
    bool endflag(false);
    
    while(currpos < xmllen) {
        curr = xmldata[currpos];
        if(MyStringUtil::whitespace(curr)) {
            ++currpos;
            continue;
        }
        
        if('<' == curr) {
            if(++currpos >= xmllen) {
                MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
                return false;
            }
            
            curr = xmldata[currpos];
            if('?' == curr) {
                // <?xml ?>
                if(currpos + 5 >= xmllen ||
                   'x' != xmldata[++currpos] ||
                   'm' != xmldata[++currpos] ||
                   'l' != xmldata[++currpos] ||
                   !parseAttribute(xmldata, nextpos, ++currpos)) {
                    MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
                    return false;
                }
                currpos = nextpos;
            } else if('!' == curr) {
                // <¡-- -->
                if(currpos + 2 >= xmllen ||
                   '-' != xmldata[++currpos] ||
                   '-' != xmldata[++currpos]) {
                    MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
                    return false;
                }
                
                currpos = xmldata.find("-->", ++currpos);
                if(std::string::npos == currpos) {
                    if(docstack.empty()) {
                        return true;
                    } else {
                        MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
                        return false;
                    }
                }
                currpos += 3;
            } else {
                if(xmllen <= (currpos = skipwhitespace(xmldata, currpos))) {
                    MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
                    return false;
                }
                if('/' == xmldata[currpos]) {
                    endflag = true;
                    if(xmllen <= (currpos = skipwhitespace(xmldata, ++currpos))) {
                        MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
                        return false;
                    }
                } else {
                    endflag = false;
                }
                keypos = currpos;
                while(MyStringUtil::variable(xmldata[currpos])) {
                    ++currpos;
                    if(currpos >= xmllen) {
                        MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
                        return false;
                    }
                }
                if(keypos == currpos) {
                    MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
                    return false;
                }
                keyendpos = currpos;
                if(xmllen <= (currpos = skipwhitespace(xmldata, currpos))) {
                    MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
                    return false;
                }
                curr = xmldata[currpos];
                if('>' != curr) {
                    MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
                    return false;
                }
                ++currpos;
                key = xmldata.substr(keypos, keyendpos - keypos);
                if(endflag) {
                    if(docstack.empty() || docstack.top() != key) {
                        MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
                        return false;
                    }
                    docstack.pop();
                    
                    currnode = nodestack.top();
                    if(valpos > 0) {
                        currnode->nodeType(MyXMLNode::kXMLNodeTypeText);
                        currnode->nodeValue(xmldata.substr(valpos, valendpos - valpos));
                    }
                    nodestack.pop();
                    
                    if(nodestack.empty()) {
                        // root node
                        rootnode = currnode;
                    } else {
                        prevnode = nodestack.top();
                        childnode = prevnode->childNode();
                        if(0 == valpos) {
                            firststack.pop();
                        }
                        if(childnode) {
                            firststack.top()->siblingNode(currnode);
                            firststack.pop();
                        } else {
                            prevnode->childNode(currnode);
                        }
                        firststack.push(currnode);
                    }
                    valpos = 0;
                } else {
                    currnode = MyXMLNode::createWithNameType(key);
                    docstack.push(key);
                    nodestack.push(currnode);
                }
            }
        } else {
            valpos = currpos;
            if(docstack.empty() ||
               std::string::npos == (currpos = xmldata.find('<', ++currpos))) {
                MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
                return false;
            }
            valendpos = currpos;
        }
    }
    
    if(!docstack.empty()) {
        MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
        return false;
    }
    
    rootNode(rootnode);
    return true;
}

bool MyXMLDocument::parseAttribute(const std::string &xmldata,
                                   std::string::size_type &nextpos,
                                   const std::string::size_type pos) {
    std::string::size_type xmlpos(pos), keypos, valpos, keyendpos;
    const std::string::size_type xmllen(xmldata.length());
    char xmlchar;
    bool endflag(false);
    
    while(xmlpos < xmllen) {
        xmlchar = xmldata[xmlpos];
        
        if('?' == xmlchar) {
            if(++xmlpos >= xmllen) {
                break;
            }
            xmlchar = xmldata[xmlpos];
            if('>' == xmlchar) {
                nextpos = ++xmlpos;
                endflag = true;
                break;
            }
        }
        if(MyStringUtil::variable(xmlchar)) {
            keypos = xmlpos;
            while(++xmlpos < xmllen && MyStringUtil::variable(xmldata[xmlpos]));
            if(xmlpos >= xmllen) {
                break;
            }
            keyendpos = xmlpos;
            if((xmlpos = skipwhitespace(xmldata, xmlpos)) >= xmllen) {
                break;
            }
            xmlchar = xmldata[xmlpos];
            if('=' == xmlchar) {
                ++xmlpos;
                if((xmlpos = skipwhitespace(xmldata, xmlpos)) >= xmllen) {
                    break;
                }
                xmlchar = xmldata[xmlpos];
                if('"' == xmlchar) {
                    valpos = ++xmlpos;
                    xmlpos = xmldata.find('"', xmlpos);
                    if(std::string::npos == xmlpos) {
                        break;
                    }
                    _attributeMap[xmldata.substr(keypos, keyendpos - keypos)] = xmldata.substr(valpos, xmlpos - valpos);
                    ++xmlpos;
                }
            }
        } else {
            ++xmlpos;
        }
    }
    
    return endflag;
}

std::string::size_type MyXMLDocument::skipwhitespace(const std::string &xmldata,
                                                     const std::string::size_type pos) {
    assert(pos < xmldata.length() && "MyXMLDocument::skipwhitespace = pos invalid");
    
    std::string::size_type idxpos(pos);
    while(idxpos < xmldata.length() && MyStringUtil::whitespace(xmldata[idxpos])) {
        ++idxpos;
    }
    
    return idxpos;
}

MINE_NAMESPACE_END
