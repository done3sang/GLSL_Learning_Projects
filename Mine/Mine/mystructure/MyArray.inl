//
//  MyArray.inl
//  Mine
//
//  Created by xy on 2018/6/28.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#include "MyObject.hpp"
#include "MyTemplate.hpp"
#include "MyMemoryManager.hpp"

MINE_NAMESPACE_BEGIN

template<typename T>
FORCEINLINE MyArray<T>::MyArray(size_t length):
_data(nullptr),
_length(0),
_capacity(0) {
    relength(length);
}

template<typename T>
FORCEINLINE MyArray<T>::MyArray(T* dataArr, size_t length):
_data(nullptr),
_length(0),
_capacity(0) {
    write(dataArr, length);
}

template<typename T>
FORCEINLINE MyArray<T>::MyArray(const MyArray& other) {
    operator=(other);
}

template<typename T>
FORCEINLINE MyArray<T>::MyArray(const MyArray&& other):
_data(other._data),
_length(other._length),
_capacity(other._length) {
    other._data = nullptr;
    other._length = other._capacity = 0;
}

template<typename T>
FORCEINLINE MyArray<T>::~MyArray(void) {
    if(_data) {
        MyMemoryManager::sharedMemoryManager()->deallocate(_data);
    }
}

template<typename T>
FORCEINLINE typename MyArray<T>::iterator MyArray<T>::begin(void) {
    return _data;
}

template<typename T>
FORCEINLINE typename MyArray<T>::iterator MyArray<T>::end(void) {
    return _data + _length + 1;
}

template<typename T>
FORCEINLINE typename MyArray<T>::const_iterator MyArray<T>::begin(void) const {
    return _data;
}

template<typename T>
FORCEINLINE typename MyArray<T>::const_iterator MyArray<T>::end(void) const {
    return _data + _length + 1;
}

template<typename T>
FORCEINLINE T& MyArray<T>::operator[](size_t i) {
    return _data + i;
}

template<typename T>
FORCEINLINE const T& MyArray<T>::operator[](size_t i) const {
    return _data + i;
}

template<typename T>
FORCEINLINE void MyArray<T>::push_back(const T& value) {
    checkCapacity();
    T* v = new(_data + _length) T(value);
    ++_length;
}

template<typename T>
FORCEINLINE void MyArray<T>::pop_back(size_t num) {
    num = num > _length ? _length: num;
    if(num > 0) {
        _length -= num;
    }
}

template<typename T>
FORCEINLINE void MyArray<T>::pop_front(size_t num) {
    if(num >= _length) {
        clear();
    } else if(num > 0) {
        for(size_t i = 0; i != _length - num; ++i) {
            _data[i] = _data[i + num];
        }
        _length -= num;
    }
}

template<typename T>
template<typename ...Args>
FORCEINLINE void MyArray<T>::emplace_back(Args&&... args) {
    checkCapacity();
    ::new(_data + _length) T(args...);
    ++_length;
}

template<typename T>
FORCEINLINE void MyArray<T>::clear(void) {
    _length = 0;
}

template<typename T>
FORCEINLINE void MyArray<T>::write(const T* dataArr, size_t length) {
    relength(length);
    _length = 0;
    for(size_t i = 0; i != length; ++i) {
        push_back(dataArr[i]);
    }
}

template<typename T>
FORCEINLINE void MyArray<T>::checkCapacity(size_t num) {
    size_t nextLength = _length + num;
    if(nextLength > _capacity) {
        relength(nextLength << 1);
    }
}

template<typename T>
FORCEINLINE void MyArray<T>::relength(size_t newCapacity) {
    if(_capacity > newCapacity) {
        return;
    }
    
    T* newData = static_cast<T*>(MyMemoryManager::sharedMemoryManager()->allocate(sizeof(T) * newCapacity));
    
    if(nullptr == newData) {
        return;
    }
    
    // memset(newData, _data, sizeof(T) * _length);
    if(_data) {
        T* newIter = newData;
        for(const_iterator iter = begin(); iter != end(); ++iter) {
            new (newIter) T(*iter);
        }
    }
    
    _data = newData;
    _capacity = newCapacity;
}

MINE_NAMESPACE_END
