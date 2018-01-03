#version 400

in vec3 color;

out vec4 fragColor;

void main() {
    //fragColor = vec4(color, 1.0);
    fragColor = vec4(0.5f, 0.5f, 0.0f, 1.0f);
}
