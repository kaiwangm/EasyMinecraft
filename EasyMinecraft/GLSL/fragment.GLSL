#version 330 core 
out vec4 FragColor;     


in vec4 vertexcolor;  
in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;
in vec4 FragPosLightSpace;

uniform vec3 lightPos;
uniform vec3 direction;
uniform vec3 viewPos;
uniform vec4 ourcolor;   
uniform sampler2D ourTexture;
uniform samplerCube sky;

uniform sampler2D faceTexCoord;
uniform sampler2D shadowMap;

uniform vec3 lightColor;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 proMat;
uniform int iswater;
uniform float time;


struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
uniform Material material;

float ShadowCalculation (vec4 fragPosLightSpace) {
    //归一化坐标
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    //转换到[0,1]范围
    projCoords = projCoords * 0.5 + 0.5;
    //采样最近点
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    //当前的深度
    float currentDepth = projCoords.z;

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - 0.005 > pcfDepth ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;

    //比较当前深度和最近采样点深度
    //float shadow = (currentDepth - 0.005) > closestDepth? 1.0 : 0.0;
    //超出深度图区域的修正
    if (projCoords.z > 1.0)
        shadow = 0.0;

    return shadow;
}


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


	float shadow = ShadowCalculation(FragPosLightSpace);   
    vec3 result = (ambient + (1.0 - shadow) * (diffuse + specular));
   //vec3 result=vec3(shadow);
	vec4 texColor =texture(ourTexture, TexCoord);
	if(texColor.a < 0.1)
        discard;


	if(iswater==0){
			FragColor = vec4(result,1.0)*texColor;
	}
	else{
		if(dot(Normal,vec3(0,1,0))<0.5)
		{
			discard;
		}
		vec3 I = normalize(FragPos - viewPos);
		vec3 R = reflect(I, normalize(Normal));
		FragColor = (1-shadow)*vec4(texture(sky, R).rgb, 1.0)-vec4(0,0,0,0.5);
	}

}
	
