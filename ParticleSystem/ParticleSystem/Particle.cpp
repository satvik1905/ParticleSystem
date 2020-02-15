#include "Particle.h"



void nsParticleSystem::Particle::SetLife(float _fLife)
{	
	m_fLife = _fLife;
}

void nsParticleSystem::Particle::SetSize(float _fSize)
{
	m_fSize = _fSize;
}

nsParticleSystem::Particle::Particle()
	:m_vPos(0.0f, 0.0f, 0.0f),
	m_vSpeed(0.0f, 0.0f, 0.0f),
	m_vColor(0.0f, 0.0f, 0.0f),
	m_fSize(0.5),
	m_fLife(1.0)
{

}


nsParticleSystem::Particle::~Particle()
{
}

void nsParticleSystem::Particle::Process(float _fTick)
{
	this->SetSize(this->m_fSize * _fTick);
	this->SetLife(this->m_fLife * _fTick);
}


