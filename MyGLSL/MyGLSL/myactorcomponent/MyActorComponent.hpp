//
//  MyActorComponent.hpp
//  MyGLSL
//
//  Created by xy on 11/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#ifndef MyActorComponent_hpp
#define MyActorComponent_hpp

#include <string>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyUniqueRef;

class MyActorComponent: public MyUniqueRef {
public:
    static const int kComponentTypeNone;
    static const int kComponentTypeMaterial;
    static const int kComponentTypeDirectionalLight;
    static const int kComponentTypePointLight;
    static const int kComponentTypeSpotLight;
    
    static const int kComponentGroupNone;
    static const int kComponentGroupMaterial;
    static const int kComponentGroupLight;
    
public:
    int componentType(void) const { return _componentType; }
    int groupId(void) const { return _groupId; }
    const std::string& componentName(void) const { return _componentName; }
    bool sameGroup(const MyActorComponent* another) const {
        return another && another->groupId() == groupId();
    }
    
protected:
    explicit
    MyActorComponent(int compType,
                     const std::string &compName = "",
                     int groupid = kComponentGroupNone):
    _componentType(compType),  _componentName(compName),
    _groupId(groupid), _componentEnabled(true) {}
    ~MyActorComponent(void) {}
    
    void componentType(int type) { _componentType = type; }
    void groupId(int id) { _groupId = id; }
    void componentName(const std::string &name) { _componentName = name; }
    
private:
    int _componentType;
    int _groupId;
    std::string _componentName;
    bool _componentEnabled;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyActorComponent_hpp */
