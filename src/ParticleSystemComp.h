//#pragma once
//
//#include "SSBO.h"
//#include <glad/glad.h>
//#include <glm/glm.hpp>
//#include "ComputeShader.h"
//
//class ParticleSystemComp
//{
//public:
//	ParticleSystemComp()
//	{
//		m_ParticlesCount = 10000;
//		m_Radius = 2.0f;
//		m_MinVelocity = glm::vec3(0.0f, 0.1f, 0.0f);
//		m_MaxVelocity = glm::vec3(0.0f, 0.5f, 0.0f);
//		m_ParticleLifeTime = 3.0f;
//		m_ParticlesLifeTimeCounter = 0.0f;
//
//		Reset();
//	}
//
//	virtual void Begin();
//	virtual void Update();
//	virtual void PreRender();
//	virtual void Render();
//	virtual void Destroy();
//
//	void Reset();
//	
//	void SetParticlesCount(uint32_t count);
//	void SetParticleLifeTime(float lifeTime);
//	void SetRadius(float radius);
//	void SetMinVelocity(glm::vec3 minVelocity);
//	void SetMaxVelocity(glm::vec3 maxVelocity);
//
//private:
//	SSBO<glm::vec4> m_PositionBuffer;
//	SSBO<glm::vec4> m_VelocityBuffer;
//	SSBO<uint32_t> m_IndexBuffer;
//
//	ComputeShader m_ComputeShader("../../res/shaders/Particles/Particles.comp");
//
//	//int32_t m_NoiseTexture;
//
//	uint32_t m_ParticleVAO;
//
//	uint32_t m_ParticlesCount;
//	float m_Radius;
//	glm::vec3 m_MinVelocity;
//	glm::vec3 m_MaxVelocity;
//	float m_ParticleLifeTime;
//
//	float m_ParticlesLifeTimeCounter;
//
//};