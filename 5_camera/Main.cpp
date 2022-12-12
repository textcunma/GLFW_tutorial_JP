#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include"VAO.h"
#include"EBO.h"
#include"VBO.h"
#include"Camera.h"
#include"Texture.h"
#include"shaderClass.h"

// 頂点情報
GLfloat vertices[] = {
	// 座標情報			色情報				テクスチャ座標
	-0.5f,	0.0f,  0.5f,	0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f,	0.0f, -0.5f,	0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f,	0.0f, -0.5f,	0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f,	0.0f,  0.5f,	0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f,	0.8f,  0.0f,	0.92f, 0.86f, 0.76f,	2.5f, 5.0f,
};

// 頂点インデックス
GLuint indices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
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
	Shader shaderProgram("./5_camera/default.vert", "./5_camera/default.frag");

	// VAOを作成, 有効化
	VAO VAO1;
	VAO1.Bind();

	// VBOを作成, 有効化, 頂点データを設定
	VBO VBO1(vertices, sizeof(vertices));

	// EBOを作成, 有効化, インデックスデータを設定
	EBO EBO1(indices, sizeof(indices));

	// VBOを連携(頂点位置, 頂点色, テクスチャ座標)
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float),
		(void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float),
		(void*)(6 * sizeof(float)));

	// VAO, VBO, EBOを無効化
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// テクスチャ設定
	Texture Tex("./5_camera/human.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	// デプステストの有効化
	glEnable(GL_DEPTH_TEST);

	// 画面の更新頻度設定(1秒につき1回更新)
	glfwSwapInterval(1);

	// カメラ設定(カメラ位置指定)
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));	

	// メインループ
	while (glfwWindowShouldClose(window) == GL_FALSE) {
		// 背景色指定	
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// 画面を初期化(色バッファ, デプスバッファを初期化)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// シェーダプログラムの有効化
		shaderProgram.Activate();

		// カメラ操作入力
		camera.Inputs(window);

		// 変換行列作成
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		// テクスチャを有効化
		Tex.Bind();

		// VAOを有効化
		VAO1.Bind();

		// backバッファに図形を描画
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		// シェーダプログラムの無効化
		glUseProgram(0);

		// 画面を更新
		glfwSwapBuffers(window);

		// ユーザーからの入力イベントを処理
		glfwPollEvents();
	}

	// VAO, VBO, EBO, テクスチャ, シェーダープログラムを削除
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	Tex.Delete();
	shaderProgram.Delete();

	// ウィンドウの消去
	glfwDestroyWindow(window);

	// GLFWの終了処理
	glfwTerminate();
	return 0;
}