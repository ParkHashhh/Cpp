#include "PathManager.h"

std::unordered_map<std::string, TCHAR*> CPathManager::mPathMap;


void CPathManager::Clear()
{
	using uniter = std::unordered_map<std::string, TCHAR*>::const_iterator;
	uniter iterbegin = mPathMap.begin();
	uniter iterEnd = mPathMap.end();

	for (;iterbegin != iterEnd; ++iterbegin)
	{
		delete[] iterbegin->second;
	}



}

bool CPathManager::Init()
{
	TCHAR Path[MAX_PATH] = {};
	GetModuleFileName(nullptr, Path, MAX_PATH);
	// 루트 경로 생성
	int Count = 0;
	for (int i = lstrlen(Path) - 1; i >= 0; --i)
	{
		if (Path[i] == '\\' || Path[i] == '/')
		{
			Path[i] = '\0'; // 하나씩 잘라냄
			Count++;
			if (Count == 3) break; // [Client.exe], [Debug], [x64] 세 번 탈출
		}
	}

	// 마지막에 다시 '\'를 붙여서 경로 완성
	lstrcat(Path, TEXT("\\GameEngine\\"));

	mPathMap.insert(std::make_pair("Root", _wcsdup(Path))); // 문자열 복사해서 저장

	// 이제 여기서부터 상대경로 시작
	CreatePath("Asset", TEXT("Asset\\"));
	CreatePath("Shader", TEXT("Shader\\"), "Asset");

	return true;
}

bool CPathManager::CreatePath(const std::string& Name, const TCHAR* Path, const std::string& BasePathName)
{
	if (FindPath(Name))
		return false;

	const TCHAR* BasePath = FindPath(BasePathName);
	if (!BasePath)
		return false;
	TCHAR* FullPath = new TCHAR[MAX_PATH];


	memset(FullPath, 0, sizeof(TCHAR) * MAX_PATH);
	lstrcpy(FullPath, BasePath);
	lstrcat(FullPath, Path);

	mPathMap.insert(std::make_pair(Name, FullPath));

	return true;
}

const TCHAR* CPathManager::FindPath(const std::string& Name)
{
	auto iter = mPathMap.find(Name);
	if (iter == mPathMap.end())
		return nullptr;	

	return iter->second;
}
