 #version 330 core              

layout(location = 0) in vec3 aPos;   
layout(location = 1) in vec2 aTexCoord; 
layout (location = 2) in vec3 aNormal;
//uniform mat4 transform;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 proMat;


out vec3 vertexcolor;      
out vec3 Normal;
out vec3 FragPos;  
out vec2 TexCoord;


void main(){                 

		gl_Position = proMat* viewMat*modelMat * (vec4(aPos.x, aPos.y, aPos.z, 1.0)+vec4(0.5,0.0,0.5,0));
		TexCoord = aTexCoord;
		FragPos = vec3(modelMat * vec4(aPos, 1.0));
		Normal=aNormal;
}