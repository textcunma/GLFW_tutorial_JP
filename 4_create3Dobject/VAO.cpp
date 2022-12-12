#include"VAO.h"

// コンストラクタ
VAO::VAO() {
	glGenVertexArrays(1, &ID);	//　VAOを作成
}

// VBOを連携
void VAO::LinkAttrib(VBO VBO,
	GLuint layout,			// location
	GLuint numComponents,	// 要素数
	GLenum type,			// データ型
	GLsizeiptr stride,		// 属性間のバイトオフセット
	void* offset) {		// バッファの先頭のポインタ
// VBOを有効化
	VBO.Bind();

	// 頂点情報の格納場所と書式を指定
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
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