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

uniform struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;
uniform bool existTexture;

// 平行光源
vec4 direcLight() {
	vec3 normal = normalize(Normal);								// 法線(正規化済み)
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));		// 光線(正規化済み)

	// 拡散光
	float diffuse = max(dot(normal, lightDirection), 0.0f);	

	// 鏡面反射光
	float specularLight = 0.50f;									// 鏡面反射光係数
	vec3 viewDirection = normalize(camPos - crntPos);				// 視線ベクトル
	vec3 reflectionDirection = reflect(-lightDirection, normal);	// 反射ベクトル
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32);
	float specular = specAmount * specularLight;

	// 環境光係数
	float ambient = 0.20f;
	
	// 最終色の計算
	return (texture(diffuse0, texCoord) * lightColor * (diffuse + ambient) + 
							texture(specular0, texCoord).r * specular) * lightColor;
}

// 点光源
vec4 pointLight() {
	vec3 normal = normalize(Normal);			// 法線(正規化済み)
	vec3 lightVec = lightPos - crntPos;			// 光線ベクトル
	vec3 lightDirection = normalize(lightVec);	// 光線(正規化済み)
	
	// 拡散光
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// 鏡面反射光
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);				// 視線ベクトル(正規化済み)
	vec3 reflectionDirection = reflect(-lightDirection, normal);	// 反射ベクトル(正規化済み)
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32);
	float specular = specAmount * specularLight;

	// 環境光係数
	float ambient = 0.20f;	

	// 光の強度
	float a = 0.05;	// 二次項の係数
	float b = 0.01; // 一次項の係数
	float dist = length(lightVec);
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	// 最終色の計算
	return (texture(diffuse0, texCoord) * lightColor * (diffuse * inten + ambient) +
						texture(specular0, texCoord).r * specular * inten ) * lightColor;
}

// スポットライト光源
vec4 spotLight() {
	vec3 normal = normalize(Normal);						// 法線(正規化済み)
	vec3 lightDirection = normalize(lightPos - crntPos);	// 光線(正規化済み)

	// 拡散光
	float diffuse = max(dot(normal, lightDirection), 0.0f);	
	
	// 鏡面反射光
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);				// 視線ベクトル(正規化済み)
	vec3 reflectionDirection = reflect(-lightDirection, normal);	// 反射ベクトル(正規化済み)
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	// 環境光係数
	float ambient = 0.20f;	

	// 光の強度
	float innerCone = 0.95f;	// 内側の円錐と光線との角度
	float outerCone = 0.90f;	// 外側の円錐と光線との角度
	vec3 spotDirection = vec3(0.0f, -1.0f, 0.0f);	// 点灯しているベクトル
	float theta = dot(spotDirection, -lightDirection);
	float epsilon   = innerCone - outerCone;
	float inten = clamp((theta - outerCone) / epsilon, 0.0f, 1.0f);	// 上限・下限を設定の上,計算

	// 最終色の計算
	return (texture(diffuse0, texCoord) * lightColor * (diffuse * inten + ambient) + 
						texture(specular0, texCoord).r * specular * inten) * lightColor;
}

vec4 NoTexture() {
	vec3 normal = normalize(Normal);								// 法線(正規化済み)
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));		// 光線(正規化済み)

	vec3 lightColor = vec3(lightColor[0], lightColor[1], lightColor[2]);

    // 環境光
    vec3 ambient = lightColor * material.ambient;
  	
    // 拡散光
	float diff = max(dot(normal, lightDirection), 0.0f);	
    vec3 diffuse = lightColor * (diff * material.diffuse);
    
    // 鏡面反射光
	vec3 viewDirection = normalize(camPos - crntPos);				// 視線ベクトル
	vec3 reflectionDirection = reflect(-lightDirection, normal);	// 反射ベクトル
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), material.shininess);
	vec3 specular = lightColor * specAmount * material.specular;
        
    return vec4(ambient + diffuse + specular, 1.0);
}

void main(){
	if (existTexture){
		FragColor = pointLight();
		// FragColor = spotLight();
		// FragColor = direcLight();
	} else {
		FragColor = NoTexture();
	}
}