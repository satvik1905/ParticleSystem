#include "ParticleSystem.h"
#include "Particle.h"


void nsParticleSystem::ParticleSystem::AddParticle()
{
	m_vParticleContainer.push_back(new Particle());
}

nsParticleSystem::ParticleSystem::ParticleSystem()
{
}


nsParticleSystem::ParticleSystem::~ParticleSystem()
{
	delete m_pVetices;
	std::vector<Particle *>::iterator itr;
	for (itr = m_vParticleContainer.begin(); itr != m_vParticleContainer.end(); itr++)
		m_vParticleContainer.erase(itr);	
}

void nsParticleSystem::ParticleSystem::Process(float _fTick)
{
	std::vector<Particle *>::iterator itr;
	for (itr = m_vParticleContainer.begin(); itr != m_vParticleContainer.end(); itr++)
		(*itr)->Process(_fTick);
}


void nsParticleSystem::ParticleSystem::Render(float _fTick, glm::mat4 _matView, glm::mat4 _matProjection)
{
}
