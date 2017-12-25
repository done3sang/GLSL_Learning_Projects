//
//  MyVertexAttribute.hpp
//  Mine
//
//  Created by xy on 25/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyVertexAttribute_hpp
#define MyVertexAttribute_hpp

#include <vector>
#include <string>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyUniqueRef;

class MyVertexAttribute: public MyUniqueRef {
public:
    struct VertexAttribute {
        int attrib;
        int size;
        int stride;
        int offset;
    };
    
    bool formatLoaded(void) const { return _loaded; }
    
    bool loadFormat(const std::string &format);
    
private:
    MyVertexAttribute(const std::string &format): _attributeName(format) { loadFormat(format); }
    ~MyVertexAttribute(void) {}
    
    std::string _attributeName;
    bool _loaded;
    std::vector<VertexAttribute> _attributeMap;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyVertexAttribute_hpp */
