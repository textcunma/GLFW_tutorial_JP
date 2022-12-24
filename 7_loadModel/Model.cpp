#include"Model.h"

// コンストラクタ
Model::Model(const char* filename, const char* texdir) {
	// テクスチャが格納されたディレクトリをstring型で保存
	basepath = std::string(texdir);

	// 初期値としてテクスチャが存在するとする
	existTexture = true;

	// モデルを読み込む
	loadModel(filename);
}

// モデルを読み込む
void Model::loadModel(const char* filename) {
	// 読み込み後の後処理フラグ 設定(詳細はREADME.md)
	unsigned int flag = 0;
	flag |= aiProcess_Triangulate;
	flag |= aiProcess_PreTransformVertices;
	flag |= aiProcess_CalcTangentSpace;
	flag |= aiProcess_GenSmoothNormals;
	flag |= aiProcess_GenUVCoords;
	flag |= aiProcess_RemoveRedundantMaterials;
	flag |= aiProcess_OptimizeMeshes;

	// ファイルからシーンを読み込む
	Assimp::Importer Importer;
	const aiScene* pScene = Importer.ReadFile(filename, flag);

	// もしファイルが存在しない, 壊れている場合は...
	if (!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode) {
		std::cout << "MODEL_LOAD_ERROR for:" << Importer.GetErrorString() \
			<< "\n" << std::endl;
	}
	// それ以外の場合は...
	else {
		std::cout << "Import file name:  " << pScene->mRootNode->mName.data << std::endl;
		processNode(pScene->mRootNode, pScene);
	}
}

// 描画関数
void Model::Draw(Shader& shader, Camera camera) {
	for (unsigned int i = 0; i < meshList.size(); i++) {
		meshList[i].Draw(shader, camera);
	}
}

// 各ノードに対して処理
void Model::processNode(aiNode* node, const aiScene* scene) {
	// ノードに含まれる各メッシュに対して処理
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshList.push_back(processMesh(mesh, scene));
	}
	// 子ノードへ移動
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

// 各メッシュに対して処理
Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;

	// 頂点情報(座標, 法線, 頂点色, テクスチャ座標)
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		// 頂点 構造体
		Vertex vertex;

		// 座標
		const aiVector3D* pos = &(mesh->mVertices[i]);
		vertex.position = glm::vec3(pos->x, pos->y, pos->z);

		// 法線
		if (mesh->HasNormals()) {
			const aiVector3D* normal = &(mesh->mNormals[i]);
			vertex.normal = glm::vec3(normal->x, normal->y, normal->z);
		}

		// 頂点色
		if (mesh->HasVertexColors(0)) {
			const aiColor4D* color = &(mesh->mColors[0][i]);
			vertex.color = glm::vec3(color->r, color->g, color->b);
		}
		else {
			vertex.color = glm::vec3(0.0f, 0.0f, 0.0f);
		}

		// テクスチャ座標
		if (mesh->mTextureCoords[0]) {
			const aiVector3D* texcoord = &(mesh->mTextureCoords[0][i]);
			vertex.texUV = glm::vec2(texcoord->x, texcoord->y);
		}
		else {
			vertex.texUV = glm::vec2(0.0f, 0.0f);
		}

		// 頂点情報を格納
		vertices.push_back(vertex);
	}

	// インデックス
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	
	// マテリアル/テクスチャ
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	// 拡散反射マップ
	std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");

	// 鏡面反射マップ
	std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");

	// 拡散反射マップの存在を確認
	if (diffuseMaps.size() == 0) {
		std::cout << "Nothing diffuseMap" << std::endl;
	}
	else {
		// テクスチャ情報を格納
		textures.insert(textures.end(), diffuseMaps.begin(), \
			diffuseMaps.end());
	}

	// 鏡面反射マップの存在を確認
	if (specularMaps.size() == 0) {
		std::cout << "Nothing specularMap" << std::endl;
	}
	else {
		// テクスチャ情報を格納
		textures.insert(textures.end(), specularMaps.begin(), \
			specularMaps.end());
	}

	if ((diffuseMaps.size() == 0) && (specularMaps.size() == 0)) {
		existTexture = false;
	}

	return Mesh(vertices, indices, textures);
}

// マテリアル/テクスチャ読み込み
std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat,
	aiTextureType type,
	std::string typeName) {

	// テクスチャ情報を格納
	std::vector<Texture> textures;

	// 各テクスチャに対して処理
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
		// テクスチャのファイル名を取得
		aiString textureName;
		mat->GetTexture(type, i, &textureName);

		// 既にテクスチャがロードされているか確認
		bool loaded = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++) {
			// もし既にロードされていたら...
			if (std::strcmp(textures_loaded[j].path.data(), textureName.C_Str()) == 0){
				textures.push_back(textures_loaded[j]);
				loaded = true;
				break;
			}
		}
		// もしまだロードされていなかったら...
		if (!loaded){
			const char* texType;
			GLuint unit = textures_loaded.size();
			GLenum format;

			// パス + ファイル名
			std::string texturePath = \
				basepath + std::string(textureName.C_Str());

			// 拡散反射マップの場合
			if (type == aiTextureType_DIFFUSE) {
				texType = "diffuse";
				format = GL_RGBA;
			}
			// 鏡面反射マップの場合
			else {
				texType = "specular";
				format = GL_RED;
			}
			Texture texture = \
				Texture(texturePath.c_str(), texType, unit, format, GL_UNSIGNED_BYTE);

			textures.push_back(texture);
			textures_loaded.push_back(texture);
		}
	}
	return textures;
}

