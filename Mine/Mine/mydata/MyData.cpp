//
//  MyData.cpp
//  Mine
//
//  Created by xy on 2018/6/19.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#include "MyObject.hpp"
#include "MyArray.hpp"
#include "MyData.hpp"

MINE_NAMESPACE_BEGIN

MyData* MyData::create(void) {
    return new MyData;
}

MyData* MyData::createWithLength(size_t length) {
    return new MyData(length);
}

MyData* MyData::createWithData(char* data, size_t length) {
    return new MyData(data, length);
}

MyData::MyData(size_t length) {
    operator=(new MyArray<char>(length));
}

MyData::MyData(char* data, size_t length) {
    operator=(new MyArray<char>(data, length));
}

MyData::~MyData(void) {
    purge();
}

MyData& MyData::operator=(MyArray<char>* arr) {
    MINE_ASSERT(arr);
    
    arr->addRef();
    if(_data) {
        _data->release();
    }
    _data = arr;
    _manipulator = _data->begin();
    
    return *this;
}

void MyData::purge(void) {
    if(_data) {
        _data->release();
        _data = nullptr;
        _manipulator = nullptr;
    }
}

void MyData::pop_back(size_t num) {
    if(_data) {
        _data->pop_back(num);
    }
}

void MyData::pop_front(size_t num) {
    if(_data) {
        _data->pop_front(num);
    }
}

MINE_NAMESPACE_END
