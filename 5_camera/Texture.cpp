#include"Texture.h"

// �R���X�g���N�^
Texture::Texture(
	const char* image,
	GLenum texType,
	GLenum slot,
	GLenum format,
	GLenum pixelType) {

	// �e�N�X�`���̎�ނ��N���X�S�̂ŗ��p�\�ɂ���
	type = texType;

	// �e�N�X�`����ǂݍ���
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);	// �������]
	unsigned char* bytes = stbi_load(image,
		&widthImg,
		&heightImg,
		&numColCh,
		0);

	// �e�N�X�`�����쐬
	glGenTextures(1, &ID);

	// �e�N�X�`���̃X���b�g�����w��
	glActiveTexture(slot);

	// �e�N�X�`����L����
	glBindTexture(texType, ID);

	// �e�N�X�`���̕�ԕ��@(GL_NEAREST: �ŋߖT�@)
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	// �k�������ꍇ
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	// �g�傳���ꍇ

	// �e�N�X�`�����W�O�̃e�N�X�`���̈��������w��(GL_REPEAT: �J��Ԃ�)
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);	// s��(��x��)
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);	// t��(��y��)

	// GPU�Ƀe�N�X�`���f�[�^��n��
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);

	// �~�b�v�}�b�v��ݒ�
	glGenerateMipmap(texType);

	// �摜�̔j��
	stbi_image_free(bytes);

	// �e�N�X�`���̖�����
	glBindTexture(texType, 0);
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

void Texture::Bind() {
	glBindTexture(type, ID);	// �L����
}

void Texture::Unbind() {
	glBindTexture(type, 0);	// ������
}

void Texture::Delete() {
	glDeleteTextures(1, &ID);	// �폜
}