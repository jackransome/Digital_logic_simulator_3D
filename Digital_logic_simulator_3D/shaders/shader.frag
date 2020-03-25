#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec4 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 FragPos;  
layout(location = 3) in vec3 Normal;
layout(location = 4) in vec3 cameraPos;

layout(location = 0) out vec4 outColor;

void main() {
	
    //outColor = fragColor + vec4(test, 1);// texture(texSampler, fragTexCoord);
	vec3 tex = texture(texSampler, fragTexCoord).rgb;
	vec3 lightColor = vec3(1,1,1);
	vec3 lightPos = cameraPos;
	vec4 text = texture(texSampler, fragTexCoord);
	//vec3 objectColor = vec3(text.x, text.y, text.z);
	vec3 objectColor = vec3(fragColor.x, fragColor.y, fragColor.z);//vec3(0.2,0.4,1);

	// ambient
    float ambientStrength = 0.7;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

	// specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
    if (diffuse == vec3(0,0,0)){
        specular = vec3(0,0,0);
    }

	vec3 result = (ambient + diffuse + specular) * objectColor;
    outColor = vec4(result, 1.0);
	//outColor = vec4(ambient + diffuse + specular, 1) * texture(texSampler, fragTexCoord);
}