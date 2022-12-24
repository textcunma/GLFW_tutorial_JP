#ifndef MATERIAL_CLASS_H
#define MATERIAL_CLASS_H
#include<glad/glad.h>
#include <array>
#include"shaderClass.h"

class Material {
public:
	std::array<double, 3> material_amb;
	std::array<double, 3> material_dif;
	std::array<double, 3> material_spec;
	float material_shin;

	// コンストラクタ
	Material();

	// マテリアルを登録
	void registerMaterial(double element[10]);

	// uniform変数に代入(シェーダーにデータを渡す)
	void MaterialUnit(Shader& shader);

};

#endif 