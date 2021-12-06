#pragma once
#include <glad/glad.h>
#include <iostream>

class Framebuffer
{
	int screenWidth;  // #warning stiff value
	int screenHeight;

public:
	GLuint ID;
	GLuint RBO;
	GLuint texture;

	Framebuffer(int scrWidth, int scrHeight)
		: screenWidth(scrWidth), screenHeight(scrHeight)
	{
		//Create();
	}

	// create frambuffer
	void Create()
	{
		// framebuffer
		glGenFramebuffers(1, &ID);
		glBindFramebuffer(GL_FRAMEBUFFER, ID);

		// zalaczniki tekstur
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screenWidth, screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// podpiecie tekstury do bufora ramki
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
		
		/*
		Jeœli chcesz renderowaæ ca³y ekran do tekstury o mniejszym
		lub wiêkszym rozmiarze, musisz ponownie wywo³aæ glViewport
		(przed renderowaniem do bufora ramki) z wymiarami twojej
		tekstury, w przeciwnym razie tylko ma³a czêœæ tekstury lub
		ekranu zostanie zapisana w teksturze.
		*/
		/*glTexImage2D(
			GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, screenWidth, screenHeight, 0,
			GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
			GL_TEXTURE_2D, texture, 0);*/


		// renderbuffer
		glGenRenderbuffers(1, &RBO);
		// powiaz renderbuffer
		glBindRenderbuffer(GL_RENDERBUFFER, RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screenWidth, screenHeight);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
	
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	
	// 1. stworz
	// 2. tylko bindowanie
	// ta funkcja wygl¹da jak powtórka z Create() ale by³o przecie¿ po kolei na learnopengl ftw
	void RenderToTexture()
	{
		glGenFramebuffers(1, &ID);
		glBindFramebuffer(GL_FRAMEBUFFER, ID);

		// tworzymy obraz tekstury, który za³¹czamy
		// jako za³¹cznik koloru do bufora ramki.
		unsigned int texColorBuffer;
		glGenTextures(1, &texColorBuffer);
		glBindTexture(GL_TEXTURE_2D, texColorBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screenWidth, screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		// do³¹cz j¹ do aktualnego obiektu framebuffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

		// renderbuffer
		glGenRenderbuffers(1, &RBO);
		glBindRenderbuffer(GL_RENDERBUFFER, RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screenWidth, screenHeight);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

		// sprawdz czy renderbuffer jest kompletny
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << "\n";
		glBindFramebuffer(GL_FRAMEBUFFER, 0);


		// scene->Render();
	}

};