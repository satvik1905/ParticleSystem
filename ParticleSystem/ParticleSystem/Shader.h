#pragma once
#include <glm/glm.hpp>
#include <gl/glew.h>

namespace nsParticleSystem
{
	class Shader
	{

	protected:
		GLuint		m_ShaderId;
		GLuint		m_ColorID;
		GLuint		m_MatrixMVPID;
		GLuint		m_TextureID;

	public:
		Shader();
		~Shader();

		bool Initialize(const char *_pShaderVSFilePath, const char *_pShaderPSFilePath);
		
		void SetShader();
		void SetMVPMatrix(glm::mat4 _matMVP);
		void SetColor(glm::vec4 _vColor);
		void SetTexture(GLuint _Texture);
		

		GLuint GetShaderID() {
			return m_ShaderId;
		}
		GLuint GetMVPMatrixID() {
			return m_MatrixMVPID;
		}
		GLuint GetColorID() {
			return m_ColorID;
		}
		GLuint GetTextureID() {
			return m_TextureID;
		}
	};
}
