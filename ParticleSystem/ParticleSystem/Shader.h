#pragma once
#include <glm/glm.hpp>

namespace nsParticleSystem
{
	class Shader
	{

	protected:
		unsigned int		m_unShaderID;
		unsigned int		m_unColorID;
		unsigned int		m_unMatrixMVPID;
		unsigned int		m_unTextureID;

	public:
		Shader();
		~Shader();

		bool Initialize(const char *_pShaderVSFilePath, const char *_pShaderPSFilePath);
		
		void SetShader();
		void SetMVPMatrix(glm::mat4 _matMVP);
		void SetColor(glm::vec4 _vColor);
		void SetTexture(unsigned int _Texture);
		
	};
}
