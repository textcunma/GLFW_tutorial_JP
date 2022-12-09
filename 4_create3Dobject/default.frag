#version 330 core	// GLSLバージョン指定(version 3.30)
out vec4 FragColor;
/* out vec4 FragColor
	「out」を用いて出力のattribute変数を設定
	vec4はRGBAを表現
*/

in vec3 color;
in vec2 texCoord;
/*
	in vec3 color
	必ず頂点シェーダで指定した「out」と同じ名前にしないといけない
*/

uniform sampler2D tex0;

void main(){
	FragColor = texture(tex0, texCoord);
}