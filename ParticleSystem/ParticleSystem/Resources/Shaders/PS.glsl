#version 330 core

//Input Fragment Shader : Texture Coordinate
in vec2 vTexUV;

//Output Fragment Shader : Final Pixel Color
out vec4 PixelColor;


//Texture Sampler
uniform sampler2D ParticleTexture;

//Particle Color
uniform vec3 ParticleColor;


void main()
{	
	vec4 TextureColor = texture(ParticleTexture, vTexUV);
	return TextureColor;
}