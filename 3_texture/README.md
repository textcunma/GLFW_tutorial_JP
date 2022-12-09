# テクスチャ貼り付け

### stbライブラリの利用
テクスチャを読み込むために**stbライブラリ**を利用。
以下URLからstb_image.hをコピー。
https://github.com/nothings/stb/blob/master/stb_image.h

その後, Libraries/include/stbに「stb_image.h」を設置。
[動画](https://youtu.be/u-00hjlfMKc)を参照するとわかりやすいと思います。

また、stbを利用するために「**stb.cpp**」を作成
```c++
#define STB_IMAGE_IMPLEMENTATION
#include<stb/stb_image.h>
```

### テクスチャの読み込み
stbライブラリの関数を使用してテクスチャを読み込む。ただし、OpenGLとstbの座標系が反転しているため垂直反転する必要がある。
```c++
int widthImg, heightImg, numColCh;
stbi_set_flip_vertically_on_load(true);	// 垂直反転
unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);
```

### テクスチャの登録
テクスチャの登録は基本的にVBOと変わらない。変わっているところのみ記述する<br>

複数のテクスチャを同時に使用するため「テクスチャユニット」に各テクスチャを登録する必要がある。
特定のテクスチャを有効化するために以下のプログラムが必要。
```c++
glActiveTexture(slot);
```
次に、テクスチャを生成し、画像データをそのテクスチャに転送(テクスチャの登録)
```c++
glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
// 引数1: target : GL_TEXTURE_2Dを必ず指定
// 引数2: level : 0を基準とした詳細番号を指定(ミップマップを使わない場合は0)
// 引数3: internalformat: テクスチャ画像フォーマット(GL_RGBAなど)
// 引数4: width : テクスチャ画像の幅を指定
// 引数5: height : テクスチャ画像の高さを指定
// 引数6: border : 境界幅(0 or 1)
// 引数7: format : 入力ピクセルデータのフォーマット(GL_RGBA)など 
// 引数8: *pixels : 画像配列のポインタ
```

### テクスチャをシェーダーで利用
uniform変数にテクスチャ情報を入力してGLSLでテクスチャ座標と共に利用。これによってテクスチャを描画可能。
glUnifrom1i関数によってGLSLのuniform変数にデータを渡す。
```c++
void Texture::texUnit(Shader shader, const char* uniform, GLuint unit) {
	// uniform変数の識別子を得る
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);	

	// シェーダープログラムを有効化
	shader.Activate();

	// シェーダーにデータを渡す
	glUniform1i(texUni, unit);	
}
```
次に、その情報が「tex0」に代入。tex0とテクスチャ座標情報を用いてテクスチャが描画。
```glsl
uniform sampler2D tex0;

void main(){
	FragColor = texture(tex0, texCoord);
}
```