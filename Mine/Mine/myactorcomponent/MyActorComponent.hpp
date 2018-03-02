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

class MyUniqueObject;

class MyActorComponent: public MyUniqueObject {
public:
    static constexpr int kComponentTypeNone = 0;
    static constexpr int kComponentTypeMaterial = 1;
    static constexpr int kComponentTypeDirectionalLight = 2;
    static constexpr int kComponentTypePointLight = 3;
    static constexpr int kComponentTypeSpotLight = 4;
    static constexpr int kComponentTypeModel = 5;
    static constexpr int kComponentTypeTransform = 6;
    
    static constexpr int kComponentGroupNone = 0;
    static constexpr int kComponentGroupMaterial = 1;
    static constexpr int kComponentGroupLight = 2;
    static constexpr int kComponentGroupModel = 3;
    static constexpr int kComponentGroupTransform = 4;
    
public:
    FORCEINLINE int componentType(void) const { return _componentType; }
    FORCEINLINE int groupId(void) const { return _groupId; }
    FORCEINLINE bool sameGroup(const MyActorComponent* another) const {
        return another && another->groupId() == groupId();
    }
    
    FORCEINLINE bool componentEnabled(void) const { return _componentEnabled; }
    FORCEINLINE void componentEnabled(bool enabled) { _componentEnabled = enabled; }
    
protected:
    explicit
    FORCEINLINE MyActorComponent(int compType,
                     int groupid = kComponentGroupNone):
    _componentType(compType),
    _groupId(groupid),
    _componentEnabled(true) {}
    FORCEINLINE virtual ~MyActorComponent(void) {}
    
    FORCEINLINE void componentType(int type) { _componentType = type; }
    FORCEINLINE void groupId(int id) { _groupId = id; }
    
private:
    int _componentType;
    int _groupId;
    bool _componentEnabled;
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyActorComponent_hpp */
