#version 400

in vec3 color;
in vec2 texCoord0;

uniform sampler2D baseTexture;
uniform float opacity;
uniform float metallic;

out vec4 fragColor;

void main() {
    fragColor = texture(baseTexture, texCoord0) * vec4(color, opacity) * metallic;
    //fragColor = vec4(color, 1.0);
    //fragColor = vec4(0.5f, 0.5f, 0.0f, 1.0f);
}
