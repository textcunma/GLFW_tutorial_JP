#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO {
public:
	// VAOのIDを格納する配列
	GLuint ID;

	// コンストラクタ
	VAO();

	void LinkVBO(VBO VBO, GLuint layout);	// VBOを連携
	void Bind();						// 有効化
	void Unbind();						// 無効化
	void Delete();						// 削除
};

#endif