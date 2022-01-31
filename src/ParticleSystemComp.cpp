#include "ParticleSystemComp.h"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/constants.hpp>

void ParticleSystemComp::Begin()
{
	// GLuint m_PositionBuffer;  // glm::vec4
	// GLuint m_VelocityBuffer;  // glm::vect4
	// GLuint m_IndexBuffer;	  // uint32_t

	glGenBuffers(1, &m_PositionBuffer);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_PositionBuffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, m_ParticlesCount * sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	glGenBuffers(1, &m_VelocityBuffer);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_VelocityBuffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, m_ParticlesCount * sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	glGenBuffers(1, &m_IndexBuffer);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_IndexBuffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, m_ParticlesCount * 6 * sizeof(uint32_t), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void ParticleSystemComp::Update()
{
	m_ParticlesLifeTimeCounter += 0.016f;
	if (m_ParticlesLifeTimeCounter > m_ParticleLifeTime)
	{
		m_ParticlesLifeTimeCounter = 0.0f;

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_PositionBuffer);  // bind
		glm::vec4* positions = (glm::vec4*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, m_ParticlesCount * sizeof(glm::vec4), access);
		for (size_t i = 0; i < m_ParticlesCount; i++)
		{
			//glm::vec3 center = worldPosition;
			glm::vec3 center = { 1.f, 1.f, 1.f };

			float u = ((float)rand() / RAND_MAX) * m_Radius;
			float v = ((float)rand() / RAND_MAX) * m_Radius;
			float theta = 2.0f * glm::pi<float>() * u;
			float phi = acos(2.0f * v - 1.0f);
			float r = cbrt((float)rand() / RAND_MAX) * m_Radius;
			float sinTheta = sin(theta);
			float cosTheta = cos(theta);
			float sinPhi = sin(phi);
			float cosPhi = cos(phi);
			float x = center.x + r * sinPhi * cosTheta;
			float y = center.y + r * sinPhi * sinTheta;
			float z = center.z + r * cosPhi;


			positions[i] = glm::vec4(x, y, z, 1.0f);
		}
		glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}


	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, m_PositionBuffer);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, m_VelocityBuffer);

	compShader->Use();

	glDispatchCompute(m_ParticlesCount / 128, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

void ParticleSystemComp::Render(Shader& particleShader, glm::mat4 modelMatrix,
	glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	particleShader.use();
	particleShader.setMat4("u_Model", modelMatrix);
	particleShader.setMat4("u_View", viewMatrix);
	particleShader.setMat4("u_Projection", projectionMatrix);
	particleShader.setVec2("u_SpriteSize", glm::vec2(0.03f, 0.03f));
	//particleShader.setBool("u_IsSprite", false);
	//particleShader.setInt("u_Sprite", 0);
	//particleShader.setVec4("u_Color", glm::vec4(0.4f, 6.0f, 7.0f, std::clamp((m_ParticleLifeTime - m_ParticlesLifeTimeCounter), 0.0f, 1.0f)));

	//glDisable(GL_CULL_FACE);

	glBindVertexArray(m_ParticleVAO);

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, m_PositionBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

	glDrawElements(GL_TRIANGLES, m_ParticlesCount * 6, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, 0);

	glBindVertexArray(0);

	//glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
}

void ParticleSystemComp::Reset()
{
	/*m_PositionBuffer = std::make_shared<SSBO<glm::vec4>>(m_ParticlesCount);
	m_VelocityBuffer = std::make_shared<SSBO<glm::vec4>>(m_ParticlesCount);
	m_IndexBuffer = std::make_shared<SSBO<uint32_t>>(m_ParticlesCount * 6);*/

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_PositionBuffer);
	glm::vec4* positions = (glm::vec4*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, m_ParticlesCount * sizeof(glm::vec4), access);

	for (size_t i = 0; i < m_ParticlesCount; i++)
	{
		glm::vec3 center = { 1.f, 1.f, 1.f };

		float u = ((float)rand() / RAND_MAX) * m_Radius;
		float v = ((float)rand() / RAND_MAX) * m_Radius;
		float theta = 2.0f * glm::pi<float>() * u;
		float phi = acos(2.0f * v - 1.0f);
		float r = cbrt((float)rand() / RAND_MAX) * m_Radius;
		float sinTheta = sin(theta);
		float cosTheta = cos(theta);
		float sinPhi = sin(phi);
		float cosPhi = cos(phi);
		float x = center.x + r * sinPhi * cosTheta;
		float y = center.y + r * sinPhi * sinTheta;
		float z = center.z + r * cosPhi;

		positions[i] = glm::vec4(x, y, z, 1.0f);
	}
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_VelocityBuffer);
	glm::vec4* velocities = (glm::vec4*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, m_ParticlesCount * sizeof(glm::vec4), access);
	for (size_t i = 0; i < m_ParticlesCount; i++)
	{
		float x = (float)rand() / (RAND_MAX / (m_MaxVelocity.x - m_MinVelocity.x));
		float y = (float)rand() / (RAND_MAX / (m_MaxVelocity.y - m_MinVelocity.y));
		float z = (float)rand() / (RAND_MAX / (m_MaxVelocity.z - m_MinVelocity.z));

		velocities[i] = glm::vec4(x, y, z, 1.0f);
	}
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_IndexBuffer);
	uint32_t* indices = (uint32_t*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, 6 * m_ParticlesCount * sizeof(uint32_t), access);
	for (size_t i = 0; i < m_ParticlesCount; i++)
	{
		size_t index = i << 2;
		*(indices++) = index;
		*(indices++) = index + 1;
		*(indices++) = index + 2;
		*(indices++) = index;
		*(indices++) = index + 2;
		*(indices++) = index + 3;
	}
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	//m_ComputeShader = CreateRef<ComputeShader>("res/shaders/Particle/StandardParticle.comp");
	compShader->Use();
	compShader->SetUint("u_ParticlesCount", m_ParticlesCount);

	if (m_ParticleVAO)
	{
		glDeleteVertexArrays(1, &m_ParticleVAO);
	}

	glGenVertexArrays(1, &m_ParticleVAO);
}
