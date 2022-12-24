#include"Material.h"

// コンストラクタ
Material::Material() {
	material_amb = { 0.0f, 0.0f, 0.0f };
	material_dif = { 0.0f, 0.0f, 0.0f };
	material_spec = { 0.0f, 0.0f, 0.0f };
	material_shin = 0.0f;
}


void Material::registerMaterial(double element[10]) {
	material_amb = { element[0], element[1], element[2]};
	material_dif = { element[3], element[4], element[5]};
	material_spec = { element[6], element[7], element[8]};
	material_shin = element[9];
}

// Uniform変数に代入
void Material::MaterialUnit(Shader& shader) {
	// シェーダープログラムを有効化
	shader.Activate();
	glUniform3f(glGetUniformLocation(shader.ID, "material.ambient"),
		material_amb[0], material_amb[1], material_amb[2]);
	glUniform3f(glGetUniformLocation(shader.ID, "material.diffuse"),
		material_dif[0], material_dif[1], material_dif[2]);
	glUniform3f(glGetUniformLocation(shader.ID, "material.specular"),
		material_spec[0], material_spec[1], material_spec[2]);
	glUniform1f(glGetUniformLocation(shader.ID, "material.shininess"),
		material_shin);
}
