#include"VBO.h"

// �R���X�g���N�^
VBO::VBO(std::vector<Vertex>& vertices) {
	// VBO���쐬, �L����
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);

	// VBO�ɒ��_�f�[�^���i�[
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);	// VBO��L����
}

void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);	// VBO�𖳌���
}

void VBO::Delete() {
	glDeleteBuffers(1, &ID);	// VBO���폜
}