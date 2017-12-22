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

MINE_NAMESPACE_END
