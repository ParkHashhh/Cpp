#include "ShaderManager.h"
#include "ShaderColor2D.h"


CShaderManager::CShaderManager()
{
}

CShaderManager::~CShaderManager()
{
}

bool CShaderManager::Init()
{
	if (!CreateShader<CShaderColor2D>("Color2D"))
		return false;
	return true;
}

std::weak_ptr<CShader> CShaderManager::FindShader(const std::string& Name)
{
	std::unordered_map<std::string, std::shared_ptr<CShader>>::iterator iter;
	iter = mShaderMap.find(Name);

	if (iter == mShaderMap.end())
		return std::shared_ptr<CShader>();
	return iter->second;
}
