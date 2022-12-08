#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO {
public:
	// 
	GLuint ID;

	// コンストラクタ
	EBO(GLuint* indices, GLsizeiptr size);

	void Bind();	// 有効化
	void Unbind();	// 無効化
	void Delete();	// 削除

};

#endif

