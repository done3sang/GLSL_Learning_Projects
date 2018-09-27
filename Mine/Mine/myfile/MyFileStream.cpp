//
//  MyFileStream.cpp
//  Mine
//
//  Created by xy on 2018/6/28.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#include "MyObject.hpp"
#include "MyArray.hpp"
#include "MyData.hpp"
#include "MyFileStream.hpp"

MINE_NAMESPACE_BEGIN

MyFileStream* MyFileStream::createWithFile(FILE *fileptr, size_t bufferLength) {
    MINE_ASSERT(bufferLength >= 64 && fileptr);
    return new MyFileStream(fileptr, bufferLength);
}

MyFileStream::MyFileStream(FILE* fileptr, size_t bufferLength):
_filePointer(fileptr),
_streamPosition(0) {
    _dataBuffer = MyData<char>::createWithLength(bufferLength);
    fseek(fileptr, 0, SEEK_END);
    _streamLength = ftell(fileptr);
    fseek(fileptr, 0, SEEK_SET);
    forward(0);
}

MyFileStream::~MyFileStream(void) {
    fclose(_filePointer);
}

void MyFileStream::rewind(void) {
    fseek(_filePointer, 0, SEEK_SET);
    _streamPosition = 0;
}

MyData<char>* MyFileStream::forward(size_t steps) {
    _streamPosition += steps;
    _dataBuffer->pop_front(steps);
    fread(_dataBuffer->rawEnd(), steps, 1, _filePointer);
    return _dataBuffer;
}

MINE_NAMESPACE_END
