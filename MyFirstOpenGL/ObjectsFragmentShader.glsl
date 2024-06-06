#version 440 core

struct AmbientLight {
    vec3 color;
    float ambientIntensity;
};

uniform vec2 windowSize;
uniform sampler2D textureSampler;
uniform AmbientLight ambientLight;

in vec2 uvsFragmentShader;

out vec4 fragColor;

void main() {

        vec2 adjustTexCoord = vec2(uvsFragmentShader.x, 1.0 - uvsFragmentShader.y);
        vec4 ambientColor = vec4(ambientLight.color, 1.f) * ambientLight.ambientIntensity;

        vec4 textureColor = texture(textureSampler, adjustTexCoord);
        fragColor = textureColor * ambientColor;
}
