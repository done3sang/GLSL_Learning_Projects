#version 400

in vec2 texCoord;

out vec4 fragColor;

uniform BlobSetting {
    vec4 innerColor;
    vec4 outerColor;
    float innerRadius;
    float outerRadius;
} Blob;

void main() {
    vec2 dt = texCoord - vec2(0.5, 0.5);
    float dist = length(dt);
    
    fragColor = mix(Blob.innerColor, Blob.outerColor, smoothstep(Blob.innerRadius, Blob.outerRadius, dist));
    //fragColor = mix(innerColor, outerColor, smoothstep(innerRadius, outerRadius, dist));
}
