//
//  MyFileManager.cpp
//  Mine
//
//  Created by xy on 2018/6/28.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#include <cstdlib>
#include "MyObject.hpp"
#include "MyArray.hpp"
#include "MyData.hpp"
#include "MyFileStream.hpp"
#include "MyFileManager.hpp"

MINE_NAMESPACE_BEGIN

MyFileManager* MyFileManager::_sharedFileManager = nullptr;

MyFileManager* MyFileManager::sharedFileManager(void) {
    if(!_sharedFileManager) {
        _sharedFileManager = new MyFileManager;
        _sharedFileManager->objectName("MyFileManager");
    }
    
    return _sharedFileManager;
}

void MyFileManager::closeFileManager(void) {
    if(_sharedFileManager) {
        _sharedFileManager->release();
        _sharedFileManager = nullptr;
    }
}

MyData<char>* MyFileManager::loadFile(const char *filepath) const {
    FILE* fp = fopen(filepath, "rb");
    
    if(nullptr == fp) {
        return nullptr;
    }
    
    fseek(fp, 0, SEEK_END);
    
    size_t fileLength = ftell(fp);
    MyData<char>* data = MyData<char>::createWithLength(fileLength);
    
    fseek(fp, 0, SEEK_SET);
    fread(data->raw(), fileLength, 1, fp);
    fclose(fp);
    
    return data;
}

MyFileStream* MyFileManager::streamFile(const char *filepath, size_t bufferLength) const {
    FILE* fp = fopen(filepath, "rb");
    
    if(nullptr == fp) {
        return nullptr;
    }
    
    return MyFileStream::createWithFile(fp, bufferLength);
}


MINE_NAMESPACE_END
