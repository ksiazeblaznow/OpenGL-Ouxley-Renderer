

#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

layout(binding = 10) uniform sampler2D screenTexture;

void main()
{
    vec3 color = texture(screenTexture, TexCoords).rgb;

    // post process, post renderum, post mortem
    color = pow(color, vec3(1.0/2.2));

    FragColor = vec4(color, 1.0);
} 
