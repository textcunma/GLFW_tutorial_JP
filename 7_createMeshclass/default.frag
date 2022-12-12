#version 330 core

out vec4 FragColor;

in vec3 crntPos;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

// ���s����
vec4 direcLight() {
	vec3 normal = normalize(Normal);								// �@��(���K���ς�)
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));		// ����(���K���ς�)

	// �g�U��
	float diffuse = max(dot(normal, lightDirection), 0.0f);	

	// ���ʔ��ˌ�
	float specularLight = 0.50f;									// ���ʔ��ˌ��W��
	vec3 viewDirection = normalize(camPos - crntPos);				// �����x�N�g��
	vec3 reflectionDirection = reflect(-lightDirection, normal);	// ���˃x�N�g��
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32);
	float specular = specAmount * specularLight;

	// �����W��
	float ambient = 0.20f;
	
	// �ŏI�F�̌v�Z
	return (texture(diffuse0, texCoord) * lightColor * (diffuse + ambient) + 
							texture(specular0, texCoord).r * specular) * lightColor;
}

// �_����
vec4 pointLight() {
	vec3 normal = normalize(Normal);			// �@��(���K���ς�)
	vec3 lightVec = lightPos - crntPos;			// �����x�N�g��
	vec3 lightDirection = normalize(lightVec);	// ����(���K���ς�)
	
	// �g�U��
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// ���ʔ��ˌ�
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);				// �����x�N�g��(���K���ς�)
	vec3 reflectionDirection = reflect(-lightDirection, normal);	// ���˃x�N�g��(���K���ς�)
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32);
	float specular = specAmount * specularLight;

	// �����W��
	float ambient = 0.20f;	

	// ���̋��x
	float a = 0.05;	// �񎟍��̌W��
	float b = 0.01; // �ꎟ���̌W��
	float dist = length(lightVec);
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	// �ŏI�F�̌v�Z
	return (texture(diffuse0, texCoord) * lightColor * (diffuse * inten + ambient) +
						texture(specular0, texCoord).r * specular * inten ) * lightColor;
}

// �X�|�b�g���C�g����
vec4 spotLight() {
	vec3 normal = normalize(Normal);						// �@��(���K���ς�)
	vec3 lightDirection = normalize(lightPos - crntPos);	// ����(���K���ς�)

	// �g�U��
	float diffuse = max(dot(normal, lightDirection), 0.0f);	
	
	// ���ʔ��ˌ�
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);				// �����x�N�g��(���K���ς�)
	vec3 reflectionDirection = reflect(-lightDirection, normal);	// ���˃x�N�g��(���K���ς�)
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	// �����W��
	float ambient = 0.20f;	

	// ���̋��x
	float innerCone = 0.95f;	// �����̉~���ƌ����Ƃ̊p�x
	float outerCone = 0.90f;	// �O���̉~���ƌ����Ƃ̊p�x
	vec3 spotDirection = vec3(0.0f, -1.0f, 0.0f);	// �_�����Ă���x�N�g��
	float theta = dot(spotDirection, -lightDirection);
	float epsilon   = innerCone - outerCone;
	float inten = clamp((theta - outerCone) / epsilon, 0.0f, 1.0f);	// ����E������ݒ�̏�,�v�Z

	// �ŏI�F�̌v�Z
	return (texture(diffuse0, texCoord) * lightColor * (diffuse * inten + ambient) + 
						texture(specular0, texCoord).r * specular * inten) * lightColor;
}

void main(){
	// FragColor = direcLight();
	FragColor = pointLight();
	// FragColor = spotLight();
}