#version 400

struct LightDef {
    vec4 position;
    vec3 color;
    float intensity;
    float ambientFactor;
    bool ambientEnabled;
    bool diffuseEnabled;
    bool specularEnabled;
    
    // point&spot
    float attenuationDistance;
    
    // spot
    bool spotlight;
    vec3 direction;
    float attenuationExponent;
    float cutoff; // cos
};

struct MaterialDef {
    vec3 baseColor;
    float shininess;
    float ambientFactor;
    float specularFactor;
};

in vec3 vertexPosition;
in vec3 vertexNormal;

out vec3 deliveryColor;

uniform LightDef lightInfo;
uniform MaterialDef matInfo;

uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelViewProjectionMatrix;

vec3 gouraudShading(LightDef lightdef, MaterialDef matdef, vec4 pos, vec3 norm) {
    vec3 color = vec3(0.0);
    vec3 sight;
    float distanceFactor = 1.0;
    
    if(lightdef.position.w == 0) {
        sight = normalize(vec3(lightdef.position));
    } else {
        sight = normalize(vec3(lightdef.position- pos));
        distanceFactor = distance(lightdef.position, pos);
        if(distanceFactor >= lightdef.attenuationDistance) {
            return color;
        }
        float spotFactor = 1.0;
        if(lightdef.spotlight) {
            float cosrad = dot(-sight, lightdef.direction);
            if(cosrad <= lightdef.cutoff) {
                return color;
            }
            spotFactor *= pow(cosrad, lightdef.attenuationExponent);
        }
        distanceFactor = 1.0 - smoothstep(lightdef.attenuationDistance - 10.0, lightdef.attenuationDistance, distanceFactor);
        distanceFactor *= spotFactor;
    }
    
    if(lightdef.ambientEnabled) {
        color += matdef.baseColor * matdef.ambientFactor;
    }
    if(lightdef.diffuseEnabled) {
        color += matdef.baseColor * max(dot(sight, norm), 0.0);
    }
    if(lightdef.specularEnabled) {
        vec3 view = normalize(vec3(-pos));
        vec3 halfway = normalize(view + sight);
        color += matdef.baseColor * pow(max(dot(halfway, norm), 0.0), matdef.shininess);
    }
    
    color *= lightdef.color * distanceFactor;
    return color;
}

void main() {
    vec3 eyeNorm = normalize(normalMatrix * vertexNormal);
    vec4 homPosition = vec4(vertexPosition, 1.0);
    vec4 eyePosition = modelViewMatrix * homPosition;
    
    deliveryColor = gouraudShading(lightInfo, matInfo, eyePosition, eyeNorm);
    
    gl_Position = modelViewProjectionMatrix * homPosition;
}
