#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>
#include"shaderClass.h"

class Texture {
public:
	GLuint ID;		// �e�N�X�`����ID���i�[����z��̃|�C���^
	const char* type;	// �e�N�X�`���̎��(2D or 3D)
	GLuint unit;		// �X���b�g�ԍ�

	// �R���X�g���N�^
	Texture(const char* image, 
			const char* texType, // �e�N�X�`���̎��(2D or 3D)
			GLuint slot,		// �e�N�X�`�����j�b�g�ԍ�
			GLenum format,		// ���̓s�N�Z���f�[�^�̃t�H�[�}�b�g(GL_RGBA)�Ȃ�
			GLenum pixelType);	// �s�N�Z���f�[�^�̃f�[�^�^

	// uniform�ϐ��ɑ��(�V�F�[�_�[�Ƀf�[�^��n��)
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	
	void Bind();	// �L����
	void Unbind();	// ������
	void Delete();	// �폜
};

#endif