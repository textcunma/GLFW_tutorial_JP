#include"VBO.h"

// コンストラクタ
VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
	// VBOを作成, 有効化
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);

	// VBOに頂点データを格納
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);	// VBOを有効化
}

void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);	// VBOを無効化
}

void VBO::Delete() {
	glDeleteBuffers(1, &ID);	// VBOを削除
}