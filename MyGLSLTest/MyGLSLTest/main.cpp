//
//  main.cpp
//  MyGLSLTest
//
//  Created by xy on 01/12/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "MyGLSLAll.hpp"

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

USING_MINE_NAMESPACE;

static void errorCallback(int err, const char *desc) {
    std::cout << "Error(" << err << ") = " << desc << "\n";
}

void resize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

static const std::string vertexShaderSource = "#version 400\n"
"in vec3 vertexPosition;\n"
"in vec3 vertexColor;\n"
"out vec3 outColor;\n"
"uniform mat4 modelViewProjectionMatrix = mat4(1.0);\n"
"void main() {\n"
"outColor = vertexColor;\n"
"gl_Position = modelViewProjectionMatrix * vec4(vertexPosition, 1.0);\n"
"}\n";

static const std::string fragmentShaderSource = "#version 400\n"
"in vec3 outColor;\n"
"out vec4 fragColor;\n"
"void main() {\n"
"fragColor = vec4(outColor, 1.0);\n"
"}\n";

class MyErrorDisposer: public MyErrorCallback {
public:
    void disposeError(int errCode, const std::string &errDesc) {
        std::cout << "Error(" << errCode << ") = " << errDesc << "\n";
    }
};

int main(int argc, const char * argv[]) {
    glfwSetErrorCallback(errorCallback);
    if(!glfwInit()) {
        std::cout << "Error occurs" << std::endl;
        return -1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWwindow *window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -2;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize);
    
    MyErrorDisposer errDisposer;
    
    MyErrorDesc::sharedErrorDesc()->errorCallback(errDisposer);
    
    MyGLSL *sharedGLSL = MyGLSL::sharedGLSL();
    MyRenderer *sharedRenderer = MyRenderer::sharedRenderer();
    
    sharedRenderer->clearBufferBit(MyRenderer::kBufferBitColor | MyRenderer::kBufferBitDepth);
    
    MyShader *vertexShader = MyShader::createWithShaderType(MyShader::kShaderTypeVertex);
    if(!MyErrorDesc::successed(vertexShader->loadFromSource(vertexShaderSource))) {
        std::cout << "Error occurs in shader: " << vertexShader->shaderLog() << "\n";
        
        glfwTerminate();
        sharedGLSL->closeGLSL();
        
        return -3;
    }
    
    MyShader *fragmentShader = MyShader::createWithShaderType(MyShader::kShaderTypeFragment);
    if(!MyErrorDesc::successed(fragmentShader->loadFromSource(fragmentShaderSource))) {
        std::cout << "Error occurs in shader: " << fragmentShader->shaderLog() << "\n";
        
        glfwTerminate();
        sharedGLSL->closeGLSL();
        
        return -3;
    }
    
    MyProgram *program = MyProgram::create();
    program->attachShader(*vertexShader);
    program->attachShader(*fragmentShader);
    if(!MyErrorDesc::successed(program->linkPorgram())) {
        std::cout << "Error occurs in program: " << program->programLog() << "\n";
        
        glfwTerminate();
        sharedGLSL->closeGLSL();
        
        return -4;
    }
    
    float positionData[] = {
        -0.8f, -0.8f, 0.0f,
        0.8f, -0.8f, 0.0f,
        0.0f, 0.8f, 0.0f
    };
    float colorData[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
    
    MyBufferObject *positionBuffer = MyBufferObject::createWithBufferType(MyBufferObject::kBufferArray);
    positionBuffer->bufferData(9 * sizeof(float), positionData);
    
    MyBufferObject *colorBuffer = MyBufferObject::createWithBufferType(MyBufferObject::kBufferArray);
    colorBuffer->bufferData(9 * sizeof(float), colorData);
    
    MyVertexArrayObject *vertexArray = MyVertexArrayObject::create();
    vertexArray->vertexAttribPoint(*positionBuffer, MyProgram::kAttribPosition, 3, 0);
    vertexArray->vertexAttribPoint(*colorBuffer, MyProgram::kAttribColor, 3, 0);
    
    glm::mat4 rotationMatrix;
    float rotationAngle(0.0f);
    
    while(!glfwWindowShouldClose(window)) {
        rotationMatrix = glm::rotate(glm::mat4(1.0f), rotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));
        rotationAngle += 1.0f;
        
        sharedRenderer->prepareRender();
        
        program->useProgram();
        //program->uniformMatrix4("modelViewProjectionMatrix", rotationMatrix);
        
        vertexArray->bindVertexArray();
        sharedRenderer->drawArrays(MyRenderer::kRenderPrimitiveTriangles, 0, 3);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    sharedGLSL->closeGLSL();
    glfwTerminate();
    
    return 0;
}
