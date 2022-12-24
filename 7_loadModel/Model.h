#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include<string>
#include<vector>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

#include"Mesh.h"

class Model {
public:
	// コンストラクタ
	Model(const char* filename,	// モデルファイル名
		const char* texdir);	// テクスチャがあるディレクトリ

	// 描画
	void Draw(Shader& shader, Camera camera);

	// ファイル内にある全てのテクスチャを保存
	std::vector<Texture> textures_loaded;	

	// Meshリスト
	std::vector<Mesh> meshList;

	// テクスチャ存在フラグ
	bool existTexture;

private:
	// モデル読み込み
	void loadModel(const char* filename);	

	// 各ノードに対して処理
	void processNode(aiNode* node, const aiScene* scene);

	// 各メッシュに対して処理
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	
	// マテリアル/テクスチャを読み込み
	std::vector<Texture> loadMaterialTextures\
		(aiMaterial* mat, aiTextureType type, std::string typeName);
	
	// テクスチャがあるディレクトリ(string型)
	std::string basepath;
};
#endif