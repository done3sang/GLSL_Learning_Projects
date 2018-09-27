//
//  MyVertexAttribute.hpp
//  Mine
//
//  Created by xy on 25/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyVertex_hpp
#define MyVertex_hpp

#include <vector>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyUniqueObject;

class MyVertex final: public MyUniqueObject {
public:
    static MyVertex* vertex(void);
    static MyVertex* vertexWithFormat(const char *format);
    
    struct VertexAttribute {
        int attrib;
        int size;
        int offset;
    };
    
    FORCEINLINE bool ready(void) const { return _loaded; }
    FORCEINLINE const char* format(void) const { return _format; }
    FORCEINLINE const std::vector<VertexAttribute>& attributeMap(void) const { return _attributeMap; }
    FORCEINLINE int stride(void) const { return _stride; }
    FORCEINLINE int strideSize(void) const { return _stride/sizeof(float); }
    
private:
    FORCEINLINE MyVertex(void):
    _format(nullptr),
    _loaded(false),
    _stride(0) {}
    MyVertex(const char *format);
    FORCEINLINE virtual ~MyVertex(void) {}
    
    const char* _format;
    bool _loaded;
    int _stride;
    std::vector<VertexAttribute> _attributeMap;
    
    //! position[3]_normal[3]_texcoord[2]_texcoord1[2]
    bool initWithFormat(const char *format);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyVertexAttribute_hpp */
