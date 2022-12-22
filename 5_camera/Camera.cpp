#include"Camera.h"

// コンストラクタ
Camera::Camera(int width, int height, glm::vec3 position) {
	Camera::width = width;
	Camera::height = height;
	Position = position;
	start_mouseX = 1.0 / width;
	start_mouseY = 1.0 / height;
	glfwSetTime(0.0);
	currentTime = 0.0f;
	lastTime = glfwGetTime();
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
	#ifndef DEBUG
		//std::cout << glm::to_string(Position) << std::endl;
	#endif

	// ビュー変換行列を生成
	view = glm::lookAt(Position, Position + Orientation, Up);
	
	// 投影変換行列を作成
	projection = glm::perspective(glm::radians(FOVdeg),
		(float)(width / height), nearPlane, farPlane);

	// uniform変数(camMatrix)のアクセスするためのメモリ位置を取得
	GLuint uniID = glGetUniformLocation(shader.ID, uniform);

	// uniform変数(camMatrix)に値を代入
	glUniformMatrix4fv(uniID, 1, GL_FALSE, glm::value_ptr(projection * view));
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
	if (!firstClick) {
		glfwGetCursorPos(window, &start_mouseX, &start_mouseY);
	}
	
	// 30frameに1回更新
	if (currentTime - lastTime > 1.0 / 30.0) {
		double end_mouseX;
		double end_mouseY;
		glfwGetCursorPos(window, &end_mouseX, &end_mouseY);

		if ((start_mouseX == end_mouseX) || (start_mouseY == end_mouseY)) {
			return;
		}

		double in1[2] = { start_mouseX, start_mouseY };
		double in2[2] = { end_mouseX, end_mouseY };

		Trackball(in1, in2);

		start_mouseX = end_mouseX;
		start_mouseY = end_mouseY;
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

// スクリーン座標系から3D座標系に変換
glm::vec3 Camera::screen_to_vec(double p[2]) {
	double x = 2 * p[0] / width - 1;
	double y = 1 - 2 * p[1] / height;
	double z = 0.0;
	double length = x * x + y * y;

	// https://www.xarg.org/2021/07/trackball-rotation-using-quaternions/
	if (0.5 >= length) {
		z = sqrt(1 - length);
	}
	else {
		z = 0.5 * sqrt(length);
	}

	return glm::normalize(glm::vec3(x, y, z));
}

void Camera::Trackball(double p1[2], double p2[2]) {
	// スクリーン座標系から3D座標系に変換
	glm::vec3 v1 = screen_to_vec(p1);
	glm::vec3 v2 = screen_to_vec(p2);

	// 2つのベクトル間の角度を計算
	double angle = glm::acos(glm::dot(v1, v2));

	auto dif = v2 - v1;
	auto length = glm::length(dif);
	angle = length;
	std::cout << "length:  " << length << std::endl;
	std::cout << "angle:  " << angle << std::endl;

	// 2つのベクトル間の回転軸を計算
	glm::vec3 axis = glm::normalize(glm::cross(v1, v2));

	// axis = glm::vec3(dif.y / length, dif.x / length , 0.0);

	#ifndef DEBUG
		std::cout << "axis: " << glm::to_string(axis) << std::endl;
	#endif

	// 回転行列を生成
	auto c = glm::cos(angle / 2);
	auto s = glm::sin(angle / 2);

	// 0除算を防ぐ
	if (abs(s) < 0.0005f) {
		return;
	}

	glm::quat q = glm::quat(c, s * axis[0], s * axis[1], s * axis[2]);
	Position = q * Position;
	Orientation = q * Orientation;
}