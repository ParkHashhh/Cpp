#include "AssetManager.h"
#include "Mesh/MeshManager.h"
#include "Shader/ShaderManager.h"
#include "PathManager.h"


CAssetManager* CAssetManager::mInst = nullptr;

std::weak_ptr<CMeshManager> CAssetManager::GetMeshManager()
{
	return mMeshManager;
}

std::weak_ptr<class CShaderManager> CAssetManager::GetShaderManager()
{
	return mShaderManager;
}

CAssetManager::CAssetManager()
{
}

CAssetManager::~CAssetManager()
{
	CPathManager::Clear();
}

bool CAssetManager::Init()
{
	// 경로 관리자 초기화
	if (!CPathManager::Init())
		return false;

	mMeshManager.reset(new CMeshManager);

	if (!mMeshManager->Init())
		return false;

	mShaderManager.reset(new CShaderManager);

	if (!mShaderManager->Init())
		return false;

	return true;
}
