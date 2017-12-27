#version 330 core

in vec3 FragPos;
in vec2 TextCoord;
in vec3 FragNormal;

// ��Դ���Խṹ��
struct LightAttr
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;	// ˥������
	float linear;   // ˥��һ��ϵ��
	float quadratic; // ˥������ϵ��
};

uniform LightAttr light;
uniform LightAttr light1;
uniform int lighton;
uniform vec3 viewPos;
uniform sampler2D texture_diffuse0;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_specular0;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

out vec4 color;

void main()
{
	// ������ɷ�
	vec3	ambient = light.ambient * vec3(texture(texture_diffuse0, TextCoord));

	// �������ɷ� ��ʱ��Ҫ���߷���Ϊָ���Դ
	vec3	lightDir = normalize(light.position - FragPos);
	vec3	normal = normalize(FragNormal);
	float	diffFactor = max(dot(lightDir, normal), 0.0);
	vec3	diffuse = diffFactor * light.diffuse * vec3(texture(texture_diffuse0, TextCoord));

	// ���淴��ɷ� ��ʱ��Ҫ���߷���Ϊ�ɹ�Դָ��
	float	specularStrength = 0.5f;
	vec3	reflectDir = normalize(reflect(-lightDir, normal));
	vec3	viewDir = normalize(viewPos - FragPos);
	float	specFactor = pow(max(dot(reflectDir, viewDir), 0.0), 64.0f);
	vec3	specular = specFactor * light.specular * vec3(texture(texture_specular0, TextCoord));

	// �������ɷ� ��ʱ��Ҫ���߷���Ϊָ���Դ
	vec3	lightDir1 = normalize(light1.position - FragPos);
	vec3	normal1 = normalize(FragNormal);
	float	diffFactor1 = max(dot(lightDir1, normal1), 0.0);
	vec3	diffuse1 = diffFactor1 * light1.diffuse * vec3(texture(texture_diffuse0, TextCoord));

	// ���淴��ɷ� ��ʱ��Ҫ���߷���Ϊ�ɹ�Դָ��
	float	specularStrength1 = 0.5f;
	vec3	reflectDir1 = normalize(reflect(-lightDir1, normal1));
	vec3	viewDir1 = normalize(viewPos - FragPos);
	float	specFactor1 = pow(max(dot(reflectDir1, viewDir1), 0.0), 64.0f);
	vec3	specular1 = specFactor1 * light1.specular * vec3(texture(texture_specular0, TextCoord));

	// ����˥������
	float distance = length(light.position - FragPos); // ����������ϵ�м������
	float attenuation = 1.0f / (light.constant 
			+ light.linear * distance
			+ light.quadratic * distance * distance);

	vec3	result = (ambient + diffuse + specular + diffuse1*lighton + specular1*lighton) * attenuation;
	color	= vec4(result , 1.0f);
}