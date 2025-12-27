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

private:
	void CreateWindowClass(const TCHAR* WindowName, int IconID,
		int SmallIconID);

	static LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	bool Create(const TCHAR* WindowName, int Width, int Height);

	void Logic();
	void Update(float DeltaTime);
	void Render();

public:
	bool Init(HINSTANCE hInst, const TCHAR* WindowName, int IconID,
		int SmallIconID, int Width, int Height, bool WindowMode = true);
	int Run();

};

