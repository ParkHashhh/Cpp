#include "Engine.h"


CEngine* CEngine::mInst = nullptr;
bool CEngine::mLoop = true;

CEngine::CEngine()
{
}

CEngine::~CEngine()
{
}

bool CEngine::Init(HINSTANCE hInst, const TCHAR* WindowName, int IconID,
	int SmallIconID, int Width, int Height, bool WindowMode)
{

	return true;
}

int CEngine::Run()
{

	return 0;
}