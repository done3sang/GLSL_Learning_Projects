//
//  MyModelComponent.cpp
//  MyGLSL
//
//  Created by xy on 12/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include "MyTemplate.hpp"
#include "MyActorComponent.hpp"
#include "MyFileUtil.hpp"
#include "MyBufferObject.hpp"
#include "MyProgram.hpp"
#include "MyShadingManager.hpp"
#include "MyVertexAttribute.hpp"
#include "MyVertexAttributeManager.hpp"
#include "MyModelComponent.hpp"

MINE_NAMESPACE_BEGIN

MyModelComponent* MyModelComponent::create(void) {
    MyModelComponent *model = new MyModelComponent();
    model->refName("MyModelComponent");
    return model;
}

MyModelComponent* MyModelComponent::createWithModelFile(const std::string &path) {
    MyModelComponent *model = new MyModelComponent();
    model->refName("MyModelComponent");
    model->loadModelFile(path);
    return model;
}

void MyModelComponent::destroy(void) {
    if(_vertexBuffer) {
        _vertexBuffer->release();
        _vertexBuffer = nullptr;
    }
    if(_elementBuffer) {
        _elementBuffer->release();
        _elementBuffer = nullptr;
    }
    if(_program) {
        _program->release();
        _program = nullptr;
    }
}

bool MyModelComponent::loadModelFile(const std::string &path) {
    std::string filedata;
    if(!MyFileUtil::sharedFileUtil()->readFile(path, filedata)) {
        return false;
    }
    
    return loadModelSource(filedata, "position[4]_normal[3]");
}

bool MyModelComponent::loadModelSource(const std::string &source,
                                       const std::string &format,
                                       bool elemented) {
    return false;
}

bool MyModelComponent::loadVertexData(const std::vector<float> &vertexData,
                                     const std::string &format, int primitive) {
    if(vertexData.empty() || !modelPrimitive(primitive)) {
        return false;
    }
    const MyVertexAttribute *att = MyVertexAttributeManager::sharedVertexAttributeManager()->attributeByName(format);
    if(!att) {
        return false;
    }
    
    MyBufferObject *vertexBuf = MyBufferObject::createWithBufferType(MyBufferObject::kBufferArray);
    vertexBuf->bufferData(vertexData.size() * sizeof(float), vertexData.data());

    if(_vertexBuffer) {
        _vertexBuffer->release();
    }
    vertexBuf->addRef();
    
    _vertexBuffer = vertexBuf;
    _modelPrimitive = primitive;
    _vertexAttribute = att;
    
    if(kModelPrimitivePoint == _modelPrimitive) {
        _renderMode = GL_POINTS;
    } else if(kModelPrimitiveLine == _modelPrimitive) {
        _renderMode = GL_LINES;
    } else if(kModelPrimitiveTriangles == _modelPrimitive) {
        _renderMode = GL_TRIANGLES;
    } else if(kModelPrimitiveTriangleStrip == _modelPrimitive) {
        _renderMode = GL_TRIANGLE_STRIP;
    } else if(kModelPrimitiveTriangleFan == _modelPrimitive) {
        _renderMode = GL_TRIANGLE_FAN;
    }
    
    _renderStart = 0;
    _renderCount = static_cast<int>(vertexData.size())/_vertexAttribute->strideSize();
    
    if(!_program) {
        modelProgram("basic");
    }
    
    return true;
}

bool MyModelComponent::loadElementData(const std::vector<unsigned int> &elemData) {
    if(elemData.empty()) {
        return false;
    }
    
    MyBufferObject *elemBuf = MyBufferObject::createWithBufferType(MyBufferObject::kBufferElementArray);
    elemBuf->bufferData(static_cast<int>(elemData.size()) * sizeof(unsigned int), elemData.data());
    
    if(_elementBuffer) {
        _elementBuffer->release();
    }
    
    elemBuf->addRef();
    _elementBuffer = elemBuf;
    _renderCount = static_cast<int>(elemData.size());
    
    return true;
}

void MyModelComponent::modelProgram(const std::string &progName) {
    MyProgram *prog = MyShadingManager::sharedShadingManager()->programByName(progName);
    
    if(!prog) {
        return;
    }
    
    if(_program) {
        _program->release();
    }
    
    prog->addRef();
    _program = prog;
}

MINE_NAMESPACE_END
