#include"Mesh.h"
#include"Model.h"
#include"utils.h"

// 光源頂点
Vertex lightVertices[] = {
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
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

// マテリアル
double materials[10] = {
	0.24175f, 0.1995f, 0.0745f,
	0.75164f, 0.60648f, 0.22648f,
	0.628281f, 0.555802f, 0.366065f,
	0.4f
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
	Shader shaderProgram("./default.vert", "./default.frag");

	// モデルを読み込む
	Model model("../image/bunny.obj", "../image/");

	// 光に関するシェーダー読み込み
	Shader lightShader("./light.vert", "./light.frag");

	// 光源頂点, 光源インデックスのベクトルを作成
	std::vector <Vertex> lightVerts(lightVertices, \
		lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, \
		lightIndices + sizeof(lightIndices) / sizeof(GLuint));

	// lightを作成
	Mesh light(lightVerts, lightInd);

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

	// unifrom変数に値を渡す
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), \
		1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), \
		lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	
	// シェーダー有効化
	shaderProgram.Activate();

	// unifrom変数に値を渡す
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), \
		1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), \
		lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), \
		lightPos.x, lightPos.y, lightPos.z);


	// もしテクスチャが無い場合はマテリアルを適用
	if (!model.existTexture) {
		Material material;
		material.registerMaterial(materials);
		material.MaterialUnit(shaderProgram);
		glUniform1i(glGetUniformLocation(shaderProgram.ID, "existTexture"), 0);	// false
	}
	else {
		glUniform1i(glGetUniformLocation(shaderProgram.ID, "existTexture"), 1);	// true
	}

	// デプステストの有効化
	glEnable(GL_DEPTH_TEST);

	// 画面の更新頻度設定(1秒につき1回更新)
	glfwSwapInterval(1);

	// カメラ設定
	Camera camera(width, height, glm::vec3(0.0f, 2.0f, 2.0f));

	// 画像保存用バッファ
	unsigned char* image_data = (unsigned char*)malloc(width * height * 3);

	// Enterキーの連続押しを避けるため
	double lastTime = 0.0f;
	double curTime = glfwGetTime();

	// メインループ
	while (!glfwWindowShouldClose(window)) {
		// 背景色指定	
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// 画面を初期化(色バッファ, デプスバッファを初期化)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// カメラ操作入力
		camera.Inputs(window);

		// 変換行列作成
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// 被写体を描画
		model.Draw(shaderProgram, camera);

		// 光源を描画
		light.Draw(lightShader, camera);

		// シェーダプログラムの無効化
		glUseProgram(0);

		// 画面を更新
		glfwSwapBuffers(window);

		// Enterキーを押された場合、画像保存
		curTime = glfwGetTime();
		if ((curTime - lastTime > 1.0f) && (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)) {
			glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, image_data);
			imageSave(image_data, width, height);
			lastTime = curTime;
		}

		// ユーザーからの入力イベントを処理
		glfwPollEvents();
	}

	// シェーダープログラムを削除
	shaderProgram.Delete();
	lightShader.Delete();
	stbi_image_free(image_data);

	// ウィンドウの消去
	glfwDestroyWindow(window);

	// GLFWの終了処理
	glfwTerminate();
	return 0;
}