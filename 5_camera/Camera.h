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
	glm::vec3 Position;	// glm::vec3(0.0f, 0.0f, 2.0f)

	// �J�����̎����x�N�g��(���K����)
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);

	// �����(���K���ς�)
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);	// y������

	bool firstClick = true;		// �J��������t���O
	int width;				// �\����ʕ�
	int height;				// �\����ʍ���
	float speed = 0.1f;			// �ω����x
	float sensitivity = 100.0f;	// �J�������x
	
	// �R���X�g���N�^
	Camera(int width, int height, glm::vec3 position);

	// �ϊ��s��쐬
	void Matrix(float FOVdeg,			// ����p
				float nearPlane,		// �O���N���b�v��
				float farPlane,		// ����N���b�v��
				Shader& shader, 
				const char* uniform);

	// �J��������
	void Inputs(GLFWwindow* window);
};

#endif