# Meshクラス作成
今まで作成してきたものを一般化するためにMeshクラスを作成。全体の構造は以下のようになる。

<img src="../assets/7_overallclass.jpg">

主に新しい点としては頂点データをベクトルで扱うこと、そして頂点データ構造を用いてデータを扱うこと。
```
// VBO.h
// 頂点データ構造
struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};
```

