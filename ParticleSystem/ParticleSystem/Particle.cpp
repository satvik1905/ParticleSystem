#include "Particle.h"



nsParticleSystem::Particle::Particle(glm::vec3 _vPos, glm::vec4 _vColor)
	:m_vPos(_vPos),
	m_vSpeed(0.0f, 0.0f, 0.0f),
	m_vColor(_vColor),
	m_fSize(0.0125),
	//m_fSize(1.0f),
	m_fLife(0.5)
{

}


nsParticleSystem::Particle::~Particle()
{
}

void nsParticleSystem::Particle::Process(float _fTick)
{
	this->m_fSize += 1.00125 * _fTick;	
	this->m_fLife -= 1.125 * _fTick;
	this->m_vColor.a -= 1.125 * _fTick;	
}


