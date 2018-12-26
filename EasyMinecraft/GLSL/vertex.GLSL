 #version 330 core              

layout(location = 0) in vec3 aPos;   
layout(location = 1) in vec2 aTexCoord; 
layout (location = 2) in vec3 aNormal;
layout (location = 4) in vec3 pos;

//uniform mat4 transform;
//uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 proMat;
uniform int iswater;
//uniform vec3 pos;

out vec3 vertexcolor;      
out vec3 Normal;
out vec3 FragPos;  
out vec2 TexCoord;

mat4 transorm(vec3 pos)
{
	mat4 model=mat4(1.0f);
	model[3][0]=pos.x;
	model[3][1]=pos.y;
	model[3][2]=pos.z;
	return model;
}

void main(){                 

	mat4 modelMat=transorm(pos);

	if(iswater==0){
			gl_Position = proMat* viewMat*modelMat * (vec4(aPos.x, aPos.y, aPos.z, 1.0)+vec4(0.5,0.0,0.5,0));
			TexCoord = aTexCoord;
			FragPos = vec3(modelMat * vec4(aPos, 1.0));
			Normal=aNormal;
	}

	else{
			gl_Position = proMat* viewMat*modelMat * (vec4(aPos.x, aPos.y, aPos.z, 1.0)+vec4(0.5,-0.2,0.5,0));
			TexCoord = aTexCoord;
			FragPos = vec3(modelMat * vec4(aPos, 1.0));
			Normal=aNormal;
	}
		
}