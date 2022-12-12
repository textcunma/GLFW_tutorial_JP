#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>

#include"VAO.h"
#include"EBO.h"
#include"Camera.h"
#include"Texture.h"

class Mesh
{
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;
	
	// VAO���쐬
	VAO VAO;

	// �R���X�g���N�^
	Mesh(std::vector <Vertex>& vertices, 
		std::vector <GLuint>& indices, 
		std::vector <Texture>& textures);

	// ���b�V���`��֐�
	void Draw(Shader& shader, Camera& camera);
};
#endif
