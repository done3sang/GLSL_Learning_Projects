//
//  MyShadingManager.hpp
//  MyGLSL
//
//  Created by xy on 07/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyShadingManager_hpp
#define MyShadingManager_hpp

#include <map>
#include <vector>
#include <string>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MySingletonRef;
class MyShader;
class MyProgram;

class MyShadingManager: public MySingletonRef {
public:
    static MyShadingManager* sharedShadingManager();
    static void closeShadingManager(void);
    
    bool loadShaderConfig(const std::string  &path);
    bool shaderLoaded(void) const { return _shaderLoaded; }
    
    bool loadShader(int shaderType, const std::string &name, const std::string &path);
    MyProgram* createProgram(const std::string &name,
                             const std::vector<std::string> &shaderNameVec);
    
    bool containShader(const std::string &shaderName) const;
    bool containProgram(const std::string &programName) const;
    
    MyShader* shaderByName(const std::string &name) const;
    MyProgram* programByName(const std::string &name) const;
    
private:
    ~MyShadingManager(void);
    
    bool _shaderLoaded;
    
    std::map<std::string, MyShader*> _shaderMap;
    std::map<std::string, MyProgram*> _programMap;
    
    static MyShadingManager *_sharedShadingManager;
    
    void addShader(MyShader *shader);
    void addProgram(MyProgram *program);
    
    void destroy(void);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyShadingManager_hpp */
