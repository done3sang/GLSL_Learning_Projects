//
//  MyProgram.hpp
//  MyGLSL
//
//  Created by xy on 28/11/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyProgram_hpp
#define MyProgram_hpp

#include <string>
#include <vector>
#include <GLFW/glfw3.h>
#include "Precompiled.h"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyShader;

class MyProgram {
public:
    MyProgram(void);
    ~MyProgram(void);
    
    bool operator==(const MyProgram &another) const {
        return this == &another || (0 != _programId && _programId == another.programId());
    }
    
    GLuint programId(void) const { return _programId; }
    const std::string& programLog(void) const { return _programLog; }
    bool linked(void) const { return _linked; }
    bool valid(void) const { return 0 != _programId; }
    
    int attachShader(const MyShader &shader);
    int detachShader(const MyShader &shader);
    
    bool shaderAttached(const MyShader &shader) const;
    
    int linkPorgram(void);
    int useProgram(void);
    void deleteProgram(void);
    
    bool validate(void) const;
    
    void bindAttribLocation(int location, const std::string &name) const;
    
    static MyProgram* runningProgram(void);
    
public:
    static const int kAttribPosition = 0;
    static const int kAttribTexColor = 1;
    static const int kAttribTexCoord0 = 2;
    static const int kAttribNormal = 3;
    static const int kAttribTagent = 4;
    
private:
    GLuint _programId;
    bool _linked;
    std::string _programLog;
    std::vector<const MyShader*>  _shaderVec;
    
    static MyProgram *_runningProgram;
    
    MyProgram(const MyProgram&);
    MyProgram& operator=(const MyProgram&);
};

MINE_NAMESPACE_END

#endif /* MyProgram_hpp */
