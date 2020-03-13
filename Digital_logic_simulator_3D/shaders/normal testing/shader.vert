#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    //mat4 model;
    mat4 view;
    mat4 proj;
	vec3 cameraPos;
} ubo;

layout(binding=2,set=0)buffer TRANSFORM_DATA
{
  mat4 transform[500];
} objects;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inTexCoord;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 FragPos;  
layout(location = 3) out vec3 Normal;
layout(location = 4) out vec3 cameraPos;

out VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} vs_out;

layout(push_constant) uniform transformData
{
  int index;
} object;

out gl_PerVertex {
    vec4 gl_Position;
};

void main() {
    gl_Position = ubo.proj * ubo.view /** ubo.model*/ * objects.transform[object.index] * vec4(inPosition, 1.0);
    fragColor = inColor;
	FragPos = vec3(objects.transform[object.index] * vec4(inPosition, 1.0));
    Normal = mat3(transpose(inverse(objects.transform[object.index]))) * inNormal;;
	cameraPos = ubo.cameraPos;
    fragTexCoord = inTexCoord;

	vec3 tangent; 

	vec3 c1 = cross(Normal, vec3(0.0, 0.0, 1.0)); 
	vec3 c2 = cross(Normal, vec3(0.0, 1.0, 0.0)); 

	if ( length(c1) > length(c2) ) {
		tangent = c1;	
	}
	else {
		tangent = c2;	
	}

	tangent = normalize(tangent);

	vec3 bitangent = cross(tangent, Normal);

	mat3 normalMatrix = transpose(inverse(mat3(objects.transform[object.index])));
    vec3 T = normalize(normalMatrix * tangent);
    vec3 N = normalize(normalMatrix * Normal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
    mat3 TBN = transpose(mat3(T, B, N));    
    vs_out.TangentLightPos = TBN * cameraPos;
    vs_out.TangentViewPos  = TBN * cameraPos;
    vs_out.TangentFragPos  = TBN * vs_out.FragPos;
}