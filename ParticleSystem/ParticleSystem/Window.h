#pragma once
#include <gl/glew.h>
#include <GLFW/glfw3.h>

namespace nsParticleSystem
{
	class Window
	{
	protected:
		GLFWwindow* m_pWinHandle;

	public:
		Window();
		~Window();
		GLFWwindow*	GetWindowHandle() { return m_pWinHandle; }
		bool		Intialize(bool _bFullScreen = true);
	};
}

