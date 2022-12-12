#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO {
public:
	// VAO��ID���i�[����z��̃|�C���^
	GLuint ID;

	// �R���X�g���N�^
	VAO();

	// VBO��A�g
	void LinkAttrib(VBO& VBO,
		GLuint layout,			// location
		GLuint numComponents,	// �v�f��
		GLenum type,			// �f�[�^�^
		GLsizeiptr stride,		// �����Ԃ̃o�C�g�I�t�Z�b�g
		void* offset);			// �o�b�t�@�̐擪�̃|�C���^

	void Bind();		// �L����
	void Unbind();		// ������
	void Delete();		// �폜
};
#endif