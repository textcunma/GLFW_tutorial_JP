#include"shaderClass.h"

// �V�F�[�_�[�t�@�C���̓ǂݍ���
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

// �R���X�g���N�^
Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	// �V�F�[�_�[�̃\�[�X�R�[�h���擾
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// string�^��char*�^�ɕϊ�
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// �V�F�[�_�[�I�u�W�F�N�g���쐬
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// �V�F�[�_�[�I�u�W�F�N�g�Ƀ\�[�X�R�[�h��ݒ�
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

	// �\�[�X�R�[�h���R���p�C��
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	// ��̃v���O�����I�u�W�F�N�g���쐬
	ID = glCreateProgram();

	// ���_�V�F�[�_�[�ƃt���O�����g�V�F�[�_�[������
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	// �v���O�����I�u�W�F�N�g�������N(���s�\�ȏ�Ԃɂ���)
	glLinkProgram(ID);

	// �s�v�ɂȂ����V�F�[�_�[���폜
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// �V�F�[�_�[�v���O������L����
void Shader::Activate() {
	glUseProgram(ID);
}

// �V�F�[�_�[�v���O�������폜
void Shader::Delete() {
	glDeleteProgram(ID);
}