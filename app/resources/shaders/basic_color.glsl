//#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = aTexCoords;
    gl_Position = projection * view * vec4(FragPos, 1.0);
}

//#shader fragment
#version 330 core

out vec4 FragColor;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;


uniform vec3 material_diffuse;
uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 ambientColor;

uniform vec3 pointLightPos;
uniform vec3 pointLightColor;
uniform float pointLightConstant;
uniform float pointLightLinear;
uniform float pointLightQuadratic;
uniform bool torchLit;

void main() {
    vec3 baseColor;

    baseColor = material_diffuse;
    vec3 norm = normalize(Normal);
    vec3 ambient = ambientColor;

    vec3 lightDirNorm = normalize(lightDir);
    float diffDir = max(dot(norm, lightDirNorm), 0.0);
    vec3 diffuseDir = diffDir * lightColor;

    vec3 diffusePoint = vec3(0.0);
    if (torchLit) {
        vec3 lightDirPoint = normalize(pointLightPos - FragPos);
        float diffPoint = max(dot(norm, lightDirPoint), 0.0);

        float distance = length(pointLightPos - FragPos);
        float attenuation = 1.0 / (pointLightConstant + pointLightLinear * distance + pointLightQuadratic * (distance * distance));

        diffusePoint = diffPoint * pointLightColor * attenuation;
    }

    vec3 result = (ambient + diffuseDir + diffusePoint) * baseColor;

    FragColor = vec4(result, 1.0);

}