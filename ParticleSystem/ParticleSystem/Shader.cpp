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
	// 1. Fetch Shader Code
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{

		// open files
		vShaderFile.open(".\\Resources\\Shaders\\VS.glsl", std::ios::in);
		fShaderFile.open(".\\Resources\\Shaders\\PS.glsl", std::ios::in);

		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		//std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		return false;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();


	// 2. compile shaders	
	int success; char infoLog[512];
	//vertex Shader
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vShaderCode, NULL);
	glCompileShader(vertexShaderId);
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
		//std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	};

	//Pixel Shader
	GLuint pixelShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(pixelShaderId, 1, &fShaderCode, NULL);
	glCompileShader(pixelShaderId);
	glGetShaderiv(pixelShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(pixelShaderId, 512, NULL, infoLog);
		//std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	};



	//3. shader Program
	m_ShaderId = glCreateProgram();
	glAttachShader(m_ShaderId, vertexShaderId);
	glAttachShader(m_ShaderId, pixelShaderId);
	glLinkProgram(m_ShaderId);
	// print linking errors if any
	glGetProgramiv(m_ShaderId, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_ShaderId, 512, NULL, infoLog);
		//std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return false;
	}

	// Get a handle for our "Color" uniform
	m_ColorID = glGetUniformLocation(m_ShaderId, "ParticleColor");

	// Get a handle for our "MVP" uniform
	m_MatrixMVPID = glGetUniformLocation(m_ShaderId, "matrixModelViewProj");

	// Get a handle for our "TextureSampler" uniform
	m_TextureID = glGetUniformLocation(m_ShaderId, "ParticleTexture");

	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertexShaderId);
	glDeleteShader(pixelShaderId);

	return true;
}

void nsParticleSystem::Shader::SetShader()
{
	glUseProgram(m_ShaderId);
}

void nsParticleSystem::Shader::SetMVPMatrix(glm::mat4 _matMVP)
{
	glUniformMatrix4fv(m_MatrixMVPID, 1, GL_FALSE, &_matMVP[0][0]);
}

void nsParticleSystem::Shader::SetColor(glm::vec4 _vColor)
{
	glUniform4f(m_ColorID, _vColor.r, _vColor.g, _vColor.b, _vColor.a);
}

void nsParticleSystem::Shader::SetTexture(GLuint _Texture)
{
	//Set Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _Texture);
	glUniform1i(m_TextureID, 0);
}

