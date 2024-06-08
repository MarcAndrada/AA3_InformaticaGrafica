#version 440 core

struct AmbientLight {
    vec3 color;
    float ambientIntensity;
};

uniform vec2 windowSize;
uniform sampler2D textureSampler;
uniform AmbientLight ambientLight;

uniform vec3 sourceLight;
uniform vec3 sunColor;
uniform vec3 moonColor;
uniform float lerpTime;

uniform bool flashlightOn;
uniform vec3 cameraPosition;
uniform vec3 cameraForward;
uniform float innerAngle;
uniform float outerAngle;

in vec2 uvsFragmentShader;
in vec3 normalsFragmentShader;
in vec4 primitivePosition;

vec3 color;

out vec4 fragColor;

void main() {

        vec2 adjustTexCoord = vec2(uvsFragmentShader.x, 1.0 - uvsFragmentShader.y);

        vec4 textureColor = texture(textureSampler, adjustTexCoord);
        vec3 dayLightColor = mix(moonColor, sunColor, lerpTime);

        vec3 ambiendDayColor = ambientLight.color * dayLightColor;
        vec3 ambientColor = ambiendDayColor * ambientLight.ambientIntensity;

        vec4 lightedTextureColor = textureColor * vec4(dayLightColor, 1);

        vec3 lightDirection = normalize(sourceLight - primitivePosition.xyz);
        float sourceLightAngle = dot(normalsFragmentShader, lightDirection);

        color = vec3(lightedTextureColor.rgb * sourceLightAngle) + ambientColor;
        
        if(flashlightOn)
        {
            vec3 normalizedForward = normalize(cameraForward);
            vec3 line = normalize(cameraPosition - primitivePosition.xyz);
            float distanceToCamera = length(cameraPosition - primitivePosition.xyz);
            float attenuation = 1 / (distanceToCamera * distanceToCamera);
            float forwardProjection = dot(normalizedForward, -line);
            float spotlightEffect = smoothstep(cos(radians(outerAngle)), cos(radians(innerAngle)), forwardProjection);
            
            color += textureColor.rgb * spotlightEffect * attenuation;

       }

       fragColor = vec4(color, 1);
}
