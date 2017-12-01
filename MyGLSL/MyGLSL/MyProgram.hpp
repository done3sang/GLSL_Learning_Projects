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
#include <map>
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include "Precompiled.h"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyShader;
class MyRef;

class MyProgram: public MyRef {
public:
    MyProgram(void);
    ~MyProgram(void);
    
    static MyProgram* create(void);
    
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
    
    int bindAttribLocation(GLuint location, const std::string &name) const;
    int uniformMatrix4(const std::string &name, const glm::mat4 &mat);
    int uniformFloat(const std::string &name, float value);
    int uniformInteger(const std::string &name, int value);
    
    static MyProgram* runningProgram(void);
    
public:
    static const int kAttribPosition = 0;
    static const int kAttribColor = 1;
    static const int kAttribTexCoord0 = 2;
    static const int kAttribNormal = 3;
    static const int kAttribTangent = 4;
    
private:
    GLuint _programId;
    bool _linked;
    std::string _programLog;
    std::vector<const MyShader*>  _shaderVec;
    std::map<std::string, int> _uniformLocation;
    
    static MyProgram *_runningProgram;
    
    int uniformLocation(const std::string &name);
    
    MyProgram(const MyProgram&);
    MyProgram& operator=(const MyProgram&);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyProgram_hpp */
