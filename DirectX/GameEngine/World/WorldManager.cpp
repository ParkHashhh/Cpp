#include "WorldManager.h"
#include "World.h"
CWorldManager* CWorldManager::mInst = nullptr;


CWorldManager::CWorldManager()
{
}

CWorldManager::~CWorldManager()
{
}



bool CWorldManager::Init()
{
	mWorld = std::make_shared<CWorld>();

	if (!mWorld->Init())
		return false;

	return true;

}
void CWorldManager::Update(float DeltaTime)
{
	mWorld->Update(DeltaTime);
}

void CWorldManager::Render()
{
	mWorld->Render();
}