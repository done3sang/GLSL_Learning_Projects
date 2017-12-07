//
//  MyShadingManager.cpp
//  MyGLSL
//
//  Created by xy on 07/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <cassert>
#include "MyTemplate.hpp"
#include "MyShader.hpp"
#include "MyProgram.hpp"
#include "MyFileUtil.hpp"
#include "MyErrorDesc.hpp"
#include "MyShadingManager.hpp"

MINE_NAMESPACE_BEGIN

MyShadingManager* MyShadingManager::_sharedShadingManager = nullptr;

MyShadingManager* MyShadingManager::sharedShadingManager() {
    if(!_sharedShadingManager) {
        _sharedShadingManager = new MyShadingManager;
        _sharedShadingManager->refName("MyShadingManager");
        _sharedShadingManager->MyRef::retain();
        _sharedShadingManager->autorelase();
    }
    
    return _sharedShadingManager;
}

void MyShadingManager::closeShadingManager(void)  {
    if(_sharedShadingManager) {
        _sharedShadingManager->release();
        _sharedShadingManager = nullptr;
    }
}

MyShadingManager::~MyShadingManager(void) {
    destroy();
}

bool MyShadingManager::loadShaderConfig(const std::string  &shaderConfigPath) {
    assert(!shaderConfigPath.empty() && "MyShadingManager::loadShaderConfig = shaderConfigPath should not be null");
    
    std::string filedata;
    if(!MyErrorDesc::invokeErrorFailed(MyFileUtil::sharedFileUtil()->readFile(shaderConfigPath, filedata))) {
        return false;
    }
    
    return parse(filedata);
}

bool MyShadingManager::loadShader(int shaderType, const std::string &name, const std::string &path) {
    assert(MyShader::shaderType(shaderType) && "MyShadingManager::loadShaderConfig = shaderType is not valid");
    assert(name.empty() && "MyShadingManager::loadShaderConfig = name should not be null");
    assert(path.empty() && "MyShadingManager::loadShaderConfig = path should not be null");
    
    if(MyShader *shader = shaderByName(name)) {
        assert(shader->shaderType() == shaderType && "MyShadingManager::loadShaderConfig = shader type not compared");
        return true;
    }
    
    MyShader *shader = MyShader::createWithShaderType(name, shaderType);
    if(!shader || !shader->loadFromFile(path)) {
        return false;
    }
    
    addShader(shader);
    return true;
}

bool MyShadingManager::createProgram(const std::string &name, const std::vector<std::string> &shaderNameVec) {
    assert(name.empty() && "MyShadingManager::createProgram = name should not be null");
    assert(shaderNameVec.empty() && "MyShadingManager::createProgram = shaderNameVec should not be null");
}

MINE_NAMESPACE_END
