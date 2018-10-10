//
//  MyModelGenerator.cpp
//  Mine
//
//  Created by xy on 02/01/2018.
//  Copyright © 2018 SangDesu. All rights reserved.
//

#include "MyObject.hpp"
#include "MyTemplate.hpp"
#include "MyVector.hpp"
#include "MyImage.hpp"
#include "MyTexture.hpp"
#include "MyMathUtil.hpp"
#include "MyActorComponent.hpp"
#include "MyModelComponent.hpp"
#include "MyData.hpp"
#include "MyModelGenerator.hpp"

MINE_NAMESPACE_BEGIN

MyModelComponent* MyModelGenerator::generateTorus(float innerRadius,
                                                  float outerRadius,
                                                  size_t nsides,
                                                  size_t nrings) {
    MINE_ASSERT2(innerRadius > 0.0f && outerRadius > innerRadius, "ERROR = MyModelGenerator::generateTorus, radius not paired");
    MINE_ASSERT2(nsides > 0 && nrings > 0,  "ERROR = MyModelGenerator::generateTorus, side and ring not valid");
    
    MyData<float> *vertexData = MyData<float>::data();
    MyData<unsigned int> *elemData = MyData<unsigned int>::data();
    
    torusGenerator(innerRadius, outerRadius, nsides, nrings, vertexData, elemData);
    
    MyModelComponent *model = MyModelComponent::model();
    if(!model->loadWithData(MyModelComponent::kModelPrimitiveTriangleStrip,
                              vertexData,
                              "position[3]_normal[3]_texcoord0[2]",
                              elemData)) {
        return nullptr;
    }
    
    return model;
}

MyModelComponent* MyModelGenerator::generateSimpleTriangle(float span) {
    MINE_ASSERT(span > 0.0f);
    
    float triangleData[] = {
        -span, -span, 0.0f,     1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        span, -span, 0.0f,      0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        0.0f, span, 0.0f,       0.0f, 0.0f, 1.0f,   0.5f, 1.0f
    };
    MyData<float> *vertexData = MyData<float>::dataWithRaw(triangleData, sizeof(triangleData)/sizeof(float));
    MyModelComponent *model = MyModelComponent::model();
    
    if(!model->loadWithData(MyModelComponent::kModelPrimitiveTriangles,
                            vertexData,
                            "position[3]_color[3]_texcoord0[2]",
                            nullptr)) {
        return nullptr;
    }
    
    return model;
}

void MyModelGenerator::torusGenerator(float innerRadius,
                                      float outerRadius,
                                      size_t nsides,
                                      size_t nrings,
                                      MyData<float> *vertexData,
                                      MyData<unsigned int> *elemData) {
    MINE_ASSERT(innerRadius < outerRadius && vertexData && elemData);
    
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
            
            vertexData->push_back(px);
            vertexData->push_back(py);
            vertexData->push_back(pz);
            vertexData->push_back(nx);
            vertexData->push_back(ny);
            vertexData->push_back(nz);
            vertexData->push_back(tx);
            vertexData->push_back(ty);
            
            sideRadian += sideStep;
            ty += sideTexStep;
            
            // element drawn by gl_triangle_strip
            if(ringIndex < nrings) {
                elemData->push_back(elemIndex);
                elemData->push_back(elemIndex + ringStride);
            }
        }
        
        ringRadian += ringStep;
        tx += ringTexStep;
    }
}

MINE_NAMESPACE_END
