#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glm/glm.hpp>
#include<glad/glad.h>
#include<vector>

// 頂点データ構造
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

class VBO {
public:
	// EBOのIDを格納する配列のポインタ
	GLuint ID;

	// コンストラクタ
	VBO(std::vector<Vertex>& vertices);

	void Bind();	// 有効化
	void Unbind();	// 無効化
	void Delete();	// 削除

};

#endif