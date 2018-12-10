#version 330 core 
out vec4 FragColor;     

in vec4 vertexcolor;  
in vec2 TexCoord;


uniform vec4 ourcolor;   
uniform sampler2D ourTexture;
uniform sampler2D faceTexCoord;

void main() 
{ 
	FragColor = texture(ourTexture, TexCoord);
}