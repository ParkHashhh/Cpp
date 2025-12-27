#include "Timer.h"

// static 멤버 변수 초기화 (메모리 할당)
LARGE_INTEGER CTimer::mFrequency = {};
LARGE_INTEGER CTimer::mPrevCount = {};
float CTimer::mDeltaTime = 0.f;

void CTimer::Init()
{
    // 이컴퓨터의 진동수를 저장한다 (1초에 얼마나 진동하는지)
    QueryPerformanceFrequency(&mFrequency);
    // 현재 진동수가 얼마나 진동했는지 확인한다(Before)
    QueryPerformanceCounter(&mPrevCount);
}

float CTimer::Update()
{
    LARGE_INTEGER currCount;
    // 현재 진동수가 얼마나 진동했는지 확인한다(After)
    QueryPerformanceCounter(&currCount);

    // (현재 카운트 - 이전 카운트) / 초당 진동수 = 지나간 시간(초)

    mDeltaTime = (float)(currCount.QuadPart - mPrevCount.QuadPart) / (float)mFrequency.QuadPart;

    mPrevCount = currCount;

    return mDeltaTime;
}