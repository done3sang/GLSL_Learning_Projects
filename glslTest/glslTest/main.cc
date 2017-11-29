#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#pragma comment(lib, "glfw3")

static GLuint vaoHandle(0);

static void error_callback(int err, const char *desc) {
    std::cerr << "Error = " << desc << "\n";
}

bool initialize(void);
void update(float deltaTime);
void render(void);
void resize(GLFWwindow *window, int width, int height);

int main(int argc, char **argv) {
    glfwSetErrorCallback(error_callback);
    
    if (!glfwInit()) {
        std::cerr << "Error occurs" << std::endl;
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
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize);
    
    std::cout << "OpenGL Vendor:" << glGetString(GL_VENDOR) << "\n";
    std::cout << "OpenGL Render:" << glGetString(GL_RENDERER) << "\n";
    std::cout << "OpenGL Version:" << glGetString(GL_VERSION) << "\n";
    std::cout << "OpenGL Shading Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
    GLint major(0), minor(0);
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    std::cout << "OpenGL version(Integer) = " << major << "." << minor << std::endl;
    
    if (!initialize()) {
        std::cerr << "Failed to initialize Scene\n";
        glfwTerminate();
        return -1;
    }
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        update(0.016f);
        render();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    
    return 0;
}

void update(float deltaTime) {
    
}

void resize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void render(void) {
    glBindVertexArray(vaoHandle);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

bool initialize(void) {
    std::string shaderStr, line;
    const GLchar *codeArray[1] = { nullptr };
    GLint result(0);
    
    std::ifstream infile("./Shader/basic.vert", std::ifstream::in);
    if (!infile) {
        std::cerr << "Error opening file: shader/basic.vert\n";
        return false;
    }
    
    std::istreambuf_iterator<char> beg(infile), end;
    shaderStr.assign(beg, end);
    infile.close();
    
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    if (0 == vertShader) {
        std::cerr << "Error creating vertex shader.\n";
        return false;
    }
    codeArray[0] = shaderStr.c_str();
    glShaderSource(vertShader, 1, codeArray, nullptr);
    glCompileShader(vertShader);
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
    if (!result) {
        std::cerr << "Vertex shader compilation failed!\n";
        
        GLint logLen(0);
        glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLen);
        if (logLen > 0) {
            char *log = new char[logLen + 1];
            
            GLsizei written(0);
            glGetShaderInfoLog(vertShader, logLen, &written, log);
            log[logLen] = '\0';
            
            std::cerr << "Shader log: " << log << "\n";
            
            delete[] log;
        }
        
        return false;
    }
    
    std::ifstream fragfile("./Shader/basic.frag", std::ifstream::in);
    if (!fragfile) {
        std::cerr << "Error opening file: shader/basic.frag\n";
        return false;
    }
    
    shaderStr.clear();
    while (std::getline(fragfile, line)) {
        shaderStr += line + "\n";
    }
    fragfile.close();
    
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (0 == fragShader) {
        std::cerr << "Error creating fragment shader.\n";
        return false;
    }
    codeArray[0] = shaderStr.c_str();
    glShaderSource(fragShader, 1, codeArray, nullptr);
    glCompileShader(fragShader);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
    if (!result) {
        std::cerr << "Fragment shader compilation failed!\n";
        
        GLint logLen(0);
        glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLen);
        if (logLen > 0) {
            char *log = new char[logLen + 1];
            
            GLsizei written(0);
            glGetShaderInfoLog(fragShader, logLen, &written, log);
            log[logLen] = '\0';
            
            std::cerr << "Shader log: " << log << "\n";
            
            delete[] log;
        }
        
        return false;
    }
    
    GLuint prog = glCreateProgram();
    if (0 == prog) {
        std::cerr << "Error creating program object.\n";
        return false;
    }
    
    glBindAttribLocation(prog, 0, "vertexPosition");
    glBindAttribLocation(prog, 1, "vertexColor");
    
    glAttachShader(prog, vertShader);
    glAttachShader(prog, fragShader);
    glLinkProgram(prog);
    
    GLint status(0);
    glGetProgramiv(prog, GL_LINK_STATUS, &status);
    if (!status) {
        std::cerr << "Failed to link shader program!\n";
        
        GLint loglen(0);
        glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &loglen);
        
        if (loglen > 0) {
            char *log = new char[loglen + 1];
            
            GLsizei written(0);
            glGetProgramInfoLog(prog, loglen, &written, log);
            log[loglen] = '\0';
            
            std::cerr << "Program log: \n" << log;
            
            delete[] log;
        }
        
        return false;
    }
    else {
        glUseProgram(prog);
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
    
    GLuint vbo[2];
    glGenBuffers(2, vbo);
    GLuint positionBufferHandle(vbo[0]);
    GLuint colorBufferHandle(vbo[1]);
    
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positionData, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colorData, GL_STATIC_DRAW);
    
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    return true;
}

