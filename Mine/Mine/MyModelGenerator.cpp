//
//  MyModelGenerator.cpp
//  Mine
//
//  Created by xy on 02/01/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#include <cassert>
#include "MyTemplate.hpp"
#include "MyMathUtil.hpp"
#include "MyActorComponent.hpp"
#include "MyModelComponent.hpp"
#include "MyModelGenerator.hpp"

MINE_NAMESPACE_BEGIN

MyModelComponent* MyModelGenerator::generateTorus(float innerRadius,
                                                  float outerRadius,
                                                  size_t nsides,
                                                  size_t nrings) {
    assert(innerRadius > 0.0f && outerRadius > innerRadius &&
           "ERROR = MyModelGenerator::generateTorus, radius not paired");
    assert(nsides > 0 && nrings > 0 &&
           "ERROR = MyModelGenerator::generateTorus, side and ring not valid");
    
    std::vector<float> dataVec;
    std::vector<unsigned int> elemVec;
    
    torusGenerator(innerRadius, outerRadius, nsides, nrings, dataVec, elemVec);
    
    MyModelComponent *model = MyModelComponent::create();
    if(!model->loadVertexData(dataVec,
                              "position[3]_normal[3]_texcoord0[2]",
                              MyModelComponent::kModelPrimitiveTriangleStrip)) {
        return nullptr;
    }
    model->modelProgram("basic");
    if(!model->loadElementData(elemVec)) {
        return nullptr;
    }
    
    return model;
}

void MyModelGenerator::torusGenerator(float innerRadius,
                                      float outerRadius,
                                      size_t nsides,
                                      size_t nrings,
                                      std::vector<float> &dataVec,
                                      std::vector<unsigned int> &elemVec) {
    const float ringRadius((innerRadius + outerRadius) * 0.5f);
    const float sideRadius((outerRadius - innerRadius) * 0.5f);
    const float frings(static_cast<float>(nrings));
    const float fsides(static_cast<float>(nsides));
    const float ringStep(MyMathUtil::kMathPIBy2/frings);
    const float sideStep(MyMathUtil::kMathPIBy2/fsides);
    float ringRadian(0.0f), sideRadian(0.0f);
    const float ringTexStep(1.0f/frings);
    const float sideTexStep(1.0f/fsides);
    const unsigned int ringStride(static_cast<unsigned int>(nsides) + 1);
    unsigned int elemIndex(0);
    float tx, ty;
    float cx, cz;
    float px, py, pz;
    float dx, dz;
    float nx, ny, nz;
    float rnx, rnz, snx, sny;
    
    // start from (0.0, 0.0, ringRadius)
    tx = 0.0f;
    for(size_t ringIndex = 0; ringIndex != nrings + 1; ++ringIndex) {
        rnx = MyMathUtil::sin(ringRadian);
        rnz = MyMathUtil::cos(ringRadian);
        cx = rnx * ringRadius;
        cz = rnz * ringRadius;
        dx = rnx * sideRadius;
        dz = rnz * sideRadius;
        
        ty = 0.0f;
        for(size_t sideIndex = 0; sideIndex != nsides + 1; ++sideIndex, ++elemIndex) {
            snx = MyMathUtil::cos(sideRadian);
            sny = MyMathUtil::sin(sideRadian);
            
            nx = rnx * snx;
            ny = sny;
            nz = rnz * snx;
            
            px = cx + dx * snx;
            py = sny * sideRadius;
            pz = cz + dz * snx;
            
            dataVec.push_back(px);
            dataVec.push_back(py);
            dataVec.push_back(pz);
            dataVec.push_back(nx);
            dataVec.push_back(ny);
            dataVec.push_back(nz);
            dataVec.push_back(tx);
            dataVec.push_back(ty);
            
            sideRadian += sideStep;
            ty += sideTexStep;
            
            // element drawn by gl_triangle_strip
            if(ringIndex < nrings) {
                elemVec.push_back(elemIndex);
                elemVec.push_back(elemIndex + ringStride);
            }
        }
        
        ringRadian += ringStep;
        tx += ringTexStep;
    }
}

MINE_NAMESPACE_END
