# GLFW_tutorial_JP
日本語GLFWチュートリアル

## 概要
OpenGLライブラリのGLFWのチュートリアル。3DCGに関する知識, 処理について学びます。

## 環境
|    |  version  |
| ---- | ---- |
|  OpenGL  |  3.3  |
|  GLFW  |  3.3.8 |
| Glad    | Language: C/C++ <br>  API gl: Version 3.3 <br>Profile: Core |

## 準備
GLFWのインストール、Visual Studioの環境構築はVictor Gordan氏の動画を参考にしてください。

[OpenGL Tutorial 0 - Install](https://youtu.be/XpBGwZNyUh0)

## 内容
【基礎編】<br>
1. ウィンドウ生成
2. 三角形生成
3. テクスチャ
4. 3Dオブジェクト生成
5. カメラ
6. 光
7. モデル読み込み

【応用編】<br>
作る...かも?

## ファイル構造
```
├─1_createWindow
│                  
├─2_createTriangle
│                  
├─3_texture
│                  
├─4_create3Dobject
│                  
├─5_camera
│  
├─6_createLight
│                  
├─7_loadModel
│                  
├─assets
│      
├─Libraries
│  ├─include
│  │  ├─assimp
│  │  │              
│  │  ├─glad
│  │  │      glad.h
│  │  │      
│  │  ├─GLFW
│  │  │      glfw3.h
│  │  │      glfw3native.h
│  │  │      
│  │  ├─glm
│  │  │      
│  │  └─stb
│  │          stb_image.h
│  │          stb_image_write.h
│  │          
│  └─lib
│          assimp-vc143-mtd.lib
│          glfw3.lib
├─image
```
## 参考
- [Victor Gordan氏によるOpenGLチュートリアル](https://www.youtube.com/playlist?list=PLPaoO-vpZnumdcb4tZc4x5Q-v7CkrQ6M-)
- [LEARN OPENGL](https://learnopengl.com/)
- [GLFW による OpenGL 入門](https://tokoik.github.io/GLFWdraft.pdf)
- [opengl-tutorial](http://www.opengl-tutorial.org/jp/)
- [OpenGL PukiWiki](https://www.slis.tsukuba.ac.jp/~fujisawa.makoto.fu/cgi-bin/wiki/index.php?OpenGL)
- [床井先生のブログ](https://marina.sys.wakayama-u.ac.jp/~tokoi/?blogcategory=GLFW)