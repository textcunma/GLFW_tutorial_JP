#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"VAO.h"
#include"EBO.h"
#include"VBO.h"
#include"Camera.h"
#include"Texture.h"
#include"shaderClass.h"

// ���_���
GLfloat vertices[] = {
	// ���W���				�F���				�@�@�e�N�X�`�����W		�@��
	-1.0f,	0.0f,	1.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,
	-1.0f,	0.0f,	-1.0f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	1.0f,	0.0f,
	1.0f,	0.0f,	-1.0f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	0.0f,	1.0f,	0.0f,
	1.0f,	0.0f,	1.0f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,	1.0f,	0.0f
};

// ���_�C���f�b�N�X
GLuint indices[] = {
	0, 1, 2,
	0, 2, 3
};

// �������_
GLfloat lightVertices[] = {
	-0.1f, -0.1f, 0.1f,
	-0.1f, -0.1f, -0.1f,
	0.1f, -0.1f, -0.1f,
	0.1f, -0.1f, 0.1f,
	-0.1f, 0.1f, 0.1f,
	-0.1f, 0.1f, -0.1f,
	0.1f, 0.1f, -0.1f,
	0.1f, 0.1f, 0.1f
};

// �������_�C���f�b�N�X
GLuint lightIndices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
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
	Shader shaderProgram("./6_createLight/default.vert", "./6_createLight/default.frag");
	
	// VAO���쐬, �L����
	VAO VAO1;
	VAO1.Bind();

	// VBO���쐬, �L����, ���_�f�[�^��ݒ�
	VBO VBO1(vertices, sizeof(vertices));

	// EBO���쐬, �L����, �C���f�b�N�X�f�[�^��ݒ�
	EBO EBO1(indices, sizeof(indices));

	// VBO��A�g(���_�ʒu, ���_�F, �e�N�X�`�����W, �@��)
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);					// ���_
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));	// �F
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));	// �e�N�X�`��
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));	// �@��

	// VAO, VBO, EBO�𖳌���
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// ���Ɋւ���V�F�[�_�[�ǂݍ���
	Shader lightShader("./6_createLight/light.vert", "./6_createLight/light.frag");

	// ���Ɋւ���VAO���쐬, �L����
	VAO lightVAO;
	lightVAO.Bind();

	// ���Ɋւ���VBO���쐬, �L����, ���_�f�[�^��ݒ�
	VBO lightVBO(lightVertices, sizeof(lightVertices));

	// ���Ɋւ���EBO���쐬, �L����, �C���f�b�N�X�f�[�^��ݒ�
	EBO lightEBO(lightIndices, sizeof(lightIndices));

	// ���Ɋւ���VBO��A�g(���_�ʒu)
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	
	// ���Ɋւ���VAO, VBO, EBO�𖳌���
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	// �����̐F�ƈʒu
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);

	// ���f���ϊ��s��(����)
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	// ��ʑ̂̈ʒu
	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);

	// ���f���ϊ��s��(��ʑ�)
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);

	// ���Ɋւ���V�F�[�_�[�L����
	lightShader.Activate();

	// unifrom�ϐ�(model)�Ƀ��f���ϊ��s���n��
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"),	// vert
		1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"),		// frag
		lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	// �V�F�[�_�[�L����
	shaderProgram.Activate();

	// unifrom�ϐ�(model)�Ƀ��f���ϊ��s���n��
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1,	// vert
		GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"),	// frag
		lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"),		// frag
		lightPos.x, lightPos.y, lightPos.z);

	// �g�U���˃}�b�v
	Texture tileTex("./6_createLight/container2.png", \
		GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
	tileTex.texUnit(shaderProgram, "tex0", 0);

	// �X�y�L�����[�}�b�v
	Texture tileSpec("./6_createLight/container2_specular.png", \
		GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
	tileSpec.texUnit(shaderProgram, "tex1", 1);

	// �f�v�X�e�X�g�̗L����
	glEnable(GL_DEPTH_TEST);

	// ��ʂ̍X�V�p�x�ݒ�(1�b�ɂ�1��X�V)
	glfwSwapInterval(1);

	// �J�����ݒ�
	Camera camera(width, height, glm::vec3(0.0f, 2.0f, 2.0f));

	// ���C�����[�v
	while (glfwWindowShouldClose(window) == GL_FALSE) {
		// �w�i�F�w��	
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// ��ʂ�������(�F�o�b�t�@, �f�v�X�o�b�t�@��������)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// �J�����������
		camera.Inputs(window);

		// �ϊ��s��쐬
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// �V�F�[�_�v���O�����̗L����
		shaderProgram.Activate();

		// uniform�ϐ�(camPos)�ɃJ�����ʒu���W����
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"),	// frag
			camera.Position.x, camera.Position.y, camera.Position.z);

		// uniform�ϐ�(camMatrix)�Ƀr���[�E���e�ϊ��̍����s�����
		camera.Matrix(shaderProgram, "camMatrix");

		// �e�N�X�`����L����
		tileTex.Bind();
		//tileSpec.Bind();

		// VAO��L����
		VAO1.Bind();

		// back�o�b�t�@�ɐ}�`��`��
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		// ���Ɋւ���V�F�[�_�[��L����
		lightShader.Activate();

		// uniform�ϐ�(camMatrix)�Ƀr���[�E���e�ϊ��̍����s�����
		camera.Matrix(lightShader, "camMatrix");

		// ���Ɋւ���VAO��L����
		lightVAO.Bind();

		// back�o�b�t�@�ɐ}�`��`��
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

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
	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	tileTex.Delete();
	tileSpec.Delete();
	shaderProgram.Delete();
	lightShader.Delete();

	// �E�B���h�E�̏���
	glfwDestroyWindow(window);

	// GLFW�̏I������
	glfwTerminate();
	return 0;
}