#version 330 core

//Input Fragment Shader : Texture Coordinate
in vec2 vTexUV;
//in vec3 vColor;

//Output Fragment Shader : Final Pixel Color
out vec4 PixelColor;


//Texture Sampler
uniform sampler2D ParticleTexture;

//Particle Color
uniform vec4 ParticleColor;


void main()
{	
	vec4 TextureColor = texture(ParticleTexture, vTexUV);
	//vec3 ColorEffect = vColor + ParticleColor;
	PixelColor = TextureColor;//ParticleColor;//vec4(ParticleColor, 1.0);//vec4(1.0f, 0.0f, 0.0f, 1.0f);	
}