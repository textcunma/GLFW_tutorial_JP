#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO {
public:
	// VAOのIDを格納する配列のポインタ
	GLuint ID;

	// コンストラクタ
	VAO();

	// VBOを連携
	void LinkAttrib(VBO VBO,
		GLuint layout,			// location
		GLuint numComponents,	// 要素数
		GLenum type,			// データ型
		GLsizeiptr stride,		// 属性間のバイトオフセット
		void* offset);			// バッファの先頭のポインタ

	void Bind();		// 有効化
	void Unbind();		// 無効化
	void Delete();		// 削除
};
#endif