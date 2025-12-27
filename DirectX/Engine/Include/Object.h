#pragma once

#include "EngineInfo.h"

class CObject
{
public:
	CObject();
	CObject(const CObject& ref);
	CObject(CObject&& ref);
	virtual ~CObject() = 0;
};

