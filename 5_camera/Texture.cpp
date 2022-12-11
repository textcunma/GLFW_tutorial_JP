#include"Texture.h"

// コンストラクタ
Texture::Texture(
	const char* image,
	GLenum texType,
	GLenum slot,
	GLenum format,
	GLenum pixelType) {

	// テクスチャの種類をクラス全体で利用可能にする
	type = texType;

	// テクスチャを読み込む
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);	// 垂直反転
	unsigned char* bytes = stbi_load(image,
		&widthImg,
		&heightImg,
		&numColCh,
		0);

	// テクスチャを作成
	glGenTextures(1, &ID);

	// テクスチャのスロット名を指定
	glActiveTexture(slot);

	// テクスチャを有効化
	glBindTexture(texType, ID);

	// テクスチャの補間方法(GL_NEAREST: 最近傍法)
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	// 縮小される場合
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	// 拡大される場合

	// テクスチャ座標外のテクスチャの扱い方を指定(GL_REPEAT: 繰り返し)
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);	// s軸(≒x軸)
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);	// t軸(≒y軸)

	// GPUにテクスチャデータを渡す
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);

	// ミップマップを設定
	glGenerateMipmap(texType);

	// 画像の破棄
	stbi_image_free(bytes);

	// テクスチャの無効化
	glBindTexture(texType, 0);
}

// uniform変数に代入(シェーダーにデータを渡す)
void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
	// uniform変数の識別子を得る
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);

	// シェーダープログラムを有効化
	shader.Activate();

	// シェーダーにデータを渡す
	glUniform1i(texUni, unit);
}

void Texture::Bind() {
	glBindTexture(type, ID);	// 有効化
}

void Texture::Unbind() {
	glBindTexture(type, 0);	// 無効化
}

void Texture::Delete() {
	glDeleteTextures(1, &ID);	// 削除
}