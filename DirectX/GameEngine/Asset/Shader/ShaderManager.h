#pragma once
#include "../../EngineInfo.h"
#include "Shader.h"

class CShaderManager
{
	friend class CAssetManager;

private:
	CShaderManager();
	
public:
	~CShaderManager();

private:
	std::unordered_map<std::string, std::shared_ptr<CShader>> mShaderMap;


public:
	bool Init();
	std::weak_ptr<CShader> FindShader(const std::string& Name);

public:
	template <typename T>
	bool CreateShader(const std::string& Name)
	{
		std::weak_ptr<CShader> Check = FindShader(Name);

		if (!Check.expired())
			return false;

		T* Origin = new T;
		std::shared_ptr<CShader> Shader;

		Shader.reset(Origin);

		if (!Shader->Init())
			return false;

		mShaderMap.insert(std::make_pair(Name, Shader));

		return true;
	}

};




