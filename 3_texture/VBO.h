#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO {
public:
	// EBO��ID���i�[����z��̃|�C���^
	GLuint ID;

	// �R���X�g���N�^
	VBO(GLfloat* vertices, GLsizeiptr size);

	void Bind();	// �L����
	void Unbind();	// ������
	void Delete();	// �폜
};

#endif
