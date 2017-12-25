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
#include "MyModelComponent.hpp"

MINE_NAMESPACE_BEGIN

MyModelComponent::VertexAttribute MyModelComponent::vertexByFormat(int fmt) {
    VertexAttribute va;
    
    switch(fmt) {
        case kModelFormatV3N3T2:
            va.attrib = MyProgram::kAttribPosition;
            va.size = 3 * sizeof(float);
            va.stride = 6 * sizeof(float);
            va.offset = 0;
            break;
            
        case kModelFormatV3C3:
            va.attrib = MyProgram::kAttribPosition;
            va.size = 3 * sizeof(float);
            va.stride = 6 * sizeof(float);
            va.offset = 0;
            break;
    }
}

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
    
    return loadModelSource(filedata);
}

bool MyModelComponent::loadVertexData(const std::vector<float> &data,
                                     int format, int primitive) {
    if(data.empty() || !modelFormat(format) || !modelPrimitive(primitive)) {
        return false;
    }
    
    MyBufferObject *vertexBuf = MyBufferObject::createWithBufferType(MyBufferObject::kBufferArray);
    vertexBuf->bufferData(static_cast<int>(data.size()), &data[0]);
    
    if(_vertexBuffer) {
        _vertexBuffer->release();
    }
    vertexBuf->addRef();
    
    _vertexBuffer = vertexBuf;
    _modelFormat = format;
    _modelPrimitive = primitive;
    
    buildVertexAttribute(data.size());
    
    return true;
}

bool MyModelComponent::loadElementData(const std::vector<int> &data) {
    if(data.empty()) {
        return false;
    }
    
    MyBufferObject *elemBuf = MyBufferObject::createWithBufferType(MyBufferObject::kBufferElementArray);
    elemBuf->bufferData(static_cast<int>(data.size()), &data[0]);
    
    if(_elementBuffer) {
        _elementBuffer->release();
    }
    
    elemBuf->addRef();
    _elementBuffer = elemBuf;
    
    return true;
}

void MyModelComponent::buildVertexAttribute(size_t vertexBufferSize) {
    VertexAttribute va;
    int stride(32);
    
    _vertexAttribute.clear();
    switch(_modelFormat) {
        case kModelFormatV3N3T2:
            stride = 8 * sizeof(float);
            
            va.attrib = MyProgram::kAttribPosition;
            va.size = 3 * sizeof(float);
            va.stride = stride;
            va.offset = 0;
            _vertexAttribute.push_back(va);
            
            va.attrib = MyProgram::kAttribNormal;
            va.size = 3 * sizeof(float);
            va.stride = stride;
            va.offset = 3 * sizeof(float);
            _vertexAttribute.push_back(va);
            
            va.attrib = MyProgram::kAttribTexCoord0;
            va.size = 2 * sizeof(float);
            va.stride = stride;
            va.offset = 6 * sizeof(float);
            _vertexAttribute.push_back(va);
            break;
            
        case kModelFormatV3C3:
            stride = 6 * sizeof(float);
            
            va.attrib = MyProgram::kAttribPosition;
            va.size = 3 * sizeof(float);
            va.stride = stride;
            va.offset = 0;
            _vertexAttribute.push_back(va);
            
            va.attrib = MyProgram::kAttribColor;
            va.size = 3 * sizeof(float);
            va.stride = stride;
            va.offset = 3 * sizeof(float);
            _vertexAttribute.push_back(va);
            break;
            
        case kModelFormatV3N3C3:
            stride = 9 * sizeof(float);
            
            va.attrib = MyProgram::kAttribPosition;
            va.size = 3 * sizeof(float);
            va.stride = stride;
            va.offset = 0;
            _vertexAttribute.push_back(va);
            
            va.attrib = MyProgram::kAttribNormal;
            va.size = 3 * sizeof(float);
            va.stride = stride;
            va.offset = 3 * sizeof(float);
            _vertexAttribute.push_back(va);
            
            va.attrib = MyProgram::kAttribColor;
            va.size = 3 * sizeof(float);
            va.stride = stride;
            va.offset = 6 * sizeof(float);
            _vertexAttribute.push_back(va);
            break;
            
        default:
            break;
    }
    
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
    _renderCount = static_cast<int>(vertexBufferSize)/stride;
}

MINE_NAMESPACE_END
