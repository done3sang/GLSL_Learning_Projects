//
//  MyShadingManager.cpp
//  MyGLSL
//
//  Created by xy on 07/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <cassert>
#include "MyObject.hpp"
#include "MyShader.hpp"
#include "MyProgram.hpp"
#include "MyArray.hpp"
#include "MyData.hpp"
#include "MyFileManager.hpp"
#include "MyErrorDesc.hpp"
#include "MyXMLNode.hpp"
#include "MyXMLDocument.hpp"
#include "MyShadingManager.hpp"

MINE_NAMESPACE_BEGIN

MyShadingManager* MyShadingManager::_sharedShadingManager = nullptr;

MyShadingManager* MyShadingManager::sharedShadingManager(void) {
    if(!_sharedShadingManager) {
        _sharedShadingManager = new MyShadingManager();
        _sharedShadingManager->objectName("MyShadingManager");
    }
    
    return _sharedShadingManager;
}

void MyShadingManager::close(void)  {
    RELEASE_OBJECT(_sharedShadingManager);
}

MyShadingManager::~MyShadingManager(void) {
    destroy();
}

void MyShadingManager::destroy(void) {
    for(auto &iter: _programMap) {
        iter.second->release();
    }
    for(auto &iter: _shaderMap) {
        iter.second->release();
    }
    _programMap.clear();
    _shaderMap.clear();
    _shaderLoaded = false;
}

bool MyShadingManager::loadShaderConfig(const std::string  &path) {
    assert(!path.empty() && "MyShadingManager::loadShaderConfig = path null");
    const MyXMLDocument *doc = MyXMLDocument::createWithDocument(path);
    if(!doc) {
        return false;
    }
    
    MyXMLNode *rootnode = doc->rootNode();
    MyShader *shader = nullptr;
    MyProgram *program = nullptr;
    int shaderType;
    std::vector<std::string> shadervec;
    
    if(!rootnode) {
        return true;
    }
    
    for(auto node = rootnode->childNode(); node; node = node->siblingNode()) {
        if(node->nodeName() == "shader") {
            for(auto shadernode = node->childNode(); shadernode;
                shadernode = shadernode->siblingNode()) {
                if(shadernode->nodeName() == "vertex" ||
                   shadernode->nodeName() == "fragment") {
                    shaderType = shadernode->nodeName() == "vertex" ? MyShader::kShaderTypeVertex: MyShader::kShaderTypeFragment;
                    for(auto vertnode = shadernode->childNode(); vertnode;
                        vertnode = vertnode->siblingNode()) {
                        if((shader = MyShader::createWithShaderTypeAndPath(
                                                                           vertnode->nodeName(),
                                                                           shaderType,
                                                                           vertnode->nodeValue()))) {
                            addShader(shader);
                        }
                    }
                }
            }
        } else if(node->nodeName() == "program") {
            for(auto prognode = node->childNode(); prognode;
                prognode = prognode->siblingNode()) {
                shadervec.clear();
                for(auto vecnode = prognode->childNode(); vecnode;
                    vecnode = vecnode->siblingNode()) {
                    shadervec.push_back(vecnode->nodeValue());
                }
                if((program = createProgram(prognode->nodeName(), shadervec))) {
                    //addProgram(program);
                }
            }
        }
    }
    
    _shaderLoaded = true;
    return true;
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

MyProgram* MyShadingManager::createProgram(const std::string &name,
                                           const std::vector<std::string> &shaderNameVec) {
    assert(!name.empty() && "MyShadingManager::createProgram = name should not be null");
    assert(!shaderNameVec.empty() && "MyShadingManager::createProgram = shaderNameVec should not be null");

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

void MyShadingManager::addShader(MyShader *shader) {
    assert(shader && !containShader(shader->shaderName()) && "MyShadingManager::addShader = shader null or already added");
    _shaderMap[shader->shaderName()] = shader;
    shader->addRef();
}

void MyShadingManager::addProgram(MyProgram *prog) {
    assert(prog && !containProgram(prog->programName()) && "MyShadingManager::addProgram = program null or already added");
    _programMap[prog->programName()] = prog;
    prog->addRef();
}

MINE_NAMESPACE_END
