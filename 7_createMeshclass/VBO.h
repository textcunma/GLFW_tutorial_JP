#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glm/glm.hpp>
#include<glad/glad.h>
#include<vector>


// ���_�f�[�^�\��
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

class VBO {
public:
	// EBO��ID���i�[����z��̃|�C���^
	GLuint ID;

	// �R���X�g���N�^
	VBO(std::vector<Vertex>& vertices);

	void Bind();	// �L����
	void Unbind();	// ������
	void Delete();	// �폜

};

#endif