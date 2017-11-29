//
//  main.cpp
//  simpletest
//
//  Created by xy on 05/09/2017.
//  Copyright © 2017 SangDesu. All rights reserved.
//

#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static const struct {
    float x, y;
    float r, g, b;
} vertices[3] = {
    {-0.6f, -0.4f, 1.0f, 0.0f, 0.0f},
    { 0.6f, -0.4f, 0.0f, 1.0f, 0.0f},
    { 0.0f,  0.6f, 0.0f, 0.0f, 1.0f}
};

static const char* vertex_shader_text =
"#version 400\n"
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";

static const char* fragment_shader_text =
"#version 400\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";

static void error_callback(int error, const char *description) {
    std::cout << "Error: " << description << "\n";
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main(int argc, const char * argv[]) {
    GLFWwindow *window(nullptr);
    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;
    
    glfwSetErrorCallback(error_callback);
    if(!glfwInit()) {
        return -1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    
    window = glfwCreateWindow(640,480,"Simple Test",NULL,NULL);
    if(!window) {
        glfwTerminate();
        return -2;
    }
    
    glfwSetKeyCallback(window, key_callback);
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, nullptr);
    glCompileShader(vertex_shader);
    
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, nullptr);
    glCompileShader(fragment_shader);
    
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    
    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vpos_location = glGetAttribLocation(program, "vCol");
    
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, nullptr);
    
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(2 * sizeof(float)));
    
    while(!glfwWindowShouldClose(window)) {
        float ratio;
        int width, height;
        glm::mat4 modelMatrix, projectionMatrix, modelViewProjectionMatrix;
        
        glfwGetFramebufferSize(window, &width, &height);
        ratio = static_cast<float>(width)/static_cast<float>(height);
        
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glm::rotate(modelMatrix, static_cast<float>(glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));
        projectionMatrix = glm::ortho(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);
        modelViewProjectionMatrix = projectionMatrix * modelMatrix;
        
        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(modelViewProjectionMatrix));
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}
