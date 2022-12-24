#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 Normal;
in vec3 crntPos;	// ワールド座標系の被写体の位置

uniform vec3 lightColor;	// 光源色
uniform vec3 lightPos;		// 光源座標
uniform vec3 camPos;		// カメラ位置

uniform struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;
  

void main(){  
	vec3 normal = normalize(Normal);								// 法線(正規化済み)
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));		// 光線(正規化済み)

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
        
    FragColor = vec4(ambient + diffuse + specular, 1.0);
}