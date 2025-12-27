#pragma once

#include "../EngineInfo.h"

class CWorldManager
{
private:
	CWorldManager();
	~CWorldManager();

private:
	static CWorldManager* mInst;

private:
	std::shared_ptr<class CWorld> mWorld;

public:
	std::weak_ptr<CWorld> GetWorld() const
	{
		return mWorld;
	}

public:
	static CWorldManager* GetInst()
	{
		if (!mInst)
			mInst = new CWorldManager;
		return mInst;
	}
	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}

public:
	bool Init();
	void Update(float DeltaTime);
	void Render();
};

