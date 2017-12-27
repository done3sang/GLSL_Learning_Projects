//
//  MyModelComponent.hpp
//  MyGLSL
//
//  Created by xy on 12/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyModelComponent_hpp
#define MyModelComponent_hpp

#include <vector>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyActorComponent;
class MyBufferObject;
class MyProgram;
class MyVertexAttribute;

class MyModelComponent: public MyActorComponent {
public:
    static constexpr int kModelPrimitiveNone = 0;
    static constexpr int kModelPrimitivePoint = 1;
    static constexpr int kModelPrimitiveLine = 2;
    static constexpr int kModelPrimitiveTriangles = 3;
    static constexpr int kModelPrimitiveTriangleStrip = 4;
    static constexpr int kModelPrimitiveTriangleFan = 5;
    static constexpr int kModelPrimitiveBegin = kModelPrimitivePoint;
    static constexpr int kModelPrimitiveEnd = kModelPrimitiveTriangleFan;
    
public:
    static MyModelComponent* create(void);
    static MyModelComponent* createWithModelFile(const std::string &path);
    
    bool loadModelFile(const std::string &path);
    bool loadModelSource(const std::string &source,
                         const std::string &format,
                         bool elemented = false);
    bool loadVertexData(const std::vector<float> &data,
                       const std::string &format,
                       int primitive = kModelPrimitiveTriangles);
    bool loadElementData(const std::vector<int> &data);
    
    int modelFormat(void) const { return _modelFormat; }
    int modelPrimitive(void) const { return _modelPrimitive; }
    bool modelElemented(void) const { return _elementBuffer; }
    bool modelCompleted(void) const { return _vertexBuffer; }
    bool modelPrimitive(int prim) const { return kModelPrimitiveBegin <= prim && prim <= kModelPrimitiveEnd; }
    const MyVertexAttribute* modelVertexAttribute(void) const { return _vertexAttribute; }
    MyBufferObject* modelVertexBuffer(void) const { return _vertexBuffer; }
    MyBufferObject* modelElementBuffer(void) const { return _elementBuffer; }
    MyProgram* modelProgram(void) const { return _program; }
    int renderMode(void) const { return _renderMode; }
    int renderStart(void) const { return _renderStart; }
    int renderCount(void) const { return _renderCount; }
    int renderType(void) const { return _renderType; }
    
    void modelProgram(const std::string &progName);
    
private:
    MyModelComponent(void):
    MyActorComponent(MyActorComponent::kComponentTypeModel,
                     "Model", MyActorComponent::kComponentGroupModel),
    _modelPrimitive(kModelPrimitiveNone), _vertexAttribute(nullptr),
    _vertexBuffer(nullptr), _elementBuffer(nullptr), _program(nullptr),
    _renderMode(0), _renderStart(0), _renderCount(0), _renderType(0) {}
    ~MyModelComponent(void) { destroy(); }
    
    int _modelFormat;
    int _modelPrimitive;
    MyBufferObject *_vertexBuffer;
    MyBufferObject *_elementBuffer;
    MyProgram *_program;
    int _renderMode;
    int _renderStart;
    int _renderCount;
    int _renderType;
    const MyVertexAttribute *_vertexAttribute;
    
    void destroy(void);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyModelComponent_hpp */
