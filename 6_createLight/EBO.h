#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO {
public:
	// EBO��ID���i�[����z��̃|�C���^
	GLuint ID;

	// �R���X�g���N�^
	EBO(GLuint* indices, GLsizeiptr size);

	void Bind();	// �L����
	void Unbind();	// ������
	void Delete();	// �폜
};

#endif

