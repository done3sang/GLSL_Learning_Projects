//
//  MyModelGenerator.hpp
//  Mine
//
//  Created by xy on 02/01/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#ifndef MyModelGenerator_hpp
#define MyModelGenerator_hpp

#include <vector>
#include "MyPrecompiled.hpp"

/* The classes below are exported */
#pragma GCC visibility push(default)

MINE_NAMESPACE_BEGIN

class MyStatic;
class MyModelComponent;

class MyModelGenerator final: private MyStatic {
public:
    //! position[3]_normal[3]_texcoord0[2]
    static MyModelComponent* generateTorus(float innerRadius,
                                    float outerRadius,
                                    size_t nsides,
                                    size_t nrings);
    
private:
    static void torusGenerator(float innerRadius,
                               float outerRadius,
                               size_t nsides,
                               size_t nrings,
                               std::vector<float> &dataVec,
                               std::vector<unsigned int> &elemVec);
};

MINE_NAMESPACE_END

#pragma GCC visibility pop

#endif /* MyModelGenerator_hpp */
