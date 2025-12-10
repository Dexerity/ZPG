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

uniform float ra = 0.1;
uniform float rd = 1.0;
uniform float rs = 1.0;
uniform float h = 32;

out vec4 fragColor;

vec3 calculateLighting(vec3 norm, vec3 viewDir, vec3 lightDir, vec3 lightColor, float lightIntensity, float lightAtt)
{
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = rd * diff * lightColor * lightIntensity;

    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(reflectDir, viewDir), 0.0), h);
    vec3 specular = rs * spec * vec3(1.0);

    return (diffuse + specular) * lightAtt;
}

vec3 calculatePointLight(Light light, vec3 norm, vec3 viewDir, vec3 lightVector, float d)
{
    vec3 lightDir = normalize(lightVector);
    float lightAtt = 1.0 / (light.k_c + light.k_l * d + light.k_q * d * d);

    return calculateLighting(norm, viewDir, lightDir, light.color, light.intensity, lightAtt);
}

vec3 calculateDirectionalLight(Light light, vec3 norm, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    float lightAtt = 1.0;
    
    return calculateLighting(norm, viewDir, lightDir, light.color, light.intensity, lightAtt);
}

vec3 calculateSpotLight(Light light, vec3 norm, vec3 viewDir, vec3 lightVector, float d)
{
    vec3 lightDir = normalize(lightVector);
    
    float lightAtt = 1.0 / (light.k_c + light.k_l * d + light.k_q * d * d);
    
    float lightAngle = dot(normalize(-lightVector), normalize(light.direction));
    float spotIntensity = 0.0;

    if (lightAngle > light.alpha) {
        spotIntensity = clamp((lightAngle - light.alpha) / (1.0 - light.alpha), 0.0, 1.0);
    }
    
    return calculateLighting(norm, viewDir, lightDir, light.color, light.intensity, lightAtt) * spotIntensity;
}

void main(void) {
    vec3 color;
    if (objectColor.r < 0.0)
        color = texture(textureUnitID, texCoordinates).rgb;
    else
        color = objectColor;

    vec3 norm = normalize(worldNormal);
    vec3 viewDir = normalize(cameraPosition - worldPosition);

    vec3 finalLighting = vec3(1.0) * ra;
    
    for (int i = 0; i < lightsCount; i++) {
        vec3 lightVector = lights[i].position - worldPosition;
        float d = length(lightVector);

        if (lights[i].type == 1) 
        {
            finalLighting += calculateDirectionalLight(lights[i], norm, viewDir);
        }
        else if (lights[i].type == 2) 
        {
            finalLighting += calculateSpotLight(lights[i], norm, viewDir, lightVector, d);
        }
        else 
        {
            finalLighting += calculatePointLight(lights[i], norm, viewDir, lightVector, d);
        }
    }

    fragColor = vec4(color * finalLighting, 1.0);
}