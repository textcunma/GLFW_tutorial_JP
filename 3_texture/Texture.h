#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>
#include"shaderClass.h"

class Texture {
public:
	GLuint ID;	// テクスチャのIDを格納する配列のポインタ
	GLenum type;	// テクスチャの種類(2D or 3D)

	// コンストラクタ
	Texture(const char* image, 
			GLenum texType,	// テクスチャの種類(2D or 3D)
			GLenum slot,		// テクスチャユニット番号
			GLenum format, 
			GLenum pixelType);

	// uniform変数に代入(シェーダーにデータを渡す)
	void texUnit(Shader shader, const char* uniform, GLuint unit);
	
	void Bind();	// 有効化
	void Unbind();	// 無効化
	void Delete();	// 削除
};

#endif