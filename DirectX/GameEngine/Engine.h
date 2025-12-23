#pragma once
#include "EngineInfo.h"

class CEngine
{
private:
	CEngine();
	~CEngine();


private:
	static CEngine* mInst;

private:

	HINSTANCE	mhInst;
	HWND		mhWnd;

	static bool	mLoop;
public:
	static CEngine* GetInst()
	{
		if (!mInst)
			mInst = new CEngine;
		return mInst;
	}
	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}
};

