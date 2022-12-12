#include "Mesh.h"

// �R���X�g���N�^
Mesh::Mesh(std::vector <Vertex>& vertices, 
			std::vector <GLuint>& indices, 
			std::vector <Texture>& textures) {

	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	// VAO��L����
	VAO.Bind();
	
	// VBO���쐬, �L����
	VBO VBO(vertices);
	
	// EBO���쐬, �L����
	EBO EBO(indices);

	// VBO��A�g(���_�ʒu, ���_�F, �e�N�X�`�����W, �@��)
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT,\
		sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT,\
		sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT,\
		sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT,\
		sizeof(Vertex), (void*)(9 * sizeof(float)));

	// VAO, VBO, EBO�𖳌���
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}

// ���b�V���`��֐�
void Mesh::Draw(Shader& shader, Camera& camera)
{
	// �V�F�[�_�[, VAO��L����
	shader.Activate();
	VAO.Bind();

	// �e�N�X�`������ǐ�
	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	for (unsigned int i = 0; i < textures.size(); i++) {
		std::string num;
		std::string type = textures[i].type;
		if (type == "diffuse") {
			num = std::to_string(numDiffuse++);
		}
		else if (type == "specular") {
			num = std::to_string(numSpecular++);
		}

		// uniform�ϐ��ɑ��(�V�F�[�_�[�Ƀf�[�^��n��)
		textures[i].texUnit(shader, (type + num).c_str(), i);

		// �e�N�X�`����L����
		textures[i].Bind();
	}

	// uniform�ϐ�(camPos)�ɃJ�������W��n��
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), \
		camera.Position.x, camera.Position.y, camera.Position.z);

	// uniform�ϐ�(camMatrix)�ɕϊ��s���n��
	camera.Matrix(shader, "camMatrix");

	// back�o�b�t�@�ɐ}�`��`��
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}