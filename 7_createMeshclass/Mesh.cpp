#include "Mesh.h"

// コンストラクタ
Mesh::Mesh(std::vector <Vertex>& vertices, 
			std::vector <GLuint>& indices, 
			std::vector <Texture>& textures) {

	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	// VAOを有効化
	VAO.Bind();
	
	// VBOを作成, 有効化
	VBO VBO(vertices);
	
	// EBOを作成, 有効化
	EBO EBO(indices);

	// VBOを連携(頂点位置, 頂点色, テクスチャ座標, 法線)
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT,\
		sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT,\
		sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT,\
		sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT,\
		sizeof(Vertex), (void*)(9 * sizeof(float)));

	// VAO, VBO, EBOを無効化
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}

// メッシュ描画関数
void Mesh::Draw(Shader& shader, Camera& camera)
{
	// シェーダー, VAOを有効化
	shader.Activate();
	VAO.Bind();

	// テクスチャ数を追跡
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

		// uniform変数に代入(シェーダーにデータを渡す)
		textures[i].texUnit(shader, (type + num).c_str(), i);

		// テクスチャを有効化
		textures[i].Bind();
	}

	// uniform変数(camPos)にカメラ座標を渡す
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), \
		camera.Position.x, camera.Position.y, camera.Position.z);

	// uniform変数(camMatrix)に変換行列を渡す
	camera.Matrix(shader, "camMatrix");

	// backバッファに図形を描画
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}