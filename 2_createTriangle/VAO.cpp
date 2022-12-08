#include"VAO.h"

// コンストラクタ
VAO::VAO() {
	glGenVertexArrays(1, &ID);	//　VAOを作成
}

// VBOを連携
void VAO::LinkVBO(VBO VBO, GLuint layout) {
	// VBOを有効化
	VBO.Bind();

	// 頂点情報の格納場所と書式を指定
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(layout);

	// VBOを無効化
	VBO.Unbind();
}

void VAO::Bind() {
	glBindVertexArray(ID);	// VAOを有効化
}

void VAO::Unbind() {
	glBindVertexArray(0);	// VAOを無効化
}

void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);	// VAOを削除
}