#include"Camera.h"

// コンストラクタ
Camera::Camera(int width, int height, glm::vec3 position) {
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

// 変換行列作成
void Camera::Matrix(float FOVdeg,			// 視野角
				float nearPlane,		// 前方クリップ面
				float farPlane,		// 後方クリップ面
				Shader& shader,
				const char* uniform) {

	// 初期化
	glm::mat4 view = glm::mat4(1.0f);		// ビュー変換行列
	glm::mat4 projection = glm::mat4(1.0f);	// 投影変換行列

	// カメラ位置 出力
	std::cout << "(" << Position.x << "," << \
		Position.y << "," << Position.z << ")" << std::endl;

	// ビュー変換行列を作成
	view = glm::lookAt(Position, Position + Orientation, Up);

	// 投影変換行列を作成
	projection = glm::perspective(glm::radians(FOVdeg), 
						(float)(width / height), nearPlane, farPlane);

	// uniform変数(camMatrix)のアクセスするためのメモリ位置を取得
	GLuint uniID = glGetUniformLocation(shader.ID, uniform);

	// uniform変数(camMatrix)に値を代入
	glUniformMatrix4fv(uniID, 1, GL_FALSE, glm::value_ptr(projection * view));
}

// カメラ操作入力
void Camera::Inputs(GLFWwindow* window) {
	// 前進
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		Position += speed * Orientation;
	}
	// 後進
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		Position += speed * -Orientation;
	}
	// 左移動
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));	
	}
	// 右移動
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Position += speed * glm::normalize(glm::cross(Orientation, Up));	
	}
	// 上移動
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		Position += speed * Up;
	}
	// 下移動
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		Position += speed * -Up;
	}
	//　変化速度を変更
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		speed = 0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
		speed = 0.1f;
	}
	// 左クリックが押した場合
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		// カーソルを隠す
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);	

		if (firstClick) {
			// カーソルを画面中央に移動
			glfwSetCursorPos(window, (width / 2), (height / 2));	
			firstClick = false;
		}

		// カーソルの座標を取得
		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// カーソルの座標からカメラの角度を計算
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;	// 正規化変化量
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		// x軸の回転を計算
		glm::vec3 newOrientation = glm::rotate(Orientation,
												glm::radians(-rotX),
												glm::normalize(glm::cross(Orientation, Up)));

		// x軸方向の回転に制限をかける
		if (!((glm::angle(newOrientation, Up) <= glm::radians(5.0f)) or
			(glm::angle(newOrientation, -Up) <= glm::radians(5.0f)))) {
			Orientation = newOrientation;	// 許容範囲外であれば戻す
		}

		// y軸の回転を計算
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		// カーソルを画面中央に移動
		glfwSetCursorPos(window, (width / 2), (height / 2));				

	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		// カーソルを隠さない
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
}