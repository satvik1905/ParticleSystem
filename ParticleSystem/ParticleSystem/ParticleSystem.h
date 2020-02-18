#pragma once
#include "GL/glew.h"
#include <vector>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace nsParticleSystem
{
	class Texture;
	class Shader;
	class Particle;
	class ParticleSystem
	{

	private:

		struct stVertex
		{
			glm::vec3 vPosition;
			//glm::vec2 vTextureUV;
			//glm::vec3 vColor;
		};

		

	protected:
		std::vector<Particle *>	m_vParticleContainer;
		unsigned int			m_pVertexBuffer;
		unsigned int			m_pTextureBuffer;
		Shader					*m_pShader = nullptr;
		Texture					*m_pTexture = nullptr;
		unsigned int			m_unVertexCount = 6;		
		
		void		AddParticle();
		void		InitializeBuffer();	

	public:
		ParticleSystem();
		~ParticleSystem();

		bool Initialize();
		void Process(float _fTick);
		void Render(float _fTick, glm::mat4 _matView, glm::mat4 _matProjection);
	};
}

