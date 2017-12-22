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

class MyModelComponent: public MyActorComponent {
public:
    static constexpr int kModelFormatNone = 0;
    static constexpr int kModelFormatV3N3T2 = 1;
    static constexpr int kModelFormatV3C3 = 2;
    static constexpr int kModelFormatV3N3C3 = 3;
    static constexpr int kModelFormatBegin = kModelFormatV3N3T2;
    static constexpr int kModelFormatEnd = kModelFormatV3N3C3;
    
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
                         int format = kModelFormatV3N3T2,
                         bool elemented = false);
    bool loadVertexData(const std::vector<float> &data,
                       int format = kModelFormatV3N3T2,
                       int primitive = kModelPrimitiveTriangles);
    bool loadElementData(const std::vector<int> &data);
    
    int modelFormat(void) const { return _modelFormat; }
    int modelPrimitive(void) const { return _modelPrimitive; }
    bool modelElemented(void) const { return _elementBuffer; }
    bool modelCompleted(void) const { return _vertexBuffer; }
    bool modelFormat(int fmt) const { return kModelFormatBegin <= fmt && fmt <= kModelFormatEnd; }
    bool modelPrimitive(int prim) const { return kModelPrimitiveBegin <= prim && prim <= kModelPrimitiveEnd; }
    const MyBufferObject* modelVertexBuffer(void) const { return _vertexBuffer; }
    const MyBufferObject* modelElementBuffer(void) const { return _elementBuffer; }
    
private:
    MyModelComponent(void):
    MyActorComponent(MyActorComponent::kComponentTypeModel,
                     "Model", MyActorComponent::kComponentGroupModel),
    _modelFormat(kModelFormatNone), _modelPrimitive(kModelPrimitiveNone),
    _vertexBuffer(nullptr), _elementBuffer(nullptr) {}
    ~MyModelComponent(void) { destroy(); }
    
    int _modelFormat;
    int _modelPrimitive;
    MyBufferObject *_vertexBuffer;
    MyBufferObject *_elementBuffer;
    
    void destroy(void);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyModelComponent_hpp */
