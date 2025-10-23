#version 330
in vec4 worldPosition;
in vec3 worldNormal;
in vec3 camPos;

uniform vec3 objectColor;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float lightIntensity;


out vec4 outColor;

void main(void) {
	vec3 normal = normalize(worldNormal);
	vec3 viewDirection = normalize(camPos - worldPosition.xyz);

	vec3 lightToVector = normalize(lightPosition - worldPosition.xyz);
	vec3 reflectDirection = reflect(-lightToVector, normal);

	vec3 ambient = vec3(0.1, 0.1, 0.1) * objectColor;

	float dotProduct = max(dot(normal, lightToVector),0.0);
	vec3 diffuse = dotProduct * objectColor * lightColor * lightIntensity;

	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32.0);
	vec3 specular = spec * lightColor * lightIntensity;

	vec3 res = ambient + diffuse + specular;
	outColor = vec4(res, 1.0);
}