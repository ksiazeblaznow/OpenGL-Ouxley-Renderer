#version 450 core

layout (location = 0) in vec2 v_TexCoord;

layout (location = 0) out vec4 f_Color;

void main()
{
    vec4 color = { 0.9f, 0.8f, 1.0f, 1.0f };

    f_Color = color;
}