#version 330 core

// Interpolated values from the vertex shaders
in vec2 TexUV;

// Ouput data
out vec4 PixelColor;


// Values that stay constant for the whole mesh.
uniform sampler2D ParticleTexture;

uniform vec4 ParticleColor;


void main()
{	
	PixelColor = texture( ParticleTexture, TexUV );
	PixelColor.a += ParticleColor.a;
}