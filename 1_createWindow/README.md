# ウィンドウ生成

### プロファイル設定
プロファイルは2種類存在
- コアプロファイル(Core Profile)
- 互換プロファイル(Compatibility Profile)

互換プロファイルは将来的には廃止される古いOpenGL機能を持つため、勉強としてはコアプロファイルを使用することが良い。

今回はCoreをインストールしたため「*GLFW_OPENGL_CORE_PROFILE*」を設定。コアプロファイルは**GLSL**というシェーダー言語を利用して複雑な3DCG処理を行う
```C++
// コアプロファイルを設定
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
```

### GLAD読み込み
GLADとはOpenGLの拡張機能を読み込むためのライブラリ。また、OpenGLの機能を利用するための命令を簡単に取得可能。
```C++
//　GLAD読み込み
// 必ずglfwMakeContextCurrentの後に記述
gladLoadGL();
```

### 画面を初期化 & ダブルバッファリング
- 画面を初期化

     glClear関数によって画面を初期化。具体的にはbackバッファを消去して背景色を設置

     ```C++
     glClear(GL_COLOR_BUFFER_BIT);
     ```

- ダブルバッファリング

     スムーズな描画のために2つのバッファを使用して画面描画を行う手法。画面表示されるfrontバッファと裏で描画を行うbackバッファを利用、backバッファの描画が完了するとfrontバッファとbackバッファを交換して表示を行う。<br>
     glfwSwapBuffers関数によってバッファの交換を行う。
     ```C++
     // 画面を更新
     // frontバッファとbackバッファを交換
     glfwSwapBuffers(window);
     ```
### ユーザー操作
ユーザーに操作可能にするようにglfwPollEvents関数を利用。<br>
マウス、キーボード操作が可能になり、**ウィンドウの移動、拡大縮小**、キーボード入力等が可能

```C++
// ユーザーからの入力イベントを処理
glfwPollEvents();
```