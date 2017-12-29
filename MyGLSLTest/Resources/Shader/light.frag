#version 400

in vec3 deliveryColor;

out vec4 fragColor;

void main() {
    fragColor = vec4(deliveryColor, 1.0);
}
