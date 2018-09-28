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
FORCEINLINE MyData<T>* MyData<T>::data(void) {
    return new MyData;
}

template<typename T>
FORCEINLINE MyData<T>* MyData<T>::dataWithLength(size_t length) {
    return new MyData(length);
}

template<typename T>
FORCEINLINE MyData<T>* MyData<T>::dataWithRaw(const T* data, size_t length) {
    return new MyData(data, length);
}

template<typename T>
FORCEINLINE MyData<T>::MyData(size_t length) {
    operator=(new MyArray<T, false>(length));
}

template<typename T>
FORCEINLINE MyData<T>::MyData(const T* data, size_t length) {
    operator=(new MyArray<T, false>(data, length));
}

template<typename T>
FORCEINLINE MyData<T>::~MyData(void) {
    purge();
}

template<typename T>
FORCEINLINE MyData<T>& MyData<T>::operator=(MyArray<T, false>* arr) {
    MINE_ASSERT(arr);
    
    ASSIGN_OBJECT(_data, arr);
    _manipulator = _data->begin();
    
    return *this;
}

template<typename T>
FORCEINLINE void MyData<T>::purge(void) {
    RELEASE_OBJECT(_data);
    _manipulator = nullptr;
}

template<typename T>
FORCEINLINE void MyData<T>::push_back(const T &value) {
    MINE_ASSERT(_data);
    _data->push_back(value);
}

template<typename T>
FORCEINLINE void MyData<T>::pop_back(size_t num) {
    MINE_ASSERT(_data);
    _data->pop_back(num);
}

template<typename T>
FORCEINLINE void MyData<T>::pop_front(size_t num) {
    MINE_ASSERT(_data);
    _data->pop_front(num);
}

MINE_NAMESPACE_END
