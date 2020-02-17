#include "ParticleSystem.h"
#include "Particle.h"
#include "Shader.h"
#include "Texture.h"
#include <gl/glew.h>


#include <glm/gtc/matrix_transform.hpp>


void nsParticleSystem::ParticleSystem::AddParticle()
{
	float fPosX = ((float)rand() / (RAND_MAX)) + (rand() % (5) + (-3));
	float fPosY = ((float)rand() / (RAND_MAX)) + (rand() % (5) + (-3));
	glm::vec3 vPos = glm::vec3(fPosX, fPosY, 0);
	glm::vec4 vColor = glm::vec4((float)rand() / (RAND_MAX), (float)rand() / (RAND_MAX), (float)rand() / (RAND_MAX), 1.0f);
	
	this->m_vParticleContainer.push_back(new Particle(vPos, vColor));
}

void nsParticleSystem::ParticleSystem::InitializeBuffer()
{
	this->m_unVertexCount = 6;
	stVertex *pVertices = new stVertex[m_unVertexCount];
	
	//First
	pVertices[0].vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	/*pVertices[0].vTextureUV = glm::vec2(0.0f, 0.0f);
	pVertices[0].vColor = glm::vec3(1.0f, 1.0f, 0.0f);*/
	
	pVertices[1].vPosition = glm::vec3(1.0f, 0.0f, 0.0f);
	/*pVertices[1].vTextureUV = glm::vec2(0.0f, 0.0f);
	pVertices[1].vColor = glm::vec3(1.0f, 1.0f, 0.0f);*/
	
	pVertices[2].vPosition = glm::vec3(1.0f, 1.0f, 0.0f);
	/*pVertices[2].vTextureUV = glm::vec2(0.0f, 0.0f);
	pVertices[2].vColor = glm::vec3(1.0f, 1.0f, 0.0f);*/
	
	//Second
	pVertices[3].vPosition = glm::vec3(1.0f, 1.0f, 0.0f);
	/*pVertices[3].vTextureUV = glm::vec2(0.0f, 0.0f);
	pVertices[3].vColor = glm::vec3(1.0f, 1.0f, 0.0f);*/

	pVertices[4].vPosition = glm::vec3(0.0f, 1.0f, 0.0f);
	/*pVertices[4].vTextureUV = glm::vec2(0.0f, 0.0f);
	pVertices[4].vColor = glm::vec3(1.0f, 1.0f, 0.0f);*/

	pVertices[5].vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	/*pVertices[5].vTextureUV = glm::vec2(0.0f, 0.0f);
	pVertices[5].vColor = glm::vec3(1.0f, 1.0f, 0.0f);*/


	const float pVertex[] = {
		 0.0f,  0.0f, 0.0f,
		 1.0f,  0.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,

		 1.0f,  1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
		 0.0f,  0.0f, 0.0f,

	};

	glGenBuffers(1, &m_pVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_pVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pVertex), pVertex, GL_STATIC_DRAW);

	const float pTextureUV[] = {
		 0.0f,  1.0f,
		 1.0f,  1.0f,
		 1.0f,  0.0f,

		 1.0f,  0.0f,
		 0.0f,  0.0f,
		 0.0f,  1.0f
	};
	glGenBuffers(1, &m_pTextureBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_pTextureBuffer );
	glBufferData(GL_ARRAY_BUFFER, sizeof(pTextureUV), pTextureUV, GL_STATIC_DRAW);
}

nsParticleSystem::ParticleSystem::ParticleSystem()
	:m_pShader(new Shader()),
	m_pTexture(new Texture())
{
}


nsParticleSystem::ParticleSystem::~ParticleSystem()
{	
	//Release Buffer
	glDeleteBuffers(1, &m_pVertexBuffer);

	//Release Particle Instances
	std::vector<Particle *>::iterator itr;
	for (itr = m_vParticleContainer.begin(); itr != m_vParticleContainer.end(); itr++)
		m_vParticleContainer.erase(itr);	

	delete m_pShader;
	delete m_pTexture;
}

bool nsParticleSystem::ParticleSystem::Initialize()
{
	
	if (m_pShader->Initialize(".\\Resources\\Shaders\\VS.glsl", ".\\Resources\\Shaders\\PS.glsl"))
	{
		this->InitializeBuffer();

		if (m_pTexture->LoadTexture(".\\Resources\\Textures\\test-dxt5.dds") == false)
			return false;

		for (int i = 0; i < 10; i++)
			this->AddParticle();

		return true;
	}
	return false;
}

void nsParticleSystem::ParticleSystem::Process(float _fTick)
{
	std::vector<Particle *>::iterator itr;
	for (itr = m_vParticleContainer.begin(); itr != m_vParticleContainer.end(); itr++)
	{
		Particle *pParticle = (*itr);
		if (pParticle->m_fLife < 0.0f)
			itr = m_vParticleContainer.erase(itr);
		else
			pParticle->Process(_fTick);
	}

	if (m_vParticleContainer.size() < 100)
	{		
		for (int i = 0; i < rand() % 10 + 1; i++)
			this->AddParticle();
	}
		
}


void nsParticleSystem::ParticleSystem::Render(float _fTick, glm::mat4 _matView, glm::mat4 _matProjection)
{	
	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
	m_pShader->SetShader();
	std::vector<Particle *>::iterator itr;
	for (itr = m_vParticleContainer.begin(); itr != m_vParticleContainer.end(); itr++)
	{
		auto particle = (*itr);
		
		glm::vec3 vPos = particle->m_vPos;
		glm::vec3 vSize = glm::vec3(particle->m_fSize, particle->m_fSize, 1.0f);

		glm::mat4 matModel = glm::translate(glm::mat4(1.0f), glm::vec3(vPos.x, vPos.y, vPos.z));		
		glm::mat4 matTransform = glm::scale(matModel, vSize);
		glm::mat4 MVP = _matProjection * _matView * matTransform;

		
		m_pShader->SetColor(particle->m_vColor);
		m_pShader->SetMVPMatrix(MVP);
		m_pShader->SetTexture(m_pTexture->GetTexture());
		////Set Texture
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, m_pTexture->GetTexture());
		//glUniform1i(m_pShader->GetTextureId(), 0);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		
		
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_pTextureBuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_TRIANGLES, 0, m_unVertexCount);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
}
