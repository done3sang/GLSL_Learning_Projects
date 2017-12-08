//
//  MyXMLDocument.cpp
//  MyGLSL
//
//  Created by xy on 08/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <cassert>
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
    doc->autorelase();
    return doc;
}

bool MyXMLDocument::loadFromFile(const std::string &path) {
    std::string filedata;
    if(!MyErrorDesc::invokeErrorFailed(MyFileUtil::sharedFileUtil()->readFile(path, filedata))) {
        return false;
    }
    
    return parseXML(filedata);
}

bool MyXMLDocument::parseXML(const std::string &xmldata) {
    assert(!xmldata.empty() && "MyXMLDocument::parseXML = xml data cannot be empty");
    
    MyXMLNode *rootNode = MyXMLNode::create(MyXMLNode::kXMLNodeTypeRoot);
    MyXMLNode *childNode = nullptr;
    std::string::size_type currpos(0), nextpos, overpos;
    std::string nodeOverKey;
    char curr, next;
    
    while(currpos < xmldata.length()) {
        curr = xmldata[currpos];
        
        if(MyStringUtil::whitespace(curr)) {
            ++currpos;
            continue;
        }
        
        nextpos = currpos + 1;
        if('<' != curr || nextpos >= xmldata.length()) {
            return MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
        }
        
        next = xmldata[nextpos];
        if('?' == next) {
            if(!parseAttribute(xmldata, overpos, currpos)) {
                return false;
            }
            currpos = overpos;
        } else if('!' == next) {
            if(!parseComment(xmldata, overpos, currpos)) {
                return false;
            }
            currpos = overpos;
        } else if(MyStringUtil::digit_alpha(next)) {
            MyXMLNode *elemNode = parseElement(xmldata, overpos, currpos, xmldata.length() - 1);
            
            if(!elemNode) {
                return false;
            }
            
            if(!childNode) {
                rootNode->childNode(elemNode);
            } else {
                childNode->siblingNode(elemNode);
            }
            childNode = elemNode;
            
            currpos = overpos;
        } else {
            return MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
        }
    }
    
    return true;
}

bool MyXMLDocument::parseComment(const std::string &xmldata,
                                 std::string::size_type &nextpos,
                                 const std::string::size_type pos) {
    std::string::size_type xmlpos = xmldata.find_first_of("<!--", pos);
    
    if(pos != xmlpos || xmlpos + 6 >= xmldata.length()) {
        MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
        return false;
    }
    xmlpos += 3;
    
    std::string::size_type overpos = xmldata.find_first_of("-->", xmlpos);
    if(std::string::npos == overpos) {
        MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
        return false;
    }
    
    nextpos = overpos + 3;
    return true;
}

// <?xml ?>
bool MyXMLDocument::parseAttribute(const std::string &xmldata,
                                     std::string::size_type &nextpos,
                                     const std::string::size_type pos) {
    std::string::size_type xmlpos = xmldata.find_first_of("<?xml", pos);
    
    if(pos != xmlpos || xmlpos + 7 >= xmldata.length()) {
        MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
        return false;
    }
    
    xmlpos += 5;
    if(!MyStringUtil::whitespace(xmldata[xmlpos])) {
        MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
        return false;
    }
    
    ++xmlpos;
    std::string::size_type overpos = xmldata.find_first_of("?>", xmlpos);
    if(std::string::npos == overpos) {
        MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
        return false;
    }
    
    std::string::size_type mappos;
    std::string key, value;
    while(xmlpos < overpos) {
        if(MyStringUtil::whitespace(xmldata[xmlpos])) {
            ++xmlpos;
            continue;
        }
        
        mappos = xmlpos;
        while(MyStringUtil::digit_alpha(xmldata[mappos])) {
            ++mappos;
        }
        if(xmlpos == mappos) {
            MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
            return false;
        }
        if(!MyStringUtil::whitespace(xmldata[mappos]) && '='  != xmldata[mappos]) {
            MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
            return false;
        }
        key = xmldata.substr(xmlpos, mappos - xmlpos);
        xmlpos = mappos;
        while(MyStringUtil::whitespace(xmldata[xmlpos])) {
            ++xmlpos;
        }
        if('=' != xmldata[xmlpos]) {
            MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
            return false;
        }
        while(MyStringUtil::whitespace(xmldata[++xmlpos]));
        if('\"' != xmldata[xmlpos]) {
            MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
            return false;
        }
        ++xmlpos;
        mappos = xmlpos;
        while(mappos < overpos && '\"' != xmldata[mappos]) {
            if(MyStringUtil::newline(xmldata[mappos])) {
                MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
                return false;
            }
            ++mappos;
        }
        if(mappos >= overpos) {
            MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
            return false;
        }
        value = xmldata.substr(xmlpos, mappos - xmlpos);
        _attributeMap[key] = value;
        xmlpos = mappos + 1;
    }
    
    nextpos = overpos + 2;
    return true;
}

MyXMLNode* MyXMLDocument::parseElement(const std::string &xmldata,
                                       std::string::size_type &nextpos,
                                       const std::string::size_type pos,
                                       std::string::size_type endpos) {
    std::string::size_type xmlpos(pos + 1);
    std::string::size_type keypos(pos + 1);
    char keychar;
    
    if(std::string::npos == endpos) {
        endpos = xmldata.length();
    }
    
    while(keypos < endpos) {
        keychar = xmldata[keypos];
        if(MyStringUtil::digit_alpha(keychar)) {
            ++keypos;
            continue;
        } else if('>' == keychar) {
            break;
        } else {
            MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
            return nullptr;
        }
    }
    
    if(keypos >= endpos) {
        MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
        return nullptr;
    }
    
    std::string key(xmldata.substr(xmlpos, keypos - xmlpos));
    std::string overkey("</");
    std::string::size_type overpos;
    
    overkey += key;
    overkey += ">";
    overpos = xmldata.find_first_of(overkey, keypos + 1);
    if(std::string::npos == overpos || overpos >= endpos) {
        MyErrorDesc::invokeErrorFailed(MyErrorDesc::kErrXMLParseFailed);
        return nullptr;
    }
    
    MyXMLNode *node = nullptr;
    
    xmlpos = keypos;
    while(MyStringUtil::whitespace(xmldata[++xmlpos]));
    if('<' == xmldata[xmlpos]) {
        node = parseElement(xmldata, nextpos, xmlpos, overpos);
    } else {
        node = MyXMLNode::create(MyXMLNode::kXMLNodeTypeText);
        node->nodeName(key);
        
        std::string::size_type valuepos(overpos);
        while(valuepos >= xmlpos && MyStringUtil::whitespace(xmldata[valuepos])) {
            --valuepos;
        }
        node->nodeValue(xmldata.substr(xmlpos, valuepos - xmlpos + 1));
        nextpos = overpos + overkey.length();
    }
    
    return node;
}

MINE_NAMESPACE_END
