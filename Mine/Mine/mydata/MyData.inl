//
//  MyData.cpp
//  Mine
//
//  Created by xy on 2018/6/19.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#include "MyObject.hpp"

MINE_NAMESPACE_BEGIN

template<typename T>
MyData<T>* MyData<T>::create(void) {
    return new MyData;
}

template<typename T>
MyData<T>* MyData<T>::createWithLength(size_t length) {
    return new MyData(length);
}

template<typename T>
MyData<T>* MyData<T>::createWithData(const T* data, size_t length) {
    return new MyData(data, length);
}

template<typename T>
MyData<T>::MyData(size_t length) {
    operator=(new MyArray<T, false>(length));
}

template<typename T>
MyData<T>::MyData(const T* data, size_t length) {
    operator=(new MyArray<T, false>(data, length));
}

template<typename T>
MyData<T>::~MyData(void) {
    purge();
}

template<typename T>
MyData<T>& MyData<T>::operator=(MyArray<T, false>* arr) {
    MINE_ASSERT(arr);
    
    arr->addRef();
    if(_data) {
        _data->release();
    }
    _data = arr;
    _manipulator = _data->begin();
    
    return *this;
}

template<typename T>
void MyData<T>::purge(void) {
    if(_data) {
        _data->release();
        _data = nullptr;
        _manipulator = nullptr;
    }
}

template<typename T>
void MyData<T>::pop_back(size_t num) {
    if(_data) {
        _data->pop_back(num);
    }
}

template<typename T>
void MyData<T>::pop_front(size_t num) {
    if(_data) {
        _data->pop_front(num);
    }
}

MINE_NAMESPACE_END
