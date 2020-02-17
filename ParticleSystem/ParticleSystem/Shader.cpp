#include "Shader.h"
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>



nsParticleSystem::Shader::Shader()
{
}


nsParticleSystem::Shader::~Shader()
{
}

bool nsParticleSystem::Shader::Initialize(const char *_pShaderVSFilePath, const char *_pShaderPSFilePath)
{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(_pShaderVSFilePath, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", _pShaderVSFilePath);
		getchar();
		return false;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(_pShaderPSFilePath, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", _pShaderVSFilePath);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", _pShaderPSFilePath);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Link the program
	printf("Linking program\n");
	m_unShaderID = glCreateProgram();
	glAttachShader(m_unShaderID, VertexShaderID);
	glAttachShader(m_unShaderID, FragmentShaderID);
	glLinkProgram(m_unShaderID);

	// Check the program
	glGetProgramiv(m_unShaderID, GL_LINK_STATUS, &Result);
	glGetProgramiv(m_unShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(m_unShaderID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
		return false;
	}


	//uniform "Color" 
	m_unColorID = glGetUniformLocation(m_unShaderID, "ParticleColor");

	//uniform "MVP" 
	m_unMatrixMVPID = glGetUniformLocation(m_unShaderID, "matrixModelViewProj");

	//uniform "Texture"
	m_unTextureID = glGetUniformLocation(m_unShaderID, "ParticleTexture");


	glDetachShader(m_unShaderID, VertexShaderID);
	glDetachShader(m_unShaderID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);


	return true;
}

void nsParticleSystem::Shader::SetShader()
{
	glUseProgram(m_unShaderID);
}

void nsParticleSystem::Shader::SetMVPMatrix(glm::mat4 _matMVP)
{
	glUniformMatrix4fv(m_unMatrixMVPID, 1, GL_FALSE, &_matMVP[0][0]);
}

void nsParticleSystem::Shader::SetColor(glm::vec4 _vColor)
{
	glUniform4f(m_unColorID, _vColor.r, _vColor.g, _vColor.b, _vColor.a);
}

void nsParticleSystem::Shader::SetTexture(unsigned int _Texture)
{
	glBindTexture(GL_TEXTURE_2D, _Texture);
	glUniform1i(m_unTextureID, 0);
}