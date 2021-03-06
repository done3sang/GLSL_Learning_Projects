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
#include <unordered_map>

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyUniqueObject;
class MyShader;
class MyBufferObject;
class MyFVector3;
class MyFVector4;
class MyFMatrix4;

class MyTexture;
class MyMaterial;
class MyTransformComponent;

class MyProgram: public MyUniqueObject {
public:
    static MyProgram* create(const std::string& programName);
    
    bool operator==(const MyProgram &another) const {
        return this == &another || (0 != _programId && _programId == another.programId());
    }
    
    GLuint programId(void) const { return _programId; }
    const std::string& programName(void) const { return _programName; }
    const std::string& programLog(void) const { return _programLog; }
    bool linked(void) const { return _linked; }
    bool valid(void) const { return 0 != _programId; }
    
    int attachShader(MyShader *shader);
    int detachShader(MyShader *shader);
    void clearShader(void);
    bool shaderAttached(const MyShader *shader) const;
    
    int linkPorgram(void);
    void use(void);
    void deleteProgram(void);
    
    bool validate(void) const;
    
    int bindAttribLocation(GLuint location, const std::string &name) const;
    int uniformMatrix4(const std::string &name, const MyFMatrix4 &mat);
    bool uniformVector3(const std::string &name, const MyFVector3 &vec);
    bool uniformVector4(const std::string &name, const MyFVector4 &vec);
    bool uniformBool(const std::string &name, bool value);
    int uniformFloat(const std::string &name, float value);
    int uniformInteger(const std::string &name, int value);
    int uniformBlockIndex(const std::string &blockName, const std::string &indexName, int valueSize, void *valueptr);
    
    int uniformTexture(const std::string& name);
    
    void clearUniformBlock(void);
    
    std::string activeUniform(void) const;
    
    static MyProgram* runningProgram(void);
    
public:
    int bindTexture(const char* name, const MyTexture *texture);
    void bindActor(const MyTransformComponent *transform, const MyMaterial *material);
    
public:
    static const int kAttribPosition = 0;
    static const int kAttribColor = 1;
    static const int kAttribTexCoord0 = 2;
    static const int kAttribNormal = 3;
    static const int kAttribTangent = 4;
    
private:
    explicit
    MyProgram(const std::string& programName);
    ~MyProgram(void);
    
    GLuint _programId;
    std::string _programName;
    bool _linked;
    std::string _programLog;
    std::vector<MyShader*>  _shaderVec;
    std::unordered_map<std::string, int> _uniformLocation;
    std::unordered_map<int, MyBufferObject*> _uniformBlock;
    int _textureNum;
    
    static MyProgram *_runningProgram;
    
    int uniformLocation(const std::string &name);
    void addUniformBlock(int blockIndex, MyBufferObject *blockBuffer);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyProgram_hpp */
