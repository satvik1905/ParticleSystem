#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 TextureUV;


// Output data ; will be interpolated for each fragment.
out vec2 TexUV;

uniform mat4 matrixModelViewProj;

void main()
{
	gl_Position =  matrixModelViewProj * vec4(vertexPosition,1);
	TexUV = TextureUV;	
}

