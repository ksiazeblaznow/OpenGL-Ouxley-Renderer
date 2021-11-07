#pragma once
#include <glad/glad.h>
#include <stb_image.h>

class Texture
{
public:
	GLuint ID;

	int width, height, nrChannels;
	unsigned char* data;

	Texture(const char* path);
	~Texture();

};

