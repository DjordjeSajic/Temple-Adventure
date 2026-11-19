//#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    TexCoords = aTexCoords;

    gl_Position = projection * model * vec4(aPos, 1.0);
}
//#shader fragment
#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform bool hasTexture;
uniform vec3 material_diffuse;

void main()
{
    vec3 baseColor;

    if (hasTexture)
    baseColor = texture(texture_diffuse1, TexCoords).rgb;
    else
    baseColor = material_diffuse;

    // Make the torch appear lit
    vec3 glowColor = vec3(1.0, 0.45, 0.1);

    vec3 finalColor = baseColor * glowColor;

    FragColor = vec4(finalColor, 1.0);
}
