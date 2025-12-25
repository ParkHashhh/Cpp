#include "Engine.h"


CEngine* CEngine::mInst = nullptr;
bool CEngine::mLoop = true;

CEngine::CEngine()
{
}

CEngine::~CEngine()
{
}

void CEngine::CreateWindowClass(const TCHAR* WindowName, int IconID,
	int SmallIconID)
{
	// 윈도우 클래스만드는 구조체 생성
	WNDCLASSEXW wcex;
	
	// 1. 구조체의 크기 설정 (운정체제가 버전을 확인하는 용도)
	wcex.cbSize = sizeof(WNDCLASSEXW);
	// 2. 클래스 스타일: 가로(H)나 세로(V) 크기가 변하면 화면을 다시 그리도록 설정
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	// 3. 메시지 처리 함수 등록: 아까 만든 static WndProc을 연결 (가장 중요!)
	wcex.lpfnWndProc = WndProc;
	// 4. 클래스/윈도우 예약 메모리: 보통 0으로 설정
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	// 5. 인스턴스 핸들: 이 프로그램의 고유 번호를 연결
	wcex.hInstance = mhInst;
	// 6. 아이콘 설정: 작업표시줄이나 Alt+Tab에 나올 큰 아이콘
	// MAKEINTRESOURCE: 정수 ID를 리소스 시스템이 인식할 수 있는 타입으로 변환
	wcex.hIcon = LoadIcon(mhInst, MAKEINTRESOURCE(IconID));
	// 7. 커서 설정: 창 위에 마우스를 올렸을 때 나타날 모양 (IDC_ARROW: 기본 화살표)
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	// 8. 배경색 설정: 창이 처음 뜰 때 채워질 배경 브러쉬 (기본 흰색/회색 계열)
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	// 9. 메뉴 이름: 상단 메뉴바(파일, 편집 등)를 쓸지 결정 (게임에선 보통 nullptr)
	wcex.lpszMenuName = nullptr;
	// 10. 클래스 이름: 이 설계도의 고유 이름. 나중에 CreateWindow할 때 이 이름을 부름
	wcex.lpszClassName = WindowName;
	// 11. 작은 아이콘: 창 왼쪽 상단 구석에 나올 아이콘
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(SmallIconID));
	// 마지막 단계: 위 설정값들을 운영체제 시스템에 등록
	RegisterClassExW(&wcex);
}

LRESULT CEngine::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	// message: 현재 발생한 이벤트의 종류 (예: 마우스 클릭, 키 입력, 창 닫기 등)
	switch (message)
	{
	// 1. 창의 일부가 가려졌다가 다시 나타나거나, 강제로 그려야 할 때 발생
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		// GDI(Windows 기본 그리기) 시스템을 시작합니다.
		HDC hdc = BeginPaint(hWnd, &ps);

		// GDI 그리기 시스템을 종료합니다.
		EndPaint(hWnd, &ps);
	}
	break;
	// 2. 창이 파괴될 때(X 버튼을 눌렀을 때 등) 발생
	case WM_DESTROY:
	{
		// 엔진의 메인 루프(while문)를 멈추기 위해 static 변수인 mLoop를 false로 만듭니다.
		mLoop = false;
		// 메시지 큐에 "종료할 거야(WM_QUIT)"라는 메시지를 던집니다. 
		// 이 메시지가 나중에 GetMessage나 PeekMessage에서 잡히면 프로그램이 완전히 종료됩니다.
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

bool CEngine::Create(const TCHAR* WindowName, int Width, int Height)
{

	// 창을 만들어준다. 만들어준 창을 컨트롤 할 수 있는 핸들도 함께 반환된다.
	// 1번 : 윈도우 클래스 이름
	// 2번 : 윈도우 타이틀바에 출력할 이름
	// 3번 : 윈도우 창 스타일을 지정한다.
	// 4번 : 윈도우 창 시작 X좌표를 지정한다.
	// 5번 : 윈도우 창 시작 Y좌표를 지정한다.
	// 6번 : 윈도우 창 가로 크기
	// 7번 : 윈도우 창 세로 크기
	// 8번 : 부모 윈도우 핸들
	// 9번 : 메뉴 핸들
	// 10번 : 식별번호
	mhWnd = CreateWindowW(WindowName, WindowName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, Width, Height, nullptr, nullptr, mhInst, nullptr);
	if (!mhWnd)
		return false;

	// 클라이언트 영역의 해상도를 RECT로 만든다.
	RECT WindowRC = { 0,0,Width,Height };

	// 클라이언트 영역이 해상도 크기로 생성되기 위해 ThickFrame이나 기타 요소들을 포함한 실제 크기를 얻어온다.
	AdjustWindowRect(&WindowRC, WS_OVERLAPPEDWINDOW, FALSE);
	// 윈도우 크기를 변경한다.
	SetWindowPos(mhWnd, HWND_TOPMOST, 0, 0, WindowRC.right - WindowRC.left,
		WindowRC.bottom - WindowRC.top, SWP_NOMOVE | SWP_NOZORDER);

	// 창을 보여줄지를 결정한다.
	ShowWindow(mhWnd, SW_SHOW);

	// 이 윈도우를 즉시 다시 그리게 만들어준다.
	// WM_PAINT 메세지를 발생시켜준다.
	UpdateWindow(mhWnd);


	return true;
}

bool CEngine::Init(HINSTANCE hInst, const TCHAR* WindowName, int IconID,
	int SmallIconID, int Width, int Height, bool WindowMode)
{
	// 윈도우 클래스 생성 해야함
	mhInst = hInst;
	CreateWindowClass(WindowName, IconID, SmallIconID);
	Create(WindowName, Width, Height);



	return true;
}



int CEngine::Run()
{
	MSG msg = {};

	// mLoop가 true인 동안 무한 반복 (WM_DESTROY에서 false로 바뀜)
	while (mLoop)
	{
		// 1. 메시지 큐에 메시지가 있는지 확인 (기다리지 않고 바로 반환)
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// 메시지가 있으면 처리
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// 2. 메시지가 없을 때 게임 로직 수행 (프레임워크의 핵심)
			// 여기서 나중에 Update(), Render() 등을 호출합니다.
		}
	}

	return (int)msg.wParam;
}