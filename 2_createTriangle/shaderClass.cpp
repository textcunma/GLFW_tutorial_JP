#include"shaderClass.h"

// シェーダーファイルの読み込み
std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// コンストラクタ
Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	// シェーダーのソースコードを取得
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// string型をchar*型に変換
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// シェーダーオブジェクトを作成
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// シェーダーオブジェクトにソースコードを設定
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

	// ソースコードをコンパイル
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	// 空のプログラムオブジェクトを作成
	ID = glCreateProgram();

	// 頂点シェーダーとフラグメントシェーダーを結合
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	// プログラムオブジェクトをリンク(実行可能な状態にする)
	glLinkProgram(ID);

	// 不要になったシェーダーを削除
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// シェーダープログラムを有効化
void Shader::Activate() {
	glUseProgram(ID);
}

// シェーダープログラムを削除
void Shader::Delete() {
	glDeleteProgram(ID);
}