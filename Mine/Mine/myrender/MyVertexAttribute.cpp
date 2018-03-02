//
//  MyVertexAttribute.cpp
//  Mine
//
//  Created by xy on 25/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <cstdlib>
#include "MyTemplate.hpp"
#include "MyProgram.hpp"
#include "MyVertexAttribute.hpp"

MINE_NAMESPACE_BEGIN

MyVertexAttribute* MyVertexAttribute::create(void) {
    MyVertexAttribute *att = new MyVertexAttribute();
    att->objectName("MyVertexAttribute");
    return att;
}

MyVertexAttribute* MyVertexAttribute::createWithFormat(const std::string &fmt) {
    MyVertexAttribute *att = new MyVertexAttribute(fmt);
    att->objectName("MyVertexAttribute");
    return att;
}

//! position[3]_normal[3]_texcoord0[2]_texcoord1[2]
bool MyVertexAttribute::loadFormat(const std::string &format) {
    if(format.empty()) {
        return false;
    }
    
    bool formated(false), found(false);
    VertexAttribute va;
    std::string::size_type pos(0), bracket(0);
    std::string::value_type ch;
    int attrib(0), size(0), stride(0);
    
    while(pos < format.size()) {
        ch = format[pos];
        
        if('[' == ch) {
            bracket = format.find_first_of(']', pos);
            if(std::string::npos == bracket || !found) {
                return false;
            }
            size = std::atoi(format.substr(pos + 1, bracket - pos - 1).c_str());
            if(0 >= size) {
                return false;
            }
            va.attrib = attrib;
            va.size = size;
            va.offset = stride;
            stride += size * sizeof(float);
            
            if(!formated) {
                _attributeMap.clear();
                formated = true;
            }
            _attributeMap.push_back(va);
            found = false;
            pos = bracket + 1;
        } else if('p' == ch && pos == format.find("position")) {
            // position
            pos += 8;
            attrib = MyProgram::kAttribPosition;
            found = true;
        } else if('n' == ch && pos == format.find("normal")) {
            // normal
            pos += 6;
            attrib = MyProgram::kAttribNormal;
            found = true;
        } else if('t' == ch && pos == format.find("texcoord0")) {
            // texcoord0
            pos += 9;
            attrib = MyProgram::kAttribTexCoord0;
            found = true;
        } else if('c' == ch && pos == format.find("color")) {
            // color
            pos += 5;
            attrib = MyProgram::kAttribColor;
            found = true;
        } else {
            ++pos;
        }
    }
    if(formated) {
        _attributeName = format;
        _loaded = true;
        _stride = stride;
    }
    
    return formated;
}

MINE_NAMESPACE_END
