#include "Particle.h"



nsParticleSystem::Particle::Particle(glm::vec3 _vPos, glm::vec4 _vColor)
	:m_vPos(_vPos),
	m_vSpeed((float)rand() / (RAND_MAX), (float)rand() / (RAND_MAX)+(rand() % (3) + 1), 0.0f),
	m_vColor(_vColor),
	//m_fSize(0.0125),
	m_fSize(0.0625f),
	m_fLife(1.0),
	m_eType(eTYPE::EN_FIRE)
{

}


nsParticleSystem::Particle::~Particle()
{
}

void nsParticleSystem::Particle::Process(float _fTick)
{
	//this->m_fSize += 1.00125 * _fTick;	
	this->m_fLife -= 1.125 * _fTick;
	this->m_vColor.a -= 1.125 * _fTick;	
	this->m_vPos = this->m_vPos + _fTick * this->m_vSpeed;

	if (m_fLife < 0.1)
		m_eType = eTYPE::EN_FADE2;
	else if (m_fLife < 0.2)
		m_eType = eTYPE::EN_FADE1;
	else if (m_fLife < 0.5)
		m_eType = eTYPE::EN_SMOKE;
}


