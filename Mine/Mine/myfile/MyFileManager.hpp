//
//  MyFileManager.hpp
//  Mine
//
//  Created by xy on 2018/6/28.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MyFileManager_hpp
#define MyFileManager_hpp

#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MySingletonObject;
class MyData;
class MyFileStream;

class MyFileManager: public MySingletonObject {
public:
    static MyFileManager* sharedFileManager(void);
    
    MyData* loadFile(const char* filepath);
    MyFileStream* streamFile(const char* filepath, size_t bufferLength = 1024);
    
public:
    
private:
    int _fileNumber;
    
    static MyFileManager* _sharedFileManager;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyFileManager_hpp */
