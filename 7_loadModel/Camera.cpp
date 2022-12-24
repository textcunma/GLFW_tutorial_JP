#include"Camera.h"

// コンストラクタ
Camera::Camera(int width, int height, glm::vec3 position) {
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

// 変換行列更新
void Camera::updateMatrix(float FOVdeg,
	float nearPlane,
	float farPlane) {

	// 変換行列初期化
	glm::mat4 view = glm::mat4(1.0f);		// ビュー変換行列
	glm::mat4 projection = glm::mat4(1.0f);	// 投影変換行列

	// ビュー変換行列を作成
	view = glm::lookAt(Position, Position + Orientation, Up);

	// 投影変換行列を作成
	projection = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

	// 変換行列合成
	cameraMatrix = projection * view;
}

// 変換行列をuniform変数に代入
void Camera::Matrix(Shader& shader, const char* uniform) {
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::LeftClick(GLFWwindow* window) {
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

// マウスホイールを押した場合
void Camera::MiddleClick(GLFWwindow* window) {
	// カーソルの座標を取得
	currentTime = glfwGetTime();
	if (firstClick) {
		glfwGetCursorPos(window, &start_mouseX, &start_mouseY);
		firstClick = false;
		return;
	}

	// 30frameに1回更新
	if (currentTime - lastTime > 1.0 / 30.0) {
		double end_mouseX;
		double end_mouseY;
		glfwGetCursorPos(window, &end_mouseX, &end_mouseY);

		// マウス移動変位(相対量)
		double dx = (end_mouseX - start_mouseX) / width;
		double dy = (end_mouseY - start_mouseY) / height;

		// マウス移動量(相対量)
		double r = sqrt(dx * dx + dy * dy);

		if (r != 0.0) {
			// 回転角を計算
			double half_radian = r * glm::pi<float>();

			// 回転軸を計算
			double axis_x = dy / r;
			double axis_y = dx / r;
			double axis_z = 0.0;

			// z軸を中心とした回転を表すクォータニオンなため、0.0
			double r_sin = sin(half_radian);
			glm::quat q = glm::quat(cos(half_radian), axis_x * r_sin, axis_y * r_sin, axis_z * r_sin);

			// 位置・向き・上ベクトルをクォータニオンで更新
			Position = q * Position;
			Orientation = q * Orientation;
			Up = q * Up;

			// マウス位置を更新
			start_mouseX = end_mouseX;
			start_mouseY = end_mouseY;
		}

		lastTime = currentTime;
	}
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
		LeftClick(window);
	}
	// マウスホイールを押した場合
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
		MiddleClick(window);
	}
	else {
		// カーソルを隠さない
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
}