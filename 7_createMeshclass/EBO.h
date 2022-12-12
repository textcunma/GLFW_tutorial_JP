#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>
#include<vector>

class EBO {
public:
	// EBO��ID���i�[����z��̃|�C���^
	GLuint ID;
	
	// �R���X�g���N�^
	EBO(std::vector<GLuint>& indices);

	void Bind();	// �L����
	void Unbind();	// ������
	void Delete();	// �폜

};

#endif

