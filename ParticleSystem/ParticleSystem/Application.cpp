#include <iostream>
#include <gl/glew.h>
#include "Window.h"
#include "ParticleSystem.h"

#include <time.h>

int main()
{
	nsParticleSystem::Window *pWindow = new nsParticleSystem::Window();
	bool bRturnValue = pWindow->Intialize();
	if (!bRturnValue)
	{
		std::cout << "Failed to Create OpenGL Window";
		return false;
	}
	
	srand(time(NULL));
	double lastTime = glfwGetTime(), duration = 0.0f, dScreenColorR = 0.0f, dScreenColorG = 0.0f, dScreenColorB = 0.0f;
	do
	{
		double currentTime = glfwGetTime();
		double Tick = currentTime - lastTime;
		lastTime = currentTime;


		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		duration += Tick;
		if (duration > 1.0f)
		{
			duration = 0.0f;
			dScreenColorR = (double)rand() / (RAND_MAX);
			dScreenColorG = (double)rand() / (RAND_MAX);
			dScreenColorB = (double)rand() / (RAND_MAX);
		}

		glClearColor(dScreenColorR, dScreenColorG, dScreenColorB, 1.0f);



		// Swap buffers
		glfwSwapBuffers(pWindow->GetWindowHandle());
		glfwPollEvents();
	}
	while ((glfwGetKey(pWindow->GetWindowHandle(), GLFW_KEY_ESCAPE) != GLFW_PRESS) && (glfwWindowShouldClose(pWindow->GetWindowHandle()) == 0));
	

	delete pWindow;

	return 0;
}