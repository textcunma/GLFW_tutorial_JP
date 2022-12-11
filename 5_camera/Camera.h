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
	// カメラ位置
	glm::vec3 Position;	// glm::vec3(0.0f, 0.0f, 2.0f)

	// カメラの視線ベクトル(正規化済)
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);

	// 上方向(正規化済み)
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);	// y軸が上

	bool firstClick = true;		// カメラ操作フラグ
	int width;				// 表示画面幅
	int height;				// 表示画面高さ
	float speed = 0.1f;			// 変化速度
	float sensitivity = 100.0f;	// カメラ感度
	
	// コンストラクタ
	Camera(int width, int height, glm::vec3 position);

	// 変換行列作成
	void Matrix(float FOVdeg,			// 視野角
				float nearPlane,		// 前方クリップ面
				float farPlane,		// 後方クリップ面
				Shader& shader, 
				const char* uniform);

	// カメラ操作
	void Inputs(GLFWwindow* window);
};

#endif