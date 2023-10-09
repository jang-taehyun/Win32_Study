#pragma once

/**
* Macro �Լ��� ������
* - function�� ȣ���ϰ� �ƴ϶� ������ ġȯ�ϴ� ���̹Ƿ�, Macro �������� ġȯ�ϰ� �� ������ �ڵ带 ������� �Ѵ�.
*/

// -> Macro���� \(��������)�� �ǹ� : Macro ������ ���� �ٿ��� �̾����ٴ� �ǹ�
#define SINGLETON(type)	public:\
							static type* GetInst()\
							{\
								static type mgr;\
								return &mgr;\
							}