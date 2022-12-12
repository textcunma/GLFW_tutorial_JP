#include"EBO.h"

// �R���X�g���N�^
EBO::EBO(std::vector<GLuint>& indices) {
	// EBO�𐶐�, �L����
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

	// EBO�ɒ��_�C���f�b�N�X���i�[
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

// �L����
void EBO::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// ������
void EBO::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// �폜
void EBO::Delete() {
	glDeleteBuffers(1, &ID);
}