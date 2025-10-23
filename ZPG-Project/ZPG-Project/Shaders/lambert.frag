#version 330
in vec4 worldPosition;
in vec3 worldNormal;

uniform vec3 objectColor;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float lightIntensity;


out vec4 outColor;
void main(void) {
	vec3 lightToVector = lightPosition - worldPosition.xyz;

	float diff = max(dot(normalize(lightToVector),normalize(worldNormal)),0.0);
	
	vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
	outColor = ambient + (diff * vec4(objectColor * lightColor * lightIntensity, 1.0));
}