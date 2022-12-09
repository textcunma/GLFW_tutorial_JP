#version 330 core	// GLSLバージョン指定(version 3.30)
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
/* layout (location = 整数)
	入力attribute変数がデータを取り出す頂点バッファのインデックスを指定
*/

/* attribute変数
	頂点属性に関するデータをシェーダに送るための変数

*/

/* in vec3 aPos
	「in」を用いて入力のattribute変数を設定
	vec3はそれぞれx座標,y座標,z座標を表現
*/

out vec3 color;
out vec2 texCoord;
/* out vec3 color
	「out」を用いて出力のattribute変数を設定
	vec3はRGBを表現
*/

uniform float scale;
/* uniform変数
	頂点属性以外の汎用的なデータをシェーダに送るための変数
*/

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main(){
	gl_Position = proj * view * model * vec4(aPos, 1.0);	// 変換行列を逆の順番からかけるところがポイント
	color = aColor;
	texCoord = aTex;
}