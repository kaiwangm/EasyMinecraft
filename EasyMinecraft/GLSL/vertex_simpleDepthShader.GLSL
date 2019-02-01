#version 330 core
layout (location = 0) in vec3 position;
layout (location = 4) in vec3 pos;
uniform mat4 lightSpaceMatrix;

mat4 transorm(vec3 pos)
{
	mat4 model=mat4(1.0f);
	model[3][0]=pos.x;
	model[3][1]=pos.y;
	model[3][2]=pos.z;
	return model;
}

void main()
{
	mat4 model=transorm(pos);
    gl_Position = lightSpaceMatrix * model * (vec4(position, 1.0f));
}