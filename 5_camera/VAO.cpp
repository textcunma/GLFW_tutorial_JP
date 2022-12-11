#include"VAO.h"

// �R���X�g���N�^
VAO::VAO() {
	glGenVertexArrays(1, &ID);	//�@VAO���쐬
}

// VBO��A�g
void VAO::LinkAttrib(VBO VBO,
	GLuint layout,			// location
	GLuint numComponents,	// �v�f��
	GLenum type,			// �f�[�^�^
	GLsizeiptr stride,		// �����Ԃ̃o�C�g�I�t�Z�b�g
	void* offset) {		// �o�b�t�@�̐擪�̃|�C���^
	
	// VBO��L����
	VBO.Bind();

	// ���_���̊i�[�ꏊ�Ə������w��
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);

	// VBO�𖳌���
	VBO.Unbind();
}

void VAO::Bind() {
	glBindVertexArray(ID);	// VAO��L����
}

void VAO::Unbind() {
	glBindVertexArray(0);	// VAO�𖳌���
}

void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);	// VAO���폜
}