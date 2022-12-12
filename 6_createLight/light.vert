#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 model;		// モデル変換行列(ワールド座標系の光源の位置)
uniform mat4 camMatrix;	// ビュー・投影変換行列

void main() {
	gl_Position = camMatrix * model * vec4(aPos, 1.0f);
}