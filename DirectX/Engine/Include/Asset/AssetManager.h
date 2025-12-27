#pragma once
#include "../EngineInfo.h"

class CAssetManager
{
private:
	CAssetManager();
	~CAssetManager();
	
private:
	static CAssetManager* mInst;

private:
	std::shared_ptr<class CMeshManager>	mMeshManager;
	std::shared_ptr<class CShaderManager>	mShaderManager;

public:
	std::weak_ptr<class CMeshManager> GetMeshManager();
	std::weak_ptr<class CShaderManager> GetShaderManager();

public:
	bool Init();
public:
	static CAssetManager* GetInst()
	{
		if (!mInst)
			mInst = new CAssetManager;
		return mInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}
};

