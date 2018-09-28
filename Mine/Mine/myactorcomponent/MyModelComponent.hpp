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
class MyMaterial;
class MyVertex;
template<typename T>
class MyData;

class MyModelComponent: public MyActorComponent {
public:
    static const int kModelPrimitivePoint;
    static const int kModelPrimitiveLine;
    static const int kModelPrimitiveTriangles;
    static const int kModelPrimitiveTriangleStrip;
    static const int kModelPrimitiveTriangleFan;
    
public:
    static MyModelComponent* model(void);
    static MyModelComponent* modelWithContentsOfFile(const char *path);
    static MyModelComponent* modelWithData(int primitive,
                                           const MyData<float> *vertexData,
                                           const char *vertexFormat,
                                           const MyData<unsigned int> *elementData = nullptr);
    
public:
    bool loadWithContentsOfFile(const char *path);
    bool loadWithData(int primitive,
                      const MyData<float> *vertexData,
                      const char *vertexFormat,
                      const MyData<unsigned int> *elementData = nullptr);
    
    FORCEINLINE int primitive(void) const { return _primitive; }
    FORCEINLINE const MyVertex* vertex(void) const { return _vertex; }
    FORCEINLINE const MyBufferObject* vertexBuffer(void) const { return _vertexBuffer; }
    FORCEINLINE const MyBufferObject* elementBuffer(void) const { return _elementBuffer; }
    FORCEINLINE const MyMaterial* material(void) const { return _material; }
    FORCEINLINE int renderStart(void) const { return _renderStart; }
    FORCEINLINE int renderCount(void) const { return _renderCount; }
    
    void material(MyMaterial *newMat);
    
    void purge(void);
    
private:
    FORCEINLINE MyModelComponent(void):
    MyActorComponent(MyActorComponent::kComponentTypeModel,
                     MyActorComponent::kComponentGroupModel),
    _primitive(kModelPrimitiveTriangles),
    _vertex(nullptr),
    _vertexBuffer(nullptr),
    _elementBuffer(nullptr),
    _material(nullptr),
    _renderStart(0),
    _renderCount(0) {}
    ~MyModelComponent(void);
    
    int _primitive;
    MyVertex *_vertex;
    MyBufferObject *_vertexBuffer;
    MyBufferObject *_elementBuffer;
    MyMaterial *_material;
    int _renderStart;
    int _renderCount;
    
    bool initWithContentsOfFile(const char *path);
    bool initWithData(int primitive,
                      const MyData<float> *vertexData,
                      const char *vertexFormat,
                      const MyData<unsigned int> *elementData = nullptr);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyModelComponent_hpp */
