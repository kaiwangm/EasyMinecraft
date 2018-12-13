#version 330 core 
out vec4 FragColor;     


in vec4 vertexcolor;  
in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPos;
uniform vec3 direction;
uniform vec3 viewPos;
uniform vec4 ourcolor;   
uniform sampler2D ourTexture;
uniform sampler2D faceTexCoord;
uniform vec3 lightColor;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 proMat;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
uniform Material material;

void main() 
{ 
	
// 环境光
    vec3 ambient = lightColor * material.ambient;

    // 漫反射 
    vec3 norm = normalize(Normal);

    //vec3 lightDir = normalize(lightPos - FragPos);
	vec3 lightDir = normalize(-direction);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightColor * (diff * material.diffuse);

    // 镜面光
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = lightColor * (spec * material.specular);  

	float distance    = length(lightPos - FragPos);
	float attenuation = 1.0 / (1.0f + 0.009f * distance + 
                0.0032f * (distance * distance));

	//ambient  *= attenuation; 
	//diffuse  *= attenuation;
	//specular *= attenuation;

    vec3 result = ambient + diffuse + specular;

	vec4 texColor =texture(ourTexture, TexCoord);
	if(texColor.a < 0.1)
        discard;

	FragColor = vec4(result,1.0)*texColor;
}