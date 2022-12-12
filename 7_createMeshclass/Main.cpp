#include"Mesh.h"

// ���_���
Vertex vertices[] = {
	// ���W���, �F���, �e�N�X�`�����W, �@��
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

// ���_�C���f�b�N�X
GLuint indices[] = {
	0, 1, 2,
	0, 2, 3
};

// �������_
Vertex lightVertices[] = {
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
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

	// �e�N�X�`��
	Texture textures[] {
		Texture("./7_createMeshclass/container2.png", \
				"diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("./7_createMeshclass/container2_specular.png", \
				"specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};

	// �V�F�[�_�[�t�@�C���ǂݍ���
	Shader shaderProgram("./7_createMeshclass/default.vert", "./7_createMeshclass/default.frag");

	// ���_,�C���f�b�N�X,�e�N�X�`�����W�̃x�N�g�����쐬
	std::vector <Vertex> verts(vertices, \
		vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, \
		indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, \
		textures + sizeof(textures) / sizeof(Texture));

	// �ufloor�v�Ƃ���Mesh�I�u�W�F�N�g���쐬
	Mesh floor(verts, ind, tex);

	// ���Ɋւ���V�F�[�_�[�ǂݍ���
	Shader lightShader("./7_createMeshclass/light.vert", "./7_createMeshclass/light.frag");

	// �������_, �����C���f�b�N�X�̃x�N�g�����쐬
	std::vector <Vertex> lightVerts(lightVertices, \
		lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, \
		lightIndices + sizeof(lightIndices) / sizeof(GLuint));

	// �ulight�v�Ƃ���Mesh�I�u�W�F�N�g���쐬
	Mesh light(lightVerts, lightInd, tex);

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

	// unifrom�ϐ��ɒl��n��
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), \
		1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), \
		lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	
	// �V�F�[�_�[�L����
	shaderProgram.Activate();

	// unifrom�ϐ��ɒl��n��
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), \
		1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), \
		lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), \
		lightPos.x, lightPos.y, lightPos.z);

	// �f�v�X�e�X�g�̗L����
	glEnable(GL_DEPTH_TEST);

	// ��ʂ̍X�V�p�x�ݒ�(1�b�ɂ�1��X�V)
	glfwSwapInterval(1);

	// �J�����ݒ�
	Camera camera(width, height, glm::vec3(0.0f, 2.0f, 2.0f));

	// ���C�����[�v
	while (!glfwWindowShouldClose(window)) {
		// �w�i�F�w��	
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// ��ʂ�������(�F�o�b�t�@, �f�v�X�o�b�t�@��������)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// �J�����������
		camera.Inputs(window);

		// �ϊ��s��쐬
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// ��ʑ�, ������`��
		floor.Draw(shaderProgram, camera);
		light.Draw(lightShader, camera);

		// �V�F�[�_�v���O�����̖�����
		glUseProgram(0);

		// ��ʂ��X�V
		glfwSwapBuffers(window);

		// ���[�U�[����̓��̓C�x���g������
		glfwPollEvents();
	}

	// �V�F�[�_�[�v���O�������폜
	shaderProgram.Delete();
	lightShader.Delete();

	// �E�B���h�E�̏���
	glfwDestroyWindow(window);

	// GLFW�̏I������
	glfwTerminate();
	return 0;
}