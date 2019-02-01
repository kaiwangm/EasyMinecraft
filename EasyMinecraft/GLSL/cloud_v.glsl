#version 330 core
layout (location = 0) in vec3 aPos; 

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 proMat;

out vec4 vertexColor; 

void main()
{
	gl_Position = proMat* viewMat*modelMat * (vec4(aPos.x, aPos.y, aPos.z, 1.0));
    vertexColor = vec4(0.8, 0.8, 0.9, 0.2); 
}