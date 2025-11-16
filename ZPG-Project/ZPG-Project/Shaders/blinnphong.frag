#version 330

struct Light {
    int type;

    vec3 color;
    float intensity;
    vec3 position;

    float k_c;
    float k_l;
    float k_q;

    vec3 direction;
    float range;
    float alpha;
};

in vec3 worldPosition;
in vec3 worldNormal;
in vec2 texCoordinates;

uniform vec3 objectColor;
uniform vec3 cameraPosition;

uniform Light lights[20];
uniform int lightsCount;

uniform sampler2D textureUnitID;

out vec4 fragColor;

void main(void) {

    vec3 color;
    if (objectColor.r < 0.0)
        color = texture(textureUnitID, texCoordinates).rgb;
    else
        color = objectColor;

    vec3 norm = normalize(worldNormal);
    vec3 viewDir = normalize(cameraPosition - worldPosition);

    vec3 finalLighting = vec3(0.1);

    for (int i = 0; i < lightsCount; i++) {

        vec3 lightVector = lights[i].position - worldPosition;
        float d = length(lightVector);
        float lightAtt = 1.0;
        vec3 lightDir;

        if (lights[i].type == 1) {
            lightDir = normalize(-lights[i].direction);
        }
        else { // point & spot
            lightDir = normalize(lightVector);
            lightAtt = 1.0 / (lights[i].k_c + lights[i].k_l * d + lights[i].k_q * d * d);
        }

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lights[i].color * lights[i].intensity;

        vec3 halfDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(norm, halfDir), 0.0), 32.0);
        vec3 specular = spec * vec3(1.0);

        if (lights[i].type == 2) {
            float dotLF = dot(normalize(-lightVector), normalize(lights[i].direction));
            float spotIntensity = 0.0;

            if (dotLF > lights[i].alpha)
                spotIntensity = clamp((dotLF - lights[i].alpha) / (1.0 - lights[i].alpha), 0.0, 1.0);

            finalLighting += (diffuse + specular) * lightAtt * spotIntensity;
        }
        else {
            finalLighting += (diffuse + specular) * lightAtt;
        }
    }

    fragColor = vec4(color * finalLighting, 1.0);
}
