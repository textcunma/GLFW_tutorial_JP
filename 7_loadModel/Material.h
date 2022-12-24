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

	// �R���X�g���N�^
	Material();

	// �}�e���A����o�^
	void registerMaterial(double element[10]);

	// uniform�ϐ��ɑ��(�V�F�[�_�[�Ƀf�[�^��n��)
	void MaterialUnit(Shader& shader);

};

#endif 