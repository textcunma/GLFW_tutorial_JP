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
	
	// VAOを作成
	VAO VAO;

	// コンストラクタ
	Mesh(std::vector <Vertex>& vertices, 
		std::vector <GLuint>& indices, 
		std::vector <Texture>& textures);

	// メッシュ描画関数
	void Draw(Shader& shader, Camera& camera);
};
#endif
