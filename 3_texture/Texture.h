#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>
#include"shaderClass.h"

class Texture {
public:
	GLuint ID;	// �e�N�X�`����ID���i�[����z��̃|�C���^
	GLenum type;	// �e�N�X�`���̎��(2D or 3D)

	// �R���X�g���N�^
	Texture(const char* image, 
			GLenum texType,	// �e�N�X�`���̎��(2D or 3D)
			GLenum slot,		// �e�N�X�`�����j�b�g�ԍ�
			GLenum format, 
			GLenum pixelType);

	// uniform�ϐ��ɑ��(�V�F�[�_�[�Ƀf�[�^��n��)
	void texUnit(Shader shader, const char* uniform, GLuint unit);
	
	void Bind();	// �L����
	void Unbind();	// ������
	void Delete();	// �폜
};

#endif