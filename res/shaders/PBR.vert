#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout(location = 5) in ivec4 boneIds; // maybe vec4 instead of ivec4?
layout(location = 6) in vec4 weights;

out vec2 TexCoords;
out vec3 WorldPos;
out vec3 Normal;
out vec4 lightProjectionOut;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];
uniform bool isAnimated;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 lightSpaceMatrix;

void main()
{
    // Calculate bones
    vec4 totalPosition = vec4(0.0f);
    for(int i = 0 ; i < MAX_BONE_INFLUENCE; i++)
    {
        if(boneIds[i] == -1)
            continue;
        if(boneIds[i] >=MAX_BONES)
        {
            totalPosition = vec4(aPos, 1.0f);
            break;
        }
        vec4 localPosition = finalBonesMatrices[boneIds[i]] * vec4(aPos, 1.0f);
        totalPosition += localPosition * weights[i];
        vec3 localNormal = mat3(finalBonesMatrices[boneIds[i]]) * aNormal;
    }
        

    // Standardized stuff
    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
    vs_out.Normal = transpose(inverse(mat3(model))) * aNormal;
    vs_out.TexCoords = aTexCoords;
    vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);

    TexCoords = aTexCoords;
    WorldPos = vec3(model * totalPosition);
    Normal = mat3(model) * aNormal;

    //gl_Position = projection * view * vec4(WorldPos, 1.0);
    if (isAnimated)
        gl_Position = projection * view * vec4(WorldPos, 1.0);
    else if (!isAnimated)
        gl_Position = projection * view * vec4(model * vec4(aPos, 1.0));

}