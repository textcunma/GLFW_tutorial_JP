#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"

class Camera {
public:
	// �J�����ʒu
	glm::vec3 Position;

	// �J�����̎����x�N�g��(���K����)
	glm::vec3 Orientation = glm::vec3(0.0f, -1.0f, -1.0f);

	// �����(���K���ς�)
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);	// y������

	// �ϊ��s�񏉊���
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	bool firstClick = true;		// �J��������t���O
	int width;				// �\����ʕ�
	int height;				// �\����ʍ���
	float speed = 0.1f;			// �ω����x
	float sensitivity = 100.0f;	// �J�������x

	// �R���X�g���N�^
	Camera(int width, int height, glm::vec3 position);

	// �ϊ��s��X�V
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	
	// �ϊ��s���uniform�ϐ��ɑ��
	void Matrix(Shader& shader, const char* uniform);

	// �J��������
	void Inputs(GLFWwindow* window);
};

#endif