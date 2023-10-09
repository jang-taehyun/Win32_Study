#pragma once

/**
* Singleton pattern(싱글톤 패턴) : 객체의 생성을 1개로 제한하는 방법
* - 싱글톤으로 만들어진 단 1개의 객체는 어디서든 쉽게 접근 가능해야 한다.
* - 객체가 생성되었다면, 이후 객체가 생성되는 것을 불가능하게 만들어야 한다.
* - constructor를 숨겨야 한다.(생성자를 private 영역으로 넣어야 한다.)
*	-> constructor를 숨기면 외부에서 객체를 선언할 수 없다.
*	-> but, 외부에서 선언이 불가능해지기 때문에, extern 선언을 할 수 없어 객체를 아예 만들 수가 없다.
* - 객체를 얻는 방법을 특정 function를 통해서만 얻을 수 있게 제한을 거는 방법
*	-> 객체를 얻을 수 있는 function을 만들어서 외부에 제공하고, 그 function은 객체가 없어도 호출할 수 있어야 한다.
*	   -> static 키워드를 이용해 function을 만든다.(정적 멤버함수를 만들어서 객체 없이 호출 가능하게 한다.)
*		  -> but, 정적 멤버함수는 일반 member variable 접근을 할 수 없다(Why? : 어떤 객체가 호출했는지 모르기 때문, this 키워드가 없음)
*		  -> 일반적인 멤버함수는 this 키워드를 가지고 있어, 어떤 객체가 function을 호출했는지 알 수 있다.
*		  -> 정적 멤버함수는 정적 member variable(static으로 선언된 member variable)만 접근할 수 있다.
* - 구현 방법 : dynamic allocate 이용하는 방법(포인터는 Data 영역에 실제 객체는 Heap 영역에 생성), Data 영역을 이용하는 방법, template를 이용하는 방법
*/

/**
* 변수의 종류
* 1. 지역 변수
* 2. 전역 변수 : Data 영역을 사용하면서 프로그램 어디에서나 접근 가능한 변수
*	 -> 만약 이름이 같은 전역 변수가 2개 이상 선언되면, Linking에서 error가 발생한다.
* 3. 정적 변수(static 변수) : Data 영역을 사용하는 변수, 반드시 static 키워드가 붙는다.
*	 1) 함수 안에 선언 : 함수의 생성, 호출, 종료에 상관없이 Data 영역에 그대로 남아 있다. but 해당 함수에서만 접근할 수 있다.
*		-> 초기화는 함수가 처음 호출되었을 때 단 1번만 실행되고, 그 후부터 초기화 코드는 무시된다.
*	 2) 파일 안에 선언 : 해당 파일에서만 접근 가능하기 때문에 여러 파일에 이름이 중복되어도 상관없다.
*		-> 만약 Linking을 했을 때 같은 파일 안에만 있지 않으면 이름이 중복되어 상관없다.
*	 3) 클래스 안에 선언 : 객체 안에 포함되어 있지 않고, Data 영역에 단 1개만 존재한다. and 클래스 내부에서만 접근 가능하다.
*		-> 객체가 아무리 많아도 static member는 Data 영역에 단 1개만 존재한다.
*		-> static member는 반드시 클래스 밖에서 초기화해야 한다.
* 4. 외부 변수 : 전역 변수에 extern이 붙은 형태
*/

// dynamic allocate 이용하는 방법
/**
* 장점
* - 원하는 시점에 소멸 및 생성이 가능하다.
*
* 단점
* - 객체 소멸을 신경써야 한다.
*/
//class CCore
//{
//private:
//	static CCore* g_pInst;
//
//public:
//	static CCore* GetInstance()
//	{
//		if (nullptr == g_pInst)
//		{
//			g_pInst = new CCore;
//		}
//
//		return g_pInst;
//	}
//	static void ReleaseInstance()
//	{
//		if (nullptr != g_pInst)
//		{
//			delete GetInstance();
//			g_pInst = nullptr;
//		}
//	}
//
//	// 외부에서 객체가 만들어지는 것을 제한하기 위해 생성자와 소멸자를 숨긴다.
//private:
//	CCore();
//	~CCore();
//};

// Data 영역을 이용하는 방법
/**
* 장점
* - 객체 소멸을 신경쓰지 않아도 된다.
* 
* 단점
* - 원하는 시점에서 소멸이 불가능하다.
*/
//class CCore
//{
//public:
//	static CCore* GetInst()
//	{
//		static CCore core;
//
//		return &core;
//	}
//
//private:
//	CCore();
//	~CCore();
//};


class CCore
{
	SINGLETON(CCore);

private:
	HWND m_hWnd;			// 메인 윈도우 핸들
	POINT m_ptResolution;	// 윈도우 해상도
	HDC m_hDeviceContext;	// 메인 윈도우에 draw할 DC

public:
	int Init(HWND _hWnd, POINT _ptResolution);
	void Progress();

private:
	void Update();
	void Render();

private:
	CCore();
	~CCore();
};