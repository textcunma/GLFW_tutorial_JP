#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include"VAO.h"
#include"EBO.h"
#include"VBO.h"
#include"Camera.h"
#include"Texture.h"
#include"shaderClass.h"

// ���_���
GLfloat vertices[] = {
	// ���W���			�F���				�e�N�X�`�����W
	-0.5f,	0.0f,  0.5f,	0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f,	0.0f, -0.5f,	0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f,	0.0f, -0.5f,	0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f,	0.0f,  0.5f,	0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f,	0.8f,  0.0f,	0.92f, 0.86f, 0.76f,	2.5f, 5.0f,
};

// ���_�C���f�b�N�X
GLuint indices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
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
	Shader shaderProgram("./5_camera/default.vert", "./5_camera/default.frag");

	// VAO���쐬, �L����
	VAO VAO1;
	VAO1.Bind();

	// VBO���쐬, �L����, ���_�f�[�^��ݒ�
	VBO VBO1(vertices, sizeof(vertices));

	// EBO���쐬, �L����, �C���f�b�N�X�f�[�^��ݒ�
	EBO EBO1(indices, sizeof(indices));

	// VBO��A�g(���_�ʒu, ���_�F, �e�N�X�`�����W)
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float),
		(void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float),
		(void*)(6 * sizeof(float)));

	// VAO, VBO, EBO�𖳌���
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// �e�N�X�`���ݒ�
	Texture Tex("./5_camera/human.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	// �f�v�X�e�X�g�̗L����
	glEnable(GL_DEPTH_TEST);

	// ��ʂ̍X�V�p�x�ݒ�(1�b�ɂ�1��X�V)
	glfwSwapInterval(1);

	// �J�����ݒ�(�J�����ʒu�w��)
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));	

	// ���C�����[�v
	while (glfwWindowShouldClose(window) == GL_FALSE) {
		// �w�i�F�w��	
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// ��ʂ�������(�F�o�b�t�@, �f�v�X�o�b�t�@��������)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// �V�F�[�_�v���O�����̗L����
		shaderProgram.Activate();

		// �J�����������
		camera.Inputs(window);

		// �ϊ��s��쐬
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		// �e�N�X�`����L����
		Tex.Bind();

		// VAO��L����
		VAO1.Bind();

		// back�o�b�t�@�ɐ}�`��`��
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		// �V�F�[�_�v���O�����̖�����
		glUseProgram(0);

		// ��ʂ��X�V
		glfwSwapBuffers(window);

		// ���[�U�[����̓��̓C�x���g������
		glfwPollEvents();
	}

	// VAO, VBO, EBO, �e�N�X�`��, �V�F�[�_�[�v���O�������폜
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	Tex.Delete();
	shaderProgram.Delete();

	// �E�B���h�E�̏���
	glfwDestroyWindow(window);

	// GLFW�̏I������
	glfwTerminate();
	return 0;
}