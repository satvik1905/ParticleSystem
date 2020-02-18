#pragma once
#include <glm/glm.hpp>

namespace nsParticleSystem 
{
	class Particle
	{
	protected:
		enum eTYPE
		{
			EN_FIRE = 0,
			EN_SMOKE = 1,
			EN_FADE1 = 2,
			EN_FADE2 = 3
		};

	//protected:
	public:
		glm::vec3		m_vPos;
		glm::vec3		m_vSpeed;
		glm::vec4		m_vColor;
		float			m_fSize;
		float			m_fLife;
		eTYPE 			m_eType;

	public:
		Particle(glm::vec3 _vPos, glm::vec4 _vColor);
		~Particle();

		void Process(float _fTick);		
	};

}
