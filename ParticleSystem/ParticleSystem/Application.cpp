#include <iostream>
#include <gl/glew.h>
#include "Window.h"
#include "ParticleSystem.h"

#include <time.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main()
{
	nsParticleSystem::Window *pWindow = new nsParticleSystem::Window();
	if (pWindow->Intialize() == false)
	{
		std::cout << "Failed to Create OpenGL Window";
		return false;
	}
	
	nsParticleSystem::ParticleSystem *pPartileSystem = new nsParticleSystem::ParticleSystem();
	if (pPartileSystem->Initialize() == false)
	{
		std::cout << "Failed to Initialize Particle System";
		return false;
	}

	//Set View Matrix
	glm::vec3 vCameraPos = glm::vec3(0, 0, 5);
	glm::vec3 vCameraDir = glm::vec3(0, 0, 1);
	glm::vec3 vUp = glm::vec3(0, 1, 0);
	glm::mat4 matView = glm::lookAt(vCameraPos, vCameraDir, vUp);


	int count = 0;
	const GLFWvidmode *pScreen = glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);
	float fAspectRatio = (float)pScreen->width / (float)pScreen->height;
	//Set Projection Matrix
	glm::mat4 matProj = glm::perspective(glm::radians(60.0f), fAspectRatio, 0.1f, 10000.0f);


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	srand(time(NULL));
	double lastTime = glfwGetTime(), duration = 0.0f;	
	do
	{
		double currentTime = glfwGetTime();
		float Tick = (float)(currentTime - lastTime);
		lastTime = currentTime;


		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		duration += Tick;
		
		pPartileSystem->Process(Tick);
		pPartileSystem->Render(Tick, matView, matProj);

		// Swap buffers
		glfwSwapBuffers(pWindow->GetWindowHandle());
		glfwPollEvents();
	}
	while ((glfwGetKey(pWindow->GetWindowHandle(), GLFW_KEY_ESCAPE) != GLFW_PRESS) && (glfwWindowShouldClose(pWindow->GetWindowHandle()) == 0));
	

	delete pWindow;

	return 0;
}