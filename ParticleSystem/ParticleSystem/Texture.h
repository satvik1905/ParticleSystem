#pragma once

namespace nsParticleSystem
{
#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

	class Texture
	{

	protected:
		unsigned int m_unTexture;

	public:
		Texture();
		~Texture();

		bool LoadTexture(const char *_pFilePath);
		unsigned int GetTexture();
	};
}
