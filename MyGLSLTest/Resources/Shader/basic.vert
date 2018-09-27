#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 vertexTexCoord0;

uniform mat4 modelViewProjectionMatrix;

out vec3 color;
out vec2 texCoord0;

void main() {
    color = vertexColor;
    texCoord0 = vertexTexCoord0;
    
    gl_Position = modelViewProjectionMatrix * vec4(vertexPosition, 1.0);
}
