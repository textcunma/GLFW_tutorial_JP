#version 330 core	// GLSL�o�[�W�����w��(version 3.30)
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
/* layout (location = ����)
	����attribute�ϐ����f�[�^�����o�����_�o�b�t�@�̃C���f�b�N�X���w��
*/

/* attribute�ϐ�
	���_�����Ɋւ���f�[�^���V�F�[�_�ɑ��邽�߂̕ϐ�

*/

/* in vec3 aPos
	�uin�v��p���ē��͂�attribute�ϐ���ݒ�
	vec3�͂��ꂼ��x���W,y���W,z���W��\��
*/

out vec3 color;
out vec2 texCoord;
/* out vec3 color
	�uout�v��p���ďo�͂�attribute�ϐ���ݒ�
	vec3��RGB��\��
*/

uniform float scale;
/* uniform�ϐ�
	���_�����ȊO�̔ėp�I�ȃf�[�^���V�F�[�_�ɑ��邽�߂̕ϐ�
*/

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main(){
	gl_Position = proj * view * model * vec4(aPos, 1.0);	// �ϊ��s����t�̏��Ԃ��炩����Ƃ��낪�|�C���g
	color = aColor;
	texCoord = aTex;
}