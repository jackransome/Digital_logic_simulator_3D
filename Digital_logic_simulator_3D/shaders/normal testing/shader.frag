#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec4 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 FragPos;  
layout(location = 3) in vec3 Normal;
layout(location = 4) in vec3 cameraPos;

layout(location = 0) out vec4 outColor;

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;


void main() {

    //outColor = fragColor + vec4(test, 1);// texture(texSampler, fragTexCoord);
	vec3 tex = texture(texSampler, fs_in.TexCoords).rgb;
	vec3 nnormal = normalize(tex * 2.0 - 1.0);   
	vec3 lightColor = vec3(1,1,1);
	vec3 lightPos = cameraPos;
	vec3 objectColor = vec3(fragColor.x, fragColor.y, fragColor.z);//vec3(0.2,0.4,1);

	// ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(nnormal);
    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

	// specular
    float specularStrength = 0.7;
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  

	vec3 result = (ambient + diffuse + specular) * objectColor;
    outColor = vec4(result, 1.0);
	//outColor = vec4(ambient + diffuse + specular, 1) * texture(texSampler, fragTexCoord);

}