#version 330 core	// GLSL�o�[�W�����w��(version 3.30)
out vec4 FragColor;
/* out vec4 FragColor
	�uout�v��p���ďo�͂�attribute�ϐ���ݒ�
	vec4��RGBA��\��
*/

in vec3 color;
in vec2 texCoord;
/*
	in vec3 color
	�K�����_�V�F�[�_�Ŏw�肵���uout�v�Ɠ������O�ɂ��Ȃ��Ƃ����Ȃ�
*/

uniform sampler2D tex0;

void main(){
	FragColor = texture(tex0, texCoord);
}