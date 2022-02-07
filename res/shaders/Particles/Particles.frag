#version 450 core

layout (location = 0) in vec2 v_TexCoord;

layout (location = 0) out vec4 f_Color;

void main()
{
    vec4 color = { 0.5f, 0.2f, 1.0f, 1.0f };

    f_Color = color;
}