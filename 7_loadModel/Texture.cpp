#include"Texture.h"

// コンストラクタ
Texture::Texture(const char* image, 
				const char* texType, 
				GLuint slot, 
				GLenum format, 
				GLenum pixelType)
{	
	// テクスチャのファイルパスを保存
	path = image;

	// テクスチャの種類をクラス全体で利用可能にする
	type = texType;

	// テクスチャを読み込む
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);	// 垂直反転
	unsigned char* bytes = stbi_load(
							image,
							&widthImg,
							&heightImg,
							&numColCh,
							0);

	// テクスチャを作成
	glGenTextures(1, &ID);

	// テクスチャのスロット名を指定
	glActiveTexture(GL_TEXTURE0 + slot);

	// スロット番号をクラス全体で利用可能にする
	unit = slot;

	// テクスチャを有効化
	glBindTexture(GL_TEXTURE_2D, ID);

	// テクスチャの補間方法(GL_NEAREST: 最近傍法)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// テクスチャ座標外のテクスチャの扱い方を指定(GL_REPEAT: 繰り返し)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// GPUにテクスチャデータを渡す
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	
	// ミップマップを設定
	glGenerateMipmap(GL_TEXTURE_2D);

	// 画像の破棄
	stbi_image_free(bytes);

	// テクスチャの無効化
	glBindTexture(GL_TEXTURE_2D, 0);
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

// 有効化
void Texture::Bind() {
	// テクスチャユニット切り替え
	glActiveTexture(GL_TEXTURE0 + unit);

	// テクスチャの有効化
	glBindTexture(GL_TEXTURE_2D, ID);
}

// 無効化
void Texture::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

// 削除
void Texture::Delete() {
	glDeleteTextures(1, &ID);
}