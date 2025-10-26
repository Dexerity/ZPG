#version 330

struct Light {
    vec3 color;
    float intensity;
    vec3 position;
};

in vec3 worldPosition;
in vec3 worldNormal;

uniform float k_c;
uniform float k_l;
uniform float k_q;

uniform vec3 objectColor;

uniform vec3 cameraPosition;

uniform Light lights[20];
uniform int lightsCount;

out vec4 fragColor;

void main(void) {
    vec3 norm = normalize(worldNormal);
    vec3 viewDir = normalize(cameraPosition - worldPosition);

	fragColor = vec4(0.0, 0.0, 0.0, 1);

    for (int i = 0; i < lightsCount; i++) {
	float d = length(lights[i].position - worldPosition);
	float lightAtt = 1.0 / (k_c + k_l * d + k_q * d * d);

        vec3 lightDir = normalize(lights[i].position - worldPosition);

        vec4 ambient = 0.1 * vec4(lights[i].color, 1.0);

        float diff = max(dot(norm, lightDir), 0.0);
        vec4 diffuse = diff * vec4(lights[i].color, 1.0) * lights[i].intensity;

        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
        vec4 specular = spec * vec4(1.0, 1.0, 1.0, 1.0);

        fragColor += (ambient + diffuse * vec4(objectColor, 1) + specular) * lightAtt;
    }
}