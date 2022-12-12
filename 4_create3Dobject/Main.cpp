#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include"VAO.h"
#include"EBO.h"
#include"VBO.h"
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
	Shader shaderProgram("./4_create3Dobject/default.vert", "./4_create3Dobject/default.frag");

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

	// uniform変数のアクセスするためのメモリ位置を取得
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// テクスチャ設定
	Texture Tex("../image/human.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	// テクスチャユニットを配置
	Tex.texUnit(shaderProgram, "tex0", 0);

	// 立体を回転するために使用
	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	// デプステストの有効化
	glEnable(GL_DEPTH_TEST);

	// メインループ
	while (glfwWindowShouldClose(window) == GL_FALSE) {
		// 背景色指定	
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// 画面を初期化(色バッファ, デプスバッファを初期化)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// シェーダプログラムの有効化
		shaderProgram.Activate();

		// 立体物の回転の更新
		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60) {
			rotation += 0.5f;
			prevTime = crntTime;
		}

		// 初期化
		glm::mat4 model = glm::mat4(1.0f);	// モデル変換行列
		glm::mat4 view = glm::mat4(1.0f);	// ビュー変換行列
		glm::mat4 proj = glm::mat4(1.0f);	// 投影変換行列

		// モデル変換行列 設定
		model = glm::rotate(model,
					glm::radians(rotation),	// 回転角度
					glm::vec3(0.0f, 1.0f, 0.0f));	// y軸中心で回転

		// ビュー変換行列 設定
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));	// カメラの位置設定

		// 投影変換行列 設定（透視投影）
		proj = glm::perspective(glm::radians(45.0f),
							(float)(width / height),
							0.1f,
							100.0f);

		// uniform変数のアクセスするためのメモリ位置を取得
		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");

		// 変換行列をシェーダーに伝送
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		// uniform変数(scale)に値を入力
		glUniform1f(uniID, 0.5f);

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