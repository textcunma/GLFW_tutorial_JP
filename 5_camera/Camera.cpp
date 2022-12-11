#include"Camera.h"

// �R���X�g���N�^
Camera::Camera(int width, int height, glm::vec3 position) {
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

// �ϊ��s��쐬
void Camera::Matrix(float FOVdeg,			// ����p
				float nearPlane,		// �O���N���b�v��
				float farPlane,		// ����N���b�v��
				Shader& shader,
				const char* uniform) {

	// ������
	glm::mat4 view = glm::mat4(1.0f);		// �r���[�ϊ��s��
	glm::mat4 projection = glm::mat4(1.0f);	// ���e�ϊ��s��

	// �J�����ʒu �o��
	std::cout << "(" << Position.x << "," << \
		Position.y << "," << Position.z << ")" << std::endl;

	// �r���[�ϊ��s����쐬
	view = glm::lookAt(Position, Position + Orientation, Up);

	// ���e�ϊ��s����쐬
	projection = glm::perspective(glm::radians(FOVdeg), 
						(float)(width / height), nearPlane, farPlane);

	// uniform�ϐ�(camMatrix)�̃A�N�Z�X���邽�߂̃������ʒu���擾
	GLuint uniID = glGetUniformLocation(shader.ID, uniform);

	// uniform�ϐ�(camMatrix)�ɒl����
	glUniformMatrix4fv(uniID, 1, GL_FALSE, glm::value_ptr(projection * view));
}

// �J�����������
void Camera::Inputs(GLFWwindow* window) {
	// �O�i
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		Position += speed * Orientation;
	}
	// ��i
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		Position += speed * -Orientation;
	}
	// ���ړ�
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));	
	}
	// �E�ړ�
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Position += speed * glm::normalize(glm::cross(Orientation, Up));	
	}
	// ��ړ�
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		Position += speed * Up;
	}
	// ���ړ�
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		Position += speed * -Up;
	}
	//�@�ω����x��ύX
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		speed = 0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
		speed = 0.1f;
	}
	// ���N���b�N���������ꍇ
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		// �J�[�\�����B��
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);	

		if (firstClick) {
			// �J�[�\������ʒ����Ɉړ�
			glfwSetCursorPos(window, (width / 2), (height / 2));	
			firstClick = false;
		}

		// �J�[�\���̍��W���擾
		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// �J�[�\���̍��W����J�����̊p�x���v�Z
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;	// ���K���ω���
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		// x���̉�]���v�Z
		glm::vec3 newOrientation = glm::rotate(Orientation,
												glm::radians(-rotX),
												glm::normalize(glm::cross(Orientation, Up)));

		// x�������̉�]�ɐ�����������
		if (!((glm::angle(newOrientation, Up) <= glm::radians(5.0f)) or
			(glm::angle(newOrientation, -Up) <= glm::radians(5.0f)))) {
			Orientation = newOrientation;	// ���e�͈͊O�ł���Ζ߂�
		}

		// y���̉�]���v�Z
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		// �J�[�\������ʒ����Ɉړ�
		glfwSetCursorPos(window, (width / 2), (height / 2));				

	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		// �J�[�\�����B���Ȃ�
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
}