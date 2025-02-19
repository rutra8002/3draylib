#version 330

in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragPosition;
in vec3 fragNormal;
in vec4 fragObjectColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform vec3 viewPos;

#define MAX_LIGHTS 64
uniform struct Light {
    vec3 position;
    vec3 color;
    float intensity;
} lights[MAX_LIGHTS];
uniform int lightCount;

out vec4 finalColor;

void main() {
    vec3 normal = normalize(fragNormal);
    vec3 viewDir = normalize(viewPos - fragPosition);

    vec3 result = vec3(0.0);
    vec3 baseColor = fragObjectColor.rgb; // Use the object's color

    // Ambient light
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * baseColor;
    result += ambient;

    // Calculate contribution from each light
    for(int i = 0; i < lightCount; i++) {
        vec3 lightDir = normalize(lights[i].position - fragPosition);
        float distance = length(lights[i].position - fragPosition);

        // Diffuse
        float diff = max(dot(normal, lightDir), 0.0);
        float attenuation = lights[i].intensity / (1.0 + 0.1 * distance);
        vec3 diffuse = diff * lights[i].color * baseColor * attenuation;

        // Specular
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
        vec3 specular = 0.5 * spec * lights[i].color * attenuation;

        result += diffuse + specular;
    }

    finalColor = vec4(result, 1.0);
}