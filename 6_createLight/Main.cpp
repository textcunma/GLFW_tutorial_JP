#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"VAO.h"
#include"EBO.h"
#include"VBO.h"
#include"Camera.h"
#include"Texture.h"
#include"shaderClass.h"

// 頂点情報
GLfloat vertices[] = {
	// 座標情報				色情報				　　テクスチャ座標		法線
	-1.0f,	0.0f,	1.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,
	-1.0f,	0.0f,	-1.0f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	1.0f,	0.0f,
	1.0f,	0.0f,	-1.0f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	0.0f,	1.0f,	0.0f,
	1.0f,	0.0f,	1.0f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,	1.0f,	0.0f
};

// 頂点インデックス
GLuint indices[] = {
	0, 1, 2,
	0, 2, 3
};

// 光源頂点
GLfloat lightVertices[] = {
	-0.1f, -0.1f, 0.1f,
	-0.1f, -0.1f, -0.1f,
	0.1f, -0.1f, -0.1f,
	0.1f, -0.1f, 0.1f,
	-0.1f, 0.1f, 0.1f,
	-0.1f, 0.1f, -0.1f,
	0.1f, 0.1f, -0.1f,
	0.1f, 0.1f, 0.1f
};

// 光源頂点インデックス
GLuint lightIndices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
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
	Shader shaderProgram("./6_createLight/default.vert", "./6_createLight/default.frag");
	
	// VAOを作成, 有効化
	VAO VAO1;
	VAO1.Bind();

	// VBOを作成, 有効化, 頂点データを設定
	VBO VBO1(vertices, sizeof(vertices));

	// EBOを作成, 有効化, インデックスデータを設定
	EBO EBO1(indices, sizeof(indices));

	// VBOを連携(頂点位置, 頂点色, テクスチャ座標, 法線)
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);					// 頂点
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));	// 色
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));	// テクスチャ
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));	// 法線

	// VAO, VBO, EBOを無効化
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// 光に関するシェーダー読み込み
	Shader lightShader("./6_createLight/light.vert", "./6_createLight/light.frag");

	// 光に関するVAOを作成, 有効化
	VAO lightVAO;
	lightVAO.Bind();

	// 光に関するVBOを作成, 有効化, 頂点データを設定
	VBO lightVBO(lightVertices, sizeof(lightVertices));

	// 光に関するEBOを作成, 有効化, インデックスデータを設定
	EBO lightEBO(lightIndices, sizeof(lightIndices));

	// 光に関するVBOを連携(頂点位置)
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	
	// 光に関するVAO, VBO, EBOを無効化
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	// 光源の色と位置
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);

	// モデル変換行列(光源)
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	// 被写体の位置
	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);

	// モデル変換行列(被写体)
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);

	// 光に関するシェーダー有効化
	lightShader.Activate();

	// unifrom変数(model)にモデル変換行列を渡す
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"),	// vert
		1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"),		// frag
		lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	// シェーダー有効化
	shaderProgram.Activate();

	// unifrom変数(model)にモデル変換行列を渡す
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1,	// vert
		GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"),	// frag
		lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"),		// frag
		lightPos.x, lightPos.y, lightPos.z);

	// 拡散反射マップ
	Texture tileTex("./6_createLight/container2.png", \
		GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
	tileTex.texUnit(shaderProgram, "tex0", 0);

	// スペキュラーマップ
	Texture tileSpec("./6_createLight/container2_specular.png", \
		GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
	tileSpec.texUnit(shaderProgram, "tex1", 1);

	// デプステストの有効化
	glEnable(GL_DEPTH_TEST);

	// 画面の更新頻度設定(1秒につき1回更新)
	glfwSwapInterval(1);

	// カメラ設定
	Camera camera(width, height, glm::vec3(0.0f, 2.0f, 2.0f));

	// メインループ
	while (glfwWindowShouldClose(window) == GL_FALSE) {
		// 背景色指定	
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// 画面を初期化(色バッファ, デプスバッファを初期化)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// カメラ操作入力
		camera.Inputs(window);

		// 変換行列作成
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// シェーダプログラムの有効化
		shaderProgram.Activate();

		// uniform変数(camPos)にカメラ位置座標を代入
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"),	// frag
			camera.Position.x, camera.Position.y, camera.Position.z);

		// uniform変数(camMatrix)にビュー・投影変換の合成行列を代入
		camera.Matrix(shaderProgram, "camMatrix");

		// テクスチャを有効化
		tileTex.Bind();
		//tileSpec.Bind();

		// VAOを有効化
		VAO1.Bind();

		// backバッファに図形を描画
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		// 光に関するシェーダーを有効化
		lightShader.Activate();

		// uniform変数(camMatrix)にビュー・投影変換の合成行列を代入
		camera.Matrix(lightShader, "camMatrix");

		// 光に関するVAOを有効化
		lightVAO.Bind();

		// backバッファに図形を描画
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

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
	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	tileTex.Delete();
	tileSpec.Delete();
	shaderProgram.Delete();
	lightShader.Delete();

	// ウィンドウの消去
	glfwDestroyWindow(window);

	// GLFWの終了処理
	glfwTerminate();
	return 0;
}