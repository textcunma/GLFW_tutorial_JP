#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include<glad/glad.h>

// シェーダーファイル読み込み
std::string get_file_contents(const char* filename);

class Shader{
public:
	// シェーダープログラムの識別ID
	GLuint ID;

	// コンストラクタ
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate();	// 有効化
	void Delete();		// 無効化
};

#endif