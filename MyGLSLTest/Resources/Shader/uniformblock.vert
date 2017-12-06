#version 400

in vec3 vertexPosition;
in vec2 vertexTexCoord0;

out vec2 texCoord;

void main() {
    texCoord = vertexTexCoord0;
    
    gl_Position = vec4(vertexPosition, 1.0);
}
