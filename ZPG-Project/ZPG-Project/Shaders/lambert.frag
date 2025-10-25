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

uniform Light lights[5];
uniform int lightsCount;

out vec4 fragColor;

void main(void) {
	fragColor = vec4(0.0, 0.0, 0.0, 1);

	for (int i = 0; i < lightsCount; i++) {
		float d = length(lights[i].position - worldPosition);
		float lightAtt = 1.0 / (k_c + k_l * d + k_q * d * d);

        	float dotProduct  = max(dot(normalize(lights[i].position - worldPosition), normalize(worldNormal)), 0.0);
        	vec4 diffuse = dotProduct * vec4(lights[i].color, lights[i].intensity);

        	vec4 ambient = 0.1 * vec4(lights[i].color, 1.0);
        	fragColor += (ambient + diffuse) * vec4(objectColor, 1) * lightAtt;
    	}
}