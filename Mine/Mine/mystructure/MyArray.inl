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

template<class T>
FORCEINLINE MyArray<T>* MyArray<T>::array(void) {
    return new MyArray<T>();
}

template<class T>
FORCEINLINE MyArray<T>* MyArray<T>::arrayWithCapacity(size_t capacity) {
    return new MyArray<T>(capacity);
}

template<class T>
FORCEINLINE MyArray<T>* MyArray<T>::arrayWithRaw(const T* dataArr, size_t length) {
    MINE_ASSERT(dataArr && length > 0);
    return new MyArray<T>(dataArr, length);
}

template<class T>
FORCEINLINE MyArray<T>* MyArray<T>::arrayWithArray(const MyArray& arr) {
    return new MyArray<T>(arr);
}

template<typename T>
FORCEINLINE MyArray<T>::MyArray(size_t capacity):
_data(nullptr),
_length(0),
_capacity(0) {
    objectName("MyArray");
    expand(capacity);
}

template<typename T>
FORCEINLINE MyArray<T>::MyArray(const T* dataArr, size_t length):
_data(nullptr),
_length(0),
_capacity(0) {
    objectName("MyArray");
    write(dataArr, length);
}

template<typename T>
FORCEINLINE MyArray<T>::MyArray(const MyArray& arr) {
    objectName("MyArray");
    operator=(arr);
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
    return _data + _length;
}

template<typename T>
FORCEINLINE typename MyArray<T>::const_iterator MyArray<T>::begin(void) const {
    return _data;
}

template<typename T>
FORCEINLINE typename MyArray<T>::const_iterator MyArray<T>::end(void) const {
    return _data + _length;
}

template<typename T>
FORCEINLINE T& MyArray<T>::operator[](size_t i) {
    return _data[i];
}

template<typename T>
FORCEINLINE const T& MyArray<T>::operator[](size_t i) const {
    return _data[i];
}

template<typename T>
FORCEINLINE void MyArray<T>::push_back(const T& value) {
    checkCapacity();
    T* v = new(_data + _length) T(value);
    if constexpr(std::is_base_of<MyObject, T>::value) {
        v->addRef();
    }
    ++_length;
}

template<typename T>
FORCEINLINE void MyArray<T>::pop_back(size_t num) {
    num = num > _length ? _length: num;
    if(num > 0) {
        if constexpr(std::is_base_of<MyObject, T>::value) {
            for(size_t i = _length - num; i != _length; ++i) {
                _data[i]->release();
            }
        }
        _length -= num;
    }
}

template<typename T>
FORCEINLINE void MyArray<T>::pop_front(size_t num) {
    if(num >= _length) {
        clear();
    } else if(num > 0) {
        for(size_t i = 0; i != _length - num; ++i) {
            if constexpr(std::is_base_of<MyObject, T>::value) {
                _data[i].release();
            }
            _data[i] = _data[i + num];
        }
        _length -= num;
    }
}

template<typename T>
template<typename ...Args>
FORCEINLINE void MyArray<T>::emplace_back(Args&&... args) {
    checkCapacity();
    T* v = ::new(_data + _length) T(args...);
    if constexpr(std::is_base_of<MyObject, T>::value) {
        v->addRef();
    }
    ++_length;
}

template<typename T>
FORCEINLINE void MyArray<T>::clear(void) {
    if constexpr(std::is_base_of<MyObject, T>::value) {
        for(size_t i = 0; i != _length; ++i) {
            _data[i]->release();
        }
    }
    _length = 0;
}

template<typename T>
FORCEINLINE void MyArray<T>::shrink(size_t newLength) {
    MINE_ASSERT(newLength <= _length);
    pop_back(_length - newLength);
}

template<typename T>
FORCEINLINE void MyArray<T>::write(const T* dataArr, size_t length) {
    expand(length);
    _length = 0;
    for(size_t i = 0; i != length; ++i) {
        push_back(dataArr[i]);
    }
}

template<typename T>
FORCEINLINE void MyArray<T>::checkCapacity(size_t num) {
    size_t nextLength = _length + num;
    if(nextLength > _capacity) {
        expand(nextLength << 1);
    }
}

template<typename T>
FORCEINLINE void MyArray<T>::expand(size_t newCapacity) {
    if(_capacity > newCapacity) {
        return;
    }
    
    T* newData = static_cast<T*>(MyMemoryManager::sharedMemoryManager()->allocate(sizeof(T) * newCapacity));
    
    if(nullptr == newData) {
        return;
    }
    
    newData[0] = 'c';
    newData[newCapacity - 1] = 'w';
    // memset(newData, _data, sizeof(T) * _length);
    if(_data) {
        T* newIter = newData;
        for(const_iterator iter = begin(); iter != end(); ++iter) {
            T* v = new (newIter) T(*iter);
            if constexpr(std::is_base_of<MyObject, T>::value) {
                iter->release();
                v->addRef();
            }
        }
        
        MyMemoryManager::sharedMemoryManager()->deallocate(_data);
    }
    
    _data = newData;
    _capacity = newCapacity;
}

MINE_NAMESPACE_END
