#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"VAO.h"
#include"EBO.h"
#include"VBO.h"
#include"shaderClass.h"

// 頂点
GLfloat vertices[] = {
	// x座標	y座標						z座標
	-0.5f, 	-0.5f * float(sqrt(3)) / 3, 		0.0f,
	0.5f, 	-0.5f * float(sqrt(3)) / 3, 		0.0f,
	0.0f, 	0.5f * float(sqrt(3)) * 2 / 3, 	0.0f,
	-0.25f, 	0.5f * float(sqrt(3)) / 6, 		0.0f,
	0.25f, 	0.5f * float(sqrt(3)) / 6, 		0.0f,
	0.0f, 	-0.5f * float(sqrt(3)) / 3, 		0.0f
};

// インデックス
GLuint indices[] = {
	0, 3, 5,	// 三角形(左下)
	3, 2, 4,	// 三角形(右下)
	5, 4, 1	// 三角形(上部)
};

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

	// シェーダーファイル読み込み
	Shader shaderProgram("default.vert", "default.frag");
	
	// VAOを作成, 有効化
	VAO VAO1;
	VAO1.Bind();

	// VBOを作成, 有効化, 頂点データを設定
	VBO VBO1(vertices, sizeof(vertices));

	// EBOを作成, 有効化, インデックスデータを設定
	EBO EBO1(indices, sizeof(indices));
	
	// VBOを連携(location = 0)
	VAO1.LinkVBO(VBO1, 0);

	// VAO, VBO, EBOを無効化
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// メインループ
	while (glfwWindowShouldClose(window) == GL_FALSE) {
		// 背景色指定	
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// 画面を初期化(色バッファを初期化)
		glClear(GL_COLOR_BUFFER_BIT);

		// シェーダプログラムの有効化
		shaderProgram.Activate();

		// VAOを有効化
		VAO1.Bind();

		// backバッファに図形を描画
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// シェーダプログラムの無効化
		glUseProgram(0);

		// 画面を更新
		glfwSwapBuffers(window);

		// ユーザーからの入力イベントを処理
		glfwPollEvents();
	}

	// VAO, VBO, EBO, シェーダープログラムを削除
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// ウィンドウの破棄
	glfwDestroyWindow(window);

	// GLFWの終了処理
	glfwTerminate();
	return 0;
}