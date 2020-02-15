#pragma once
#include <glm/glm.hpp>
#include <vector>

namespace nsParticleSystem
{
	class Particle;
	class ParticleSystem
	{

	private:
		struct stVertex
		{
			glm::vec3 vPosition;
			glm::vec2 vTextureUV;
			glm::vec3 vColor;
		};

		

	protected:
		stVertex	*m_pVetices = nullptr;
		std::vector<Particle *>	m_vParticleContainer;

		void	AddParticle();
	public:
		ParticleSystem();
		~ParticleSystem();

		void Process(float _fTick);
		void Render(float _fTick, glm::mat4 _matView, glm::mat4 _matProjection);
	};
}

