#version 330

struct Light {
    vec3 color;
    float intensity;
    vec3 position;
};

in vec3 worldPosition;
in vec2 texCoordinates;

uniform vec3 objectColor;
uniform Light lights[5];
uniform int lightsCount;

uniform float k_c;
uniform float k_l;
uniform float k_q;

uniform sampler2D textureUnitID;

out vec4 fragColor;

void main () {
	vec3 color;
	
	if (objectColor.r < 0.0)
        	color = texture(textureUnitID, texCoordinates).rgb;
    	else
        	color = objectColor;

	fragColor = vec4(0.0, 0.0, 0.0, 1);

    for (int i = 0; i < lightsCount; i++) 
    {
	float d = length(lights[i].position - worldPosition);
	float lightAtt = 1.0 / (k_c + k_l * d + k_q * d * d);
        fragColor += vec4(color * lights[i].color * (lights[i].intensity * lightAtt), 1.0);   
    }
}