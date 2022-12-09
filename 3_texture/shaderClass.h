#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include<glad/glad.h>

// �V�F�[�_�[�t�@�C���ǂݍ���
std::string get_file_contents(const char* filename);

class Shader {
public:
	// �V�F�[�_�[�v���O�����̎���ID
	GLuint ID;

	// �R���X�g���N�^
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate();	// �L����
	void Delete();		// ������

private:
	void compileErrors(unsigned int shader, const char* type);
};
#endif