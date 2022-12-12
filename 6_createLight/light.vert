#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 model;		// ���f���ϊ��s��(���[���h���W�n�̌����̈ʒu)
uniform mat4 camMatrix;	// �r���[�E���e�ϊ��s��

void main() {
	gl_Position = camMatrix * model * vec4(aPos, 1.0f);
}