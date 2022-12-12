#include"EBO.h"

// コンストラクタ
EBO::EBO(GLuint* indices, GLsizeiptr size) {
	// EBOを生成, 有効化
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

	// EBOに頂点インデックスを格納
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);	// VBOを有効化
}

void EBO::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	// VBOを無効化
}

void EBO::Delete() {
	glDeleteBuffers(1, &ID);	// EBOを削除
}