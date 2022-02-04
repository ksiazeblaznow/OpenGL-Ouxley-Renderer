#pragma once

#include "SSBO.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "ComputeShader.h"

class ParticleSystemComp
{
public:
	ParticleSystemComp(ComputeShader& compShader)
	{
		this->compShader = std::make_shared<ComputeShader>(compShader);

		//m_ComputeShader = std::make_shared<ComputeShader>("../../res/shaders/Particles/Particles.comp");

		m_ParticlesCount = 10000;
		m_Radius = 2.0f;
		m_MinVelocity = glm::vec3(0.0f, 0.1f, 0.0f);
		m_MaxVelocity = glm::vec3(0.0f, 0.5f, 0.0f);
		m_ParticleLifeTime = 3.0f;
		m_ParticlesLifeTimeCounter = 0.0f;

		// Create Shader Storage Buffer Objects for velocity, position and index
		Begin();

		Reset();
	}

	virtual void Begin();
	virtual void Update();
	virtual void Render(Shader& particleShader, glm::mat4 modelMatrix,
		glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	void Reset();
	
public:
	GLuint m_PositionBuffer;  // glm::vec4
	GLuint m_VelocityBuffer;  // glm::vect4
	GLuint m_IndexBuffer;	  // uint32_t

	uint32_t m_ParticleVAO;

	int32_t access = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;
	uint32_t m_ParticlesCount;
	float m_Radius;
	glm::vec3 m_MinVelocity;
	glm::vec3 m_MaxVelocity;
	float m_ParticleLifeTime;
	std::shared_ptr<ComputeShader> compShader;

	float m_ParticlesLifeTimeCounter;

};