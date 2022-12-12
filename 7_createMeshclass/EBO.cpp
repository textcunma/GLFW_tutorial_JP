#include"EBO.h"

// コンストラクタ
EBO::EBO(std::vector<GLuint>& indices) {
	// EBOを生成, 有効化
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

	// EBOに頂点インデックスを格納
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

// 有効化
void EBO::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// 無効化
void EBO::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// 削除
void EBO::Delete() {
	glDeleteBuffers(1, &ID);
}