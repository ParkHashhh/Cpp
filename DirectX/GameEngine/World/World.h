#pragma once

#include "../EngineInfo.h"

class CWorld
{
public:
	CWorld();
	virtual ~CWorld();

protected:
	std::weak_ptr<CWorld> mSelf;


public:
	void SetSelf(std::weak_ptr<CWorld> Self)
	{
		mSelf = Self;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render();


};

