#pragma once

/**
* 미리 컴파일된 헤더 : compile 속도를 올리기 위해 만들어진 system(옵션)
* - '미리 컴파일된 헤더' 옵션을 사용하는 경우, 모든 cpp 파일에는 미리 컴파일된 헤더를 반드시 포함해야 한다.
*	-> '미리 컴파일된 헤더' 옵션을 사용하는 경우, 자동으로 cpp 파일에는 include 구문이 생성된다.
* - 변경점이 없다면, 미리 컴파일된 헤더에서 참조하고 있는 구문(include 구문)은 다시 컴파일하지 않는다.
* - 이미 완성된 코드(Window OS에서 제공하는 library, std 등)을 넣어 컴파일 속도를 빠르게 한다.
*/

#include <Windows.h>

#include "Define.h"