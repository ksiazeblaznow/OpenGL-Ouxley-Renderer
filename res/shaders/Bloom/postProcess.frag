#version 430 core
out vec4 FragColor;

in vec2 TexCoords;

layout(binding = 10) uniform sampler2D screenTexture;  // rendered main scene (with skybox)
layout (binding = 11) uniform sampler2D bloomBlur;  // bloom
uniform float exposure;  // bloom


void main()
{
    float gamma = 2.2;

    vec3 color = texture(screenTexture, TexCoords).rgb;

    // bloom
    //vec3 hdrColor = texture(scene, TexCoords).rgb;      
    vec3 bloomColor = texture(bloomBlur, TexCoords).rgb;
    //hdrColor += bloomColor; // additive blending
    color += bloomColor;
    // tone mapping
    vec3 result = vec3(1.0) - exp(-color * exposure);
    // also gamma correct while we're at it       
    result = pow(result, vec3(1.0 / gamma));
    FragColor = vec4(result, 1.0);

    // post process, post renderum, post mortem
    //color = pow(color, vec3(1.0/2.2));

    //FragColor = vec4(color, 1.0);
}
