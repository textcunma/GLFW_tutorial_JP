#include"EBO.h"

// �R���X�g���N�^
EBO::EBO(GLuint* indices, GLsizeiptr size) {
	// EBO�𐶐�, �L����
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

	// EBO�ɒ��_�C���f�b�N�X���i�[
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);	// VBO��L����
}

void EBO::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	// VBO�𖳌���
}

void EBO::Delete() {
	glDeleteBuffers(1, &ID);	// VBO���폜
}