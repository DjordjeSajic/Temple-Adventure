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
in vec3 Normal;
in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

uniform bool hasTexture;

uniform vec3 material_diffuse;
uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 ambientColor;

void main() {
    vec3 baseColor;

    // Pick texture if available, otherwise fallback to material diffuse color
    if (hasTexture) {
        baseColor = texture(texture_diffuse1, TexCoords).rgb;
    } else {
        baseColor = material_diffuse;
    }
    vec3 ambient = ambientColor;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightDir);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * baseColor;

    FragColor = vec4(result, 1.0);
}