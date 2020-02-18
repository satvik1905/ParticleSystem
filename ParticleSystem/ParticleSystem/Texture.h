#pragma once
#include <gl/glew.h>
#include <vector>

namespace nsParticleSystem
{
#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

	class Texture
	{

	protected:				
		std::vector<GLuint> m_vTextureIDList;

	public:
		Texture();
		~Texture();

		bool LoadTexture(const char *_pFilePath);
		GLuint GetTexture(int _index);		
	};
}
