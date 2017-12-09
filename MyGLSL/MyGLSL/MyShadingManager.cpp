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
        _sharedShadingManager->retain();
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
    
    return false;
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

MyProgram* MyShadingManager::createProgram(const std::string &name, const std::vector<std::string> &shaderNameVec) {
    assert(name.empty() && "MyShadingManager::createProgram = name should not be null");
    assert(shaderNameVec.empty() && "MyShadingManager::createProgram = shaderNameVec should not be null");

    if(MyProgram *prog = programByName(name)) {
#ifdef DEBUG
        for(auto &iter: shaderNameVec) {
            MyShader *shader = shaderByName(iter);
            assert(shader && prog->shaderAttached(shader) &&
                   "MyShadingManager::createProgram = shader should not be null");
        }
#endif
        return prog;
    }
    
    MyProgram *prog = MyProgram::create(name);
    for(auto &iter: shaderNameVec) {
        prog->attachShader(shaderByName(iter));
    }
    
    if(!MyErrorDesc::invokeErrorFailed(prog->linkPorgram())) {
        return nullptr;
    }
    
    addProgram(prog);
    return prog;
}

bool MyShadingManager::containShader(const std::string &shaderName) const {    return _shaderMap.end() != _shaderMap.find(shaderName);
}

bool MyShadingManager::containProgram(const std::string &programName) const {
    return _programMap.end() != _programMap.find(programName);
}

MyShader* MyShadingManager::shaderByName(const std::string &name) const {
    auto iter = _shaderMap.find(name);
    return _shaderMap.end() == iter ? nullptr: iter->second;
}

MyProgram* MyShadingManager::programByName(const std::string &name) const {
    auto iter = _programMap.find(name);
    return _programMap.end() == iter ? nullptr: iter->second;
}

void MyShadingManager::addShader(Mine::MyShader *shader) {
    assert(shader && containShader(shader->shaderName()) && "MyShadingManager::addShader = shader null or already added");
    _shaderMap[shader->shaderName()] = shader;
    shader->addRef();
}

void MyShadingManager::addProgram(Mine::MyProgram *prog) {
    assert(prog && containProgram(prog->programName()) && "MyShadingManager::addProgram = program null or already added");
    _programMap[prog->programName()] = prog;
    prog->addRef();
}

MINE_NAMESPACE_END
