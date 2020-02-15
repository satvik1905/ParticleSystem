#include "Window.h"


nsParticleSystem::Window::Window()
{
}


nsParticleSystem::Window::~Window()
{
	glfwTerminate(); //Free glfw Resources
}

bool nsParticleSystem::Window::Intialize(bool _bFullScreen)
{
	// Initialise GLFW Library
	if (!glfwInit())
		return false;



	if(_bFullScreen)
		m_pWinHandle = glfwCreateWindow(100, 100, "ParticleSystem", glfwGetPrimaryMonitor(), nullptr);
	else
		m_pWinHandle = glfwCreateWindow(1000, 800, "ParticleSystem", nullptr, nullptr);
	if (!m_pWinHandle)
		return false;

	if (!m_pWinHandle)
	{
		glfwTerminate(); //Free glfw Resources
		return false;
	}

	//Set Current Window
	glfwMakeContextCurrent(m_pWinHandle);


	//Intialize GLEW
	glewExperimental = true;
	GLenum err = glewInit();
	if (err != GLEW_OK)
		return 0;
	return true;
}
