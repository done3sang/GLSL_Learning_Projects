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
    static MyVertexAttribute* create(void);
    static MyVertexAttribute* createWithFormat(const std::string &fmt);
    
    struct VertexAttribute {
        int attrib;
        int size;
        int offset;
    };
    
    bool loaded(void) const { return _loaded; }
    const std::string& attributeName(void) const { return _attributeName; }
    const std::vector<VertexAttribute>& attributeMap(void) const { return _attributeMap; }
    int stride(void) const { return _stride; }
    int strideSize(void) const { return _stride/sizeof(float); }
    
    //! position[3]_normal[3]_texcoord[2]_texcoord1[2]
    bool loadFormat(const std::string &format);
    
private:
    MyVertexAttribute(void): _loaded(false), _stride(0) {}
    MyVertexAttribute(const std::string &format): MyVertexAttribute() { loadFormat(format); }
    ~MyVertexAttribute(void) {}
    
    std::string _attributeName;
    bool _loaded;
    int _stride;
    std::vector<VertexAttribute> _attributeMap;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyVertexAttribute_hpp */
