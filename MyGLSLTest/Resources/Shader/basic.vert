#version 400

in vec3 vertexPosition;
in vec3 vertexColor;

uniform mat4 modelViewProjectionMatrix;

out vec3 color;

void main() {
    color = vertexColor;
    gl_Position = modelViewProjectionMatrix * vec4(vertexPosition, 1.0);
}
