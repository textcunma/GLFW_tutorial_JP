#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"VAO.h"
#include"EBO.h"
#include"VBO.h"
#include"shaderClass.h"

// ���_
GLfloat vertices[] = {
	// x���W	y���W						z���W
	-0.5f, 	-0.5f * float(sqrt(3)) / 3, 		0.0f,
	0.5f, 	-0.5f * float(sqrt(3)) / 3, 		0.0f,
	0.0f, 	0.5f * float(sqrt(3)) * 2 / 3, 	0.0f,
	-0.25f, 	0.5f * float(sqrt(3)) / 6, 		0.0f,
	0.25f, 	0.5f * float(sqrt(3)) / 6, 		0.0f,
	0.0f, 	-0.5f * float(sqrt(3)) / 3, 		0.0f
};

// �C���f�b�N�X
GLuint indices[] = {
	0, 3, 5,	// �O�p�`(����)
	3, 2, 4,	// �O�p�`(�E��)
	5, 4, 1	// �O�p�`(�㕔)
};

const unsigned int width = 800;    // �E�B���h�E��
const unsigned int height = 800;   // �E�B���h�E����

int main() {
     // GLFW������
	glfwInit();	

	// OpenGL �o�[�W����3.3�w��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// �R�A�v���t�@�C����ݒ�
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// �E�B���h�E����
	GLFWwindow* window = \
          glfwCreateWindow(width, height, "GLFW Tutorial", NULL, NULL);
	
	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

     // OpenGL���`�悷��E�B���h�E���w��
	glfwMakeContextCurrent(window);

	// GLAD�ǂݍ���
	gladLoadGL();

     // �E�B���h�E�J�n�ʒu���w��
	glViewport(0, 0, width, height);

	// �V�F�[�_�[�t�@�C���ǂݍ���
	Shader shaderProgram("default.vert", "default.frag");
	
	// VAO���쐬, �L����
	VAO VAO1;
	VAO1.Bind();

	// VBO���쐬, �L����, ���_�f�[�^��ݒ�
	VBO VBO1(vertices, sizeof(vertices));

	// EBO���쐬, �L����, �C���f�b�N�X�f�[�^��ݒ�
	EBO EBO1(indices, sizeof(indices));
	
	// VBO��A�g(location = 0)
	VAO1.LinkVBO(VBO1, 0);

	// VAO, VBO, EBO�𖳌���
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// ���C�����[�v
	while (glfwWindowShouldClose(window) == GL_FALSE) {
		// �w�i�F�w��	
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// ��ʂ�������(�F�o�b�t�@��������)
		glClear(GL_COLOR_BUFFER_BIT);

		// �V�F�[�_�v���O�����̗L����
		shaderProgram.Activate();

		// VAO��L����
		VAO1.Bind();

		// back�o�b�t�@�ɐ}�`��`��
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// �V�F�[�_�v���O�����̖�����
		glUseProgram(0);

		// ��ʂ��X�V
		glfwSwapBuffers(window);

		// ���[�U�[����̓��̓C�x���g������
		glfwPollEvents();
	}

	// VAO, VBO, EBO, �V�F�[�_�[�v���O�������폜
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// �E�B���h�E�̔j��
	glfwDestroyWindow(window);

	// GLFW�̏I������
	glfwTerminate();
	return 0;
}