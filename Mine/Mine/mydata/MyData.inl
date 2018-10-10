//
//  MyData.cpp
//  Mine
//
//  Created by xy on 2018/6/19.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#include "MyObject.hpp"

MINE_NAMESPACE_BEGIN

template<class T>
FORCEINLINE MyData<T>* MyData<T>::data(void) {
    MyData* data = new MyData;
    data->objectName("MyData");
    MyArray<T> *arr = MyArray<T>::arrayWithCapacity(4);
    data->operator=(*arr);
    return data;
}

template<class T>
FORCEINLINE MyData<T>* MyData<T>::dataWithLength(size_t length) {
    MyData* data = new MyData(length);
    data->objectName("MyData");
    return data;
}

template<class T>
FORCEINLINE MyData<T>* MyData<T>::dataWithRaw(const T* data, size_t length) {
    MyData* rdata = new MyData(data, length);
    rdata->objectName("MyData");
    return rdata;
}

template<class T>
FORCEINLINE MyData<T>::MyData(size_t capacity) {
    MyArray<T>* arr = MyArray<T>::arrayWithCapacity(capacity);
    operator=(*arr);
}

template<class T>
FORCEINLINE MyData<T>::MyData(const T* data, size_t length) {
    MyArray<T>* arr = MyArray<T>::arrayWithRaw(data, length);
    operator=(*arr);
}

template<class T>
FORCEINLINE MyData<T>::~MyData(void) {
    purge();
}

template<class T>
FORCEINLINE MyData<T>& MyData<T>::operator=(MyArray<T>& arr) {    
    ASSIGN_OBJECT(_data, &arr);
    _manipulator = _data->begin();
    
    return *this;
}

template<class T>
FORCEINLINE void MyData<T>::purge(void) {
    RELEASE_OBJECT(_data);
    _manipulator = nullptr;
}

template<class T>
FORCEINLINE void MyData<T>::push_back(const T &value) {
    _data->push_back(value);
}

template<class T>
FORCEINLINE void MyData<T>::pop_back(size_t num) {
    MINE_ASSERT(_data);
    _data->pop_back(num);
}

template<class T>
FORCEINLINE void MyData<T>::pop_front(size_t num) {
    MINE_ASSERT(_data);
    _data->pop_front(num);
}

MINE_NAMESPACE_END
