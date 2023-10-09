#pragma once

/**
* Macro 함수의 주의점
* - function을 호출하게 아니라 무조건 치환하는 것이므로, Macro 구문으로 치환하고 난 다음에 코드를 살펴봐야 한다.
*/

// -> Macro에서 \(역슬레시)의 의미 : Macro 구문이 다음 줄에도 이어진다는 의미
#define SINGLETON(type)	public:\
							static type* GetInst()\
							{\
								static type mgr;\
								return &mgr;\
							}