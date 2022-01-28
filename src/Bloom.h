#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>

class Shader;

void renderQuad();

class Bloom
{
    GLuint FBO;
    GLuint attachments[2];  // setupFBO
    GLuint pingpongFBO[2];  // GaussBlur
    GLuint pingpongBuffers[2];  // GaussBlur
    unsigned int hdrFBO;
    unsigned int colorBuffers[2];
    int screenW, screenH;
    Shader& shaderBlur;

    // config for interface
    bool bloom = true;
    bool bloomKeyPressed = false;  // no
    float exposure = 1.0f;

public:
    Bloom() = default;
    Bloom(int screenW, int screenH, Shader& shaderBlur)
        : screenW(screenW), screenH(screenH), shaderBlur(shaderBlur)
    {
        setupFBO();
        //RenderGaussBlur();
    }

    void setupFBO()
    {
        // create 2 floating point color buffers
        // (1 for normal rendering, other for brightness threshold values)
        glGenFramebuffers(1, &hdrFBO);
        glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
        
        glGenTextures(2, colorBuffers);
        for (unsigned int i = 0; i < 2; i++)
        {
            glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
            glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGB16F, screenW, screenH, 0, GL_RGB, GL_FLOAT, NULL
            );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            // attach texture to framebuffer
            glFramebufferTexture2D(
                GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0
            );
        }
        attachments[0] = GL_COLOR_ATTACHMENT0;
        attachments[1] = GL_COLOR_ATTACHMENT1;
        glDrawBuffers(2, attachments);

        // Setup two framebuffers for gaussian blur (ping-pong)
        // ----------------------------------------------------
        glGenFramebuffers(2, pingpongFBO);
        glGenTextures(2, pingpongBuffers);
        for (unsigned int i = 0; i < 2; i++)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
            glBindTexture(GL_TEXTURE_2D, pingpongBuffers[i]);
            glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGB16F, screenW, screenH, 0, GL_RGB, GL_FLOAT, NULL
            );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glFramebufferTexture2D(
                GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongBuffers[i], 0
            );
        }
    }

    // Set main shader
    void RenderGaussBlur(Shader& mainShader)
    {
        bool horizontal = true, first_iteration = true;
        int amount = 10;
        shaderBlur.use();
        for (unsigned int i = 0; i < amount; i++)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
            shaderBlur.setInt("horizontal", horizontal);
            glBindTexture(
                GL_TEXTURE_2D, first_iteration ? colorBuffers[1] : pingpongBuffers[!horizontal]
            );
            renderQuad();
            horizontal = !horizontal;
            if (first_iteration)
                first_iteration = false;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Set bloom values for main shader (PBR.vert/frag)
        mainShader.use();
        mainShader.setInt("bloomBlur", 9);
        mainShader.setInt("bloom", bloom);
        mainShader.setFloat("exposure", exposure);
        renderQuad();

        // debug Bloom
        std::cout << "bloom: " << (bloom ? "on" : "off") << "| exposure: " << exposure << std::endl;

    }

};