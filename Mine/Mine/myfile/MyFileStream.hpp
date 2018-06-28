//
//  MyFileStream.hpp
//  Mine
//
//  Created by xy on 2018/6/28.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MyFileStream_hpp
#define MyFileStream_hpp

#include <cstddef>
#include <cstdlib>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyUniqueObject;
class MyData;

class MyFileStream: public MyUniqueObject {
public:
    static MyFileStream* createWithFile(FILE* fileptr, size_t bufferLength);
    
    FORCEINLINE size_t bufferLength(void) const { return _dataBuffer->length(); }
    FORCEINLINE size_t streamLength(void) const { return _streamLength; }
    FORCEINLINE size_t streamPosition(void) const { return _streamPosition; }
    FORCEINLINE MyData* bufferData(void) const { return _dataBuffer; }
    FORCEINLINE bool endOfStream(void) const { return _streamPosition >= _streamLength; }
    
    void rewind(void);
    MyData* forward(size_t steps);
    
private:
    explicit
    MyFileStream(FILE* fileptr, size_t bufferLength);
    virtual ~MyFileStream(void);
    
    FILE* _filePointer;
    MyData* _dataBuffer;
    size_t _streamPosition;
    size_t _streamLength;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyFileStream_hpp */
