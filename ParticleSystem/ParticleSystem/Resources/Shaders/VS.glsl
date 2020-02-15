#version 330 core

//Input Vertex Shader
layout(location = 0) in vec3 vPosition; //Vertex Position
layout(location = 1) in vec2 vTexUV;		//Vertex Texture Coordinate


//Output Vertex Shader
out vec2 pTexUV;

uniform mat4 matrixModelViewProj;

void main()
{

	gl_Position =  matrixModelViewProj * vec4(vPosition, 1.0f);
	pTexUV = vTexUV;
}

