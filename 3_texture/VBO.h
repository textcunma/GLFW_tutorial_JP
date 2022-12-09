#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO {
public:
	// EBOのIDを格納する配列のポインタ
	GLuint ID;

	// コンストラクタ
	VBO(GLfloat* vertices, GLsizeiptr size);

	void Bind();	// 有効化
	void Unbind();	// 無効化
	void Delete();	// 削除
};

#endif
