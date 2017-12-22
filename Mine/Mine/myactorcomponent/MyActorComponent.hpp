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
    static constexpr int kComponentTypeNone = 0;
    static constexpr int kComponentTypeMaterial = 1;
    static constexpr int kComponentTypeDirectionalLight = 2;
    static constexpr int kComponentTypePointLight = 3;
    static constexpr int kComponentTypeSpotLight = 4;
    static constexpr int kComponentTypeModel = 5;
    
    static constexpr int kComponentGroupNone = 0;
    static constexpr int kComponentGroupMaterial = 1;
    static constexpr int kComponentGroupLight = 2;
    static constexpr int kComponentGroupModel = 3;
    
public:
    int componentType(void) const { return _componentType; }
    int groupId(void) const { return _groupId; }
    const std::string& componentName(void) const { return _componentName; }
    bool sameGroup(const MyActorComponent* another) const {
        return another && another->groupId() == groupId();
    }
    
    bool componentEnabled(void) const { return _componentEnabled; }
    void componentEnabled(bool enabled) { _componentEnabled = enabled; }
    
protected:
    explicit
    MyActorComponent(int compType,
                     const std::string &compName = "",
                     int groupid = kComponentGroupNone):
    _componentType(compType),  _componentName(compName),
    _groupId(groupid), _componentEnabled(true) {}
    virtual ~MyActorComponent(void) {}
    
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
