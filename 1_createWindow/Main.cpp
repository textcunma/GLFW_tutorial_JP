#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

const unsigned int width = 800;    // ウィンドウ幅
const unsigned int height = 800;   // ウィンドウ高さ

int main() {
     // GLFW初期化
	glfwInit();	

	// OpenGL バージョン3.3指定
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// コアプロファイルを設定
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ウィンドウ生成
	GLFWwindow* window = \
          glfwCreateWindow(width, height, "GLFW Tutorial", NULL, NULL);
	
	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

     // OpenGLが描画するウィンドウを指定
	glfwMakeContextCurrent(window);

	// GLAD読み込み
	gladLoadGL();

     // ウィンドウ開始位置を指定
	glViewport(0, 0, width, height);

     // 背景色指定					
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

     // 画面を初期化(色バッファを初期化)
	glClear(GL_COLOR_BUFFER_BIT);

	// 画面を更新
	glfwSwapBuffers(window);

	// メインループ
	while (glfwWindowShouldClose(window) == GL_FALSE) {
		// ユーザーからの入力イベントを処理
		glfwPollEvents();
	}

	// ウィンドウの破棄
	glfwDestroyWindow(window);

	// GLFWの終了処理
	glfwTerminate();
	return 0;
}