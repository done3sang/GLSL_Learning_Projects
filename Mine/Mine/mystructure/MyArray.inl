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

template<typename T, bool O>
FORCEINLINE MyArray<T, O>::MyArray(size_t length):
_data(nullptr),
_length(0),
_capacity(0) {
    expand(length);
}

template<typename T, bool O>
FORCEINLINE MyArray<T, O>::MyArray(T* dataArr, size_t length):
_data(nullptr),
_length(0),
_capacity(0) {
    write(dataArr, length);
}

template<typename T, bool O>
FORCEINLINE MyArray<T, O>::MyArray(const MyArray& other) {
    operator=(other);
}

template<typename T, bool O>
FORCEINLINE MyArray<T, O>::MyArray(const MyArray&& other):
_data(other._data),
_length(other._length),
_capacity(other._length) {
    other._data = nullptr;
    other._length = other._capacity = 0;
}

template<typename T, bool O>
FORCEINLINE MyArray<T, O>::~MyArray(void) {
    if(_data) {
        MyMemoryManager::sharedMemoryManager()->deallocate(_data);
    }
}

template<typename T, bool O>
FORCEINLINE typename MyArray<T, O>::iterator MyArray<T, O>::begin(void) {
    return _data;
}

template<typename T, bool O>
FORCEINLINE typename MyArray<T, O>::iterator MyArray<T, O>::end(void) {
    return _data + _length;
}

template<typename T, bool O>
FORCEINLINE typename MyArray<T, O>::const_iterator MyArray<T, O>::begin(void) const {
    return _data;
}

template<typename T, bool O>
FORCEINLINE typename MyArray<T, O>::const_iterator MyArray<T, O>::end(void) const {
    return _data + _length;
}

template<typename T, bool O>
FORCEINLINE T& MyArray<T, O>::operator[](size_t i) {
    return _data[i];
}

template<typename T, bool O>
FORCEINLINE const T& MyArray<T, O>::operator[](size_t i) const {
    return _data[i];
}

template<typename T, bool O>
FORCEINLINE void MyArray<T, O>::push_back(const T& value) {
    checkCapacity();
    T* v = new(_data + _length) T(value);
    if constexpr(O) {
        v->addRef();
    }
    ++_length;
}

template<typename T, bool O>
FORCEINLINE void MyArray<T, O>::pop_back(size_t num) {
    num = num > _length ? _length: num;
    if(num > 0) {
        if constexpr(O) {
            for(size_t i = _length - num; i != _length; ++i) {
                _data[i].release();
            }
        }
        _length -= num;
    }
}

template<typename T, bool O>
FORCEINLINE void MyArray<T, O>::pop_front(size_t num) {
    if(num >= _length) {
        clear();
    } else if(num > 0) {
        for(size_t i = 0; i != _length - num; ++i) {
            if constexpr(O) {
                _data[i].release();
            }
            _data[i] = _data[i + num];
        }
        _length -= num;
    }
}

template<typename T, bool O>
template<typename ...Args>
FORCEINLINE void MyArray<T, O>::emplace_back(Args&&... args) {
    checkCapacity();
    T* v = ::new(_data + _length) T(args...);
    if constexpr(O) {
        v->addRef();
    }
    ++_length;
}

template<typename T, bool O>
FORCEINLINE void MyArray<T, O>::clear(void) {
    if constexpr(O) {
        for(size_t i = 0; i != _length; ++i) {
            _data[i].release();
        }
    }
    _length = 0;
}

template<typename T, bool O>
FORCEINLINE void MyArray<T, O>::shrink(size_t newLength) {
    MINE_ASSERT(newLength <= _length);
    pop_back(_length - newLength);
}

template<typename T, bool O>
FORCEINLINE void MyArray<T, O>::write(const T* dataArr, size_t length) {
    expand(length);
    _length = 0;
    for(size_t i = 0; i != length; ++i) {
        push_back(dataArr[i]);
    }
}

template<typename T, bool O>
FORCEINLINE void MyArray<T, O>::checkCapacity(size_t num) {
    size_t nextLength = _length + num;
    if(nextLength > _capacity) {
        expand(nextLength << 1);
    }
}

template<typename T, bool O>
FORCEINLINE void MyArray<T, O>::expand(size_t newCapacity) {
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
            if constexpr(O) {
                iter->release();
                v->addRef();
            }
        }
    }
    
    _data = newData;
    _capacity = newCapacity;
}

MINE_NAMESPACE_END
