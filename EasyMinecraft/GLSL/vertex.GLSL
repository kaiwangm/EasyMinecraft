 #version 330 core              

layout(location = 0) in vec3 aPos;   
layout(location = 1) in vec3 acolor; 
layout(location = 2) in vec2 aTexCoord; 

//uniform mat4 transform;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 proMat;

out vec3 vertexcolor;      
out vec2 TexCoord;
void main(){                 

		gl_Position = proMat* viewMat*modelMat * vec4(aPos.x, aPos.y, aPos.z, 1.0);
		vertexcolor = acolor; 
		TexCoord = aTexCoord;
}