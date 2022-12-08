#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO {
public:
	// VBOのIDを格納する配列
	GLuint ID;

	// コンストラクタ
	VBO(GLfloat* vertoces, GLsizeiptr size);

	void Bind();	// 有効化
	void Unbind();	// 無効化
	void Delete();	// 削除

};

#endif
