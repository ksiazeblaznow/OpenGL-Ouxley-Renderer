#pragma once
#include <glad/glad.h>
#include <cstdlib>
#include <ctime>

#define NUM_PARTICLES 1024*1024 // total number of particles to move
#define WORK_GROUP_SIZE 128 // # work-items per work-group



class ParticleSystem
{
public:
	GLuint posSSbo;
	GLuint velSSbo;
	GLuint colSSbo;

	//void glDispatchCompute(num_groups_x, num_groups_y, num_groups_z)

	struct pos
	{
		float x, y, z, w; // positions
	};
	struct vel
	{
		float vx, vy, vz, vw;
	};
	struct color
	{
		float r, g, b, a;
	};

	void Setup()
	{
		// to_delete
		srand(time(NULL));

		// position
		glGenBuffers(1, &posSSbo);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, posSSbo);
		glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_PARTICLES * sizeof(pos) * 4, NULL, GL_STATIC_DRAW);
		GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT; // the invalidate makes a big difference when re-writing
		//struct pos* points = (struct pos*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_PARTICLES * sizeof(struct pos), bufMask);
		pos *points = (struct pos*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_PARTICLES * sizeof(struct pos), bufMask);
		for (int i = 0; i < NUM_PARTICLES; i++)
		{
			points[i].x = rand() % 100 - 50;
			points[i].y = rand() % 100 - 50;
			points[i].z = rand() % 100 - 50;
			points[i].w = 1;
		}
		glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
		
		// velocity
		glGenBuffers(1, &velSSbo);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, velSSbo);
		glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_PARTICLES * sizeof(struct vel), NULL, GL_STATIC_DRAW);
		struct vel* vels = (struct vel*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_PARTICLES * sizeof(struct vel), bufMask);
		//vels = (vel*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_PARTICLES * sizeof(vel), bufMask);
		for (int i = 0; i < NUM_PARTICLES; i++)
		{
			vels[i].vx = rand() % 100 / 100.f;
			vels[i].vy = rand() % 100 / 100.f;
			vels[i].vz = rand() % 100 / 100.f;
			vels[i].vw = 1;

		}
		glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

		// color
		glGenBuffers(1, &colSSbo);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, colSSbo);
		glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_PARTICLES * sizeof(struct color), NULL, GL_STATIC_DRAW);
		struct color* cols = (struct color*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_PARTICLES * sizeof(struct color), bufMask);
		//color* cols = (color*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_PARTICLES * sizeof(color), bufMask);
		for (int i = 0; i < NUM_PARTICLES; i++)
		{
			cols[i].r = rand() % 100 / 100.f;
			cols[i].g = rand() % 100 / 100.f;
			cols[i].b = rand() % 100 / 100.f;
			cols[i].a = 1;

		}
		glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
	}

	// comp Shader and standard shader to display it
	void Run(ComputeShader& compShader, Shader& particleStandardShader)
	{
		//compShader.Use();

		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, posSSbo);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, colSSbo);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, velSSbo);

		glDispatchCompute(NUM_PARTICLES/ WORK_GROUP_SIZE, 1, 1);
		glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

		particleStandardShader.use();
		glBindBuffer(GL_ARRAY_BUFFER, posSSbo);
		glVertexPointer(4, GL_FLOAT, 0, (void*)0);
		glEnableClientState(GL_VERTEX_ARRAY);
		glDrawArrays(GL_POINTS, 0, NUM_PARTICLES);
		glDisableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
};
