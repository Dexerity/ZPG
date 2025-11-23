#version 330
layout(location=0) in vec3 vp;
layout(location=1) in vec3 vn;
layout(location=2) in vec2 uv;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform float w = 500;

out vec3 worldPosition;
out vec3 worldNormal;
out vec2 texCoordinates;

void main () {
	vec4 modelPos = modelMatrix * vec4(w * vp, w);
	worldPosition = modelPos.xyz / modelPos.w;
	worldNormal = normalize(transpose(inverse(mat3(modelMatrix))) * vn);

	gl_Position = projectionMatrix * viewMatrix * modelPos;
	texCoordinates = uv;
}