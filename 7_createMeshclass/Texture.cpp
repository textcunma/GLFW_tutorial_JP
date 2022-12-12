#include"Texture.h"

// �R���X�g���N�^
Texture::Texture(const char* image, 
				const char* texType, 
				GLuint slot, 
				GLenum format, 
				GLenum pixelType)
{
	// �e�N�X�`���̎�ނ��N���X�S�̂ŗ��p�\�ɂ���
	type = texType;

	// �e�N�X�`����ǂݍ���
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);	// �������]
	unsigned char* bytes = stbi_load(
							image,
							&widthImg,
							&heightImg,
							&numColCh,
							0);

	// �e�N�X�`�����쐬
	glGenTextures(1, &ID);

	// �e�N�X�`���̃X���b�g�����w��
	glActiveTexture(GL_TEXTURE0 + slot);

	// �X���b�g�ԍ����N���X�S�̂ŗ��p�\�ɂ���
	unit = slot;

	// �e�N�X�`����L����
	glBindTexture(GL_TEXTURE_2D, ID);

	// �e�N�X�`���̕�ԕ��@(GL_NEAREST: �ŋߖT�@)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// �e�N�X�`�����W�O�̃e�N�X�`���̈��������w��(GL_REPEAT: �J��Ԃ�)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// GPU�Ƀe�N�X�`���f�[�^��n��
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	
	// �~�b�v�}�b�v��ݒ�
	glGenerateMipmap(GL_TEXTURE_2D);

	// �摜�̔j��
	stbi_image_free(bytes);

	// �e�N�X�`���̖�����
	glBindTexture(GL_TEXTURE_2D, 0);
}

// uniform�ϐ��ɑ��(�V�F�[�_�[�Ƀf�[�^��n��)
void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
	// uniform�ϐ��̎��ʎq�𓾂�
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);

	// �V�F�[�_�[�v���O������L����
	shader.Activate();

	// �V�F�[�_�[�Ƀf�[�^��n��
	glUniform1i(texUni, unit);
}

// �L����
void Texture::Bind() {
	// �e�N�X�`�����j�b�g�؂�ւ�
	glActiveTexture(GL_TEXTURE0 + unit);

	// �e�N�X�`���̗L����
	glBindTexture(GL_TEXTURE_2D, ID);
}

// ������
void Texture::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

// �폜
void Texture::Delete() {
	glDeleteTextures(1, &ID);
}