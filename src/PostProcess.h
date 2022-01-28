#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "Shader.h"

void renderQuad();

class PostProcess
{
public:
	Shader *shader;

	// Takes postProcessShader to itself	
	PostProcess(Shader &shader)
	{
		this->shader = &shader;
		this->shader->use();
		this->shader->setInt("screenTexture", 10);
	}

	void Use()
	{
		this->shader->use();
	}


};